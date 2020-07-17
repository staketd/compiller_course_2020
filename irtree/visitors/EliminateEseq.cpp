
#include "EliminateEseq.h"
#include <sources.h>

inline bool CheckForConst(ir_tree::IRExpression* expr) {
  return expr->GetType() == ir_tree::IRNodeType::Name ||
         expr->GetType() == ir_tree::IRNodeType::Const;
}

inline bool CheckForConst(ir_tree::IRStatement* stmt) {
  if (stmt->GetType() != ir_tree::IRNodeType::Exp) {
    return false;
  }
  ir_tree::ExpStatement* estmt = dynamic_cast<ir_tree::ExpStatement*>(stmt);
  return estmt->expression_->GetType() == ir_tree::IRNodeType::Const;
}

inline std::pair<ir_tree::IRStatement*, ir_tree::ExpressionList*> Reorder(
    ir_tree::ExpressionList* list) {
  size_t n = list->expressions_.size();
  auto result_list = new ir_tree::ExpressionList(
      std::vector<ir_tree::IRExpression*>(n, nullptr));
  auto& expr_list = result_list->expressions_;
  std::vector<ir_tree::IRStatement*> stmts;
  size_t first_not_saved = 0;
  for (size_t i = 0; i < n; ++i) {
    if (list->expressions_[i]->GetType() != ir_tree::IRNodeType::Eseq) {
      expr_list[i] = list->expressions_[i];
      continue;
    }
    auto eseq = dynamic_cast<ir_tree::EseqExpression*>(list->expressions_[i]);

    if (CheckForConst(eseq->statement_)) {
      stmts.push_back(eseq->statement_);
      expr_list[i] = eseq->expression_;
      continue;
    }

    for (; first_not_saved < i; ++first_not_saved) {
      if (CheckForConst(expr_list[first_not_saved])) {
        continue;
      }

      ir_tree::Temp t;
      stmts.push_back(new ir_tree::MoveStatement(
          expr_list[first_not_saved], new ir_tree::TempExpression(t)));
      expr_list[first_not_saved] = new ir_tree::TempExpression(t);
    }

    stmts.push_back(eseq->statement_);
    expr_list[i] = eseq->expression_;
  }

  if (stmts.empty()) {
    return {new ir_tree::ExpStatement(new ir_tree::ConstExpression(0)),
            result_list};
  }
  ir_tree::IRStatement* suffix = stmts.back();
  for (int i = stmts.size() - 2; i >= 0; --i) {
    suffix = new ir_tree::SeqStatement(stmts[i], suffix);
  }
  return {suffix, result_list};
}

void ir_tree::EliminateEseq::Visit(ir_tree::ConstExpression* expression) {
  last_value_set_.expression_ = new ConstExpression(expression->Value());
}

void ir_tree::EliminateEseq::Visit(ir_tree::NameExpression* expression) {
  last_value_set_.expression_ = new NameExpression(expression->label_);
}

void ir_tree::EliminateEseq::Visit(ir_tree::TempExpression* expression) {
  last_value_set_.expression_ = new TempExpression(expression->temp_);
}

void ir_tree::EliminateEseq::Visit(ir_tree::EseqExpression* expression) {
  auto stmt = VisitAndReturnVisitor(expression->statement_).statement_;
  auto expr = VisitAndReturnVisitor(expression->expression_).expression_;
  if (expr->GetType() == IRNodeType::Eseq) {
    EseqExpression* right_eseq = dynamic_cast<EseqExpression*>(expr);
    last_value_set_.expression_ = new EseqExpression(
        new SeqStatement(stmt, right_eseq->statement_), expr);
  } else {
    last_value_set_.expression_ = new EseqExpression(stmt, expr);
  }
}

void ir_tree::EliminateEseq::Visit(ir_tree::MemExpression* expression) {
  auto expr = VisitAndReturnVisitor(expression->expression_).expression_;
  if (expr->GetType() == IRNodeType::Eseq) {
    EseqExpression* eseq = dynamic_cast<EseqExpression*>(expr);
    last_value_set_.expression_ = new EseqExpression(
        eseq->statement_, new MemExpression(eseq->expression_));
  } else {
    last_value_set_.expression_ = new MemExpression(expr);
  }
}

void ir_tree::EliminateEseq::Visit(ir_tree::JumpStatement* stmt) {
  last_value_set_.statement_ = new JumpStatement(stmt->label_);
}

void ir_tree::EliminateEseq::Visit(ir_tree::JumpConditionalStatement* stmt) {
  auto left_expr = VisitAndReturnVisitor(stmt->left_).expression_;
  auto right_expr = VisitAndReturnVisitor(stmt->left_).expression_;

  if (left_expr->GetType() == IRNodeType::Eseq) {
    EseqExpression* left_eseq = dynamic_cast<EseqExpression*>(left_expr);

    if (right_expr->GetType() == IRNodeType::Eseq) {
      EseqExpression* right_eseq = dynamic_cast<EseqExpression*>(right_expr);
      Temp t;

      last_value_set_.statement_ = new SeqStatement(
          left_eseq->statement_,
          new SeqStatement(
              new MoveStatement(left_eseq->expression_, new TempExpression(t)),
              new SeqStatement(right_eseq->statement_,
                               new JumpConditionalStatement(
                                   stmt->operator_, new TempExpression(t),
                                   right_eseq->expression_, stmt->label_true_,
                                   stmt->label_false_))));
    } else {
      last_value_set_.statement_ = new SeqStatement(
          left_eseq->statement_,
          new JumpConditionalStatement(stmt->operator_, left_eseq->expression_,
                                       right_expr, stmt->label_true_,
                                       stmt->label_false_));
    }
  } else {
    if (right_expr->GetType() == IRNodeType::Eseq) {
      EseqExpression* right_eseq = dynamic_cast<EseqExpression*>(right_expr);
      Temp t;

      last_value_set_.statement_ = new SeqStatement(
          new MoveStatement(left_expr, new TempExpression(t)),
          new SeqStatement(right_eseq->statement_,
                           new JumpConditionalStatement(
                               stmt->operator_, new TempExpression(t),
                               right_eseq->expression_, stmt->label_true_,
                               stmt->label_false_)));
    } else {
      last_value_set_.statement_ =
          new JumpConditionalStatement(stmt->operator_, left_expr, right_expr,
                                       stmt->label_true_, stmt->label_false_);
    }
  }
}

void ir_tree::EliminateEseq::Visit(ir_tree::LabelStatement* statement) {
  last_value_set_.statement_ = new LabelStatement(statement->label_);
}

void ir_tree::EliminateEseq::Visit(ir_tree::MoveStatement* statement) {
  auto src = VisitAndReturnVisitor(statement->source_).expression_;
  auto dst = VisitAndReturnVisitor(statement->destination_).expression_;
  if (dst->GetType() == IRNodeType::Temp &&
      src->GetType() == IRNodeType::Eseq) {
    auto eseq = dynamic_cast<EseqExpression*>(src);
    auto temp = dynamic_cast<TempExpression*>(dst);
    last_value_set_.statement_ = new SeqStatement(
        eseq->statement_,
        new MoveStatement(eseq->expression_, new TempExpression(temp->temp_)));
  }

  if (dst->GetType() == IRNodeType::Mem) {
    auto mem = dynamic_cast<MemExpression*>(dst);
    if (mem->expression_->GetType() == IRNodeType::Eseq) {
      auto eseq = dynamic_cast<EseqExpression*>(mem->expression_);
      if (CheckForConst(src) || CheckForConst(eseq->statement_)) {
        last_value_set_.statement_ = new SeqStatement(
            eseq->statement_,
            new MoveStatement(src, new MemExpression(eseq->expression_)));
        return;
      }
      Temp t;
      last_value_set_.statement_ = new SeqStatement(
          new MoveStatement(src, new TempExpression(t)),
          new SeqStatement(
              eseq->statement_,
              new MoveStatement(new TempExpression(t),
                                new MemExpression(eseq->expression_))));
      return;
    }
  }

  if (src->GetType() == IRNodeType::Eseq && dst->GetType() == IRNodeType::Mem) {
    auto eseq = dynamic_cast<EseqExpression*>(src);
    auto mem = dynamic_cast<MemExpression*>(dst);
    if (CheckForConst(eseq->expression_) || CheckForConst(mem->expression_)) {
      last_value_set_.statement_ = new SeqStatement(
          eseq->statement_,
          new MoveStatement(eseq->expression_,
                            new MemExpression(mem->expression_)));
      return;
    }
    Temp t;
    last_value_set_.statement_ = new SeqStatement(
        new MoveStatement(mem->expression_, new TempExpression(t)),
        new SeqStatement(
            eseq->statement_,
            new MoveStatement(eseq->expression_,
                              new MemExpression(new TempExpression(t)))));
    return;
  }

  if (dst->GetType() == IRNodeType::Temp &&
      src->GetType() == IRNodeType::Call) {
    auto temp = dynamic_cast<TempExpression*>(dst);
    auto call = dynamic_cast<CallExpression*>(src);
    auto reordered = Reorder(call->args_);
    if (call->function_name_->GetType() == IRNodeType::Eseq) {
      auto eseq = dynamic_cast<EseqExpression*>(call->function_name_);
      last_value_set_.statement_ = new SeqStatement(
          eseq->statement_,
          new SeqStatement(
              reordered.first,
              new MoveStatement(
                  new CallExpression(
                      eseq->expression_,
                      reordered.second,
                      call->has_return_value_
                      ),
                  new TempExpression(
                      temp->temp_
                      )
                  )
              )
          );
      return;
    } else {
      last_value_set_.statement_ = new SeqStatement(
          reordered.first,
          new MoveStatement(
              new CallExpression(
                  call->function_name_,
                  reordered.second,
                  call->has_return_value_
                  ),
              new TempExpression(temp->temp_)
              )
          );
      return;
    }
  }

  last_value_set_.statement_ = new MoveStatement(src, dst);
}

void ir_tree::EliminateEseq::Visit(ir_tree::SeqStatement* stmt) {
  auto first = VisitAndReturnVisitor(stmt->first_).statement_;
  auto second = VisitAndReturnVisitor(stmt->second_).statement_;
  last_value_set_.statement_ = new ir_tree::SeqStatement(first, second);
}

void ir_tree::EliminateEseq::Visit(ir_tree::IRPrintStatement* stmt) {
  auto expr = VisitAndReturnVisitor(stmt->expression_).expression_;
  if (expr->GetType() == IRNodeType::Eseq) {
    auto eseq = dynamic_cast<EseqExpression*>(expr);

    last_value_set_.statement_ = new SeqStatement(
        eseq->statement_, new IRPrintStatement(eseq->expression_));
  } else {
    last_value_set_.statement_ = new IRPrintStatement(expr);
  }
}

void ir_tree::EliminateEseq::Visit(ir_tree::ExpStatement* stmt) {
  auto expr = VisitAndReturnVisitor(stmt->expression_).expression_;
  if (expr->GetType() == IRNodeType::Eseq) {
    auto eseq = dynamic_cast<EseqExpression*>(expr);

    last_value_set_.statement_ = eseq->statement_;
    return;
  }
  if (expr->GetType() == IRNodeType::Call) {
    auto call = dynamic_cast<CallExpression*>(expr);
    auto reordered = Reorder(call->args_);
    if (call->function_name_->GetType() == IRNodeType::Eseq) {
      auto eseq = dynamic_cast<EseqExpression*>(call->function_name_);
      last_value_set_.statement_ = new SeqStatement(
          eseq->statement_,
          new SeqStatement(
              reordered.first,
              new ExpStatement(
                  new CallExpression(
                      eseq->expression_,
                      reordered.second,
                      call->has_return_value_
                      )
                  )
              )
          );
      return;
    } else {
      last_value_set_.statement_ = new SeqStatement(
          reordered.first,
          new ExpStatement(
              new CallExpression(
                  call->function_name_,
                  reordered.second,
                  call->has_return_value_
                  )
              )
          );
      return;
    }
  }
  last_value_set_.statement_ = new ExpStatement(expr);
}

void ir_tree::EliminateEseq::Visit(ir_tree::CallExpression* expression) {
  auto expr = VisitAndReturnVisitor(expression->function_name_).expression_;
  auto args = VisitAndReturnVisitor(expression->args_).expression_list_;
  last_value_set_.expression_ =
      new CallExpression(expr, args, expression->has_return_value_);
}

void ir_tree::EliminateEseq::Visit(ir_tree::BinOpExpression* expr) {
  auto first = VisitAndReturnVisitor(expr->first_).expression_;
  auto second = VisitAndReturnVisitor(expr->second_).expression_;
  if (first->GetType() == IRNodeType::Eseq &&
      second->GetType() == IRNodeType::Eseq) {
    auto f_eseq = dynamic_cast<EseqExpression*>(first);
    auto s_eseq = dynamic_cast<EseqExpression*>(second);

    if (CheckForConst(f_eseq->expression_) ||
        CheckForConst(s_eseq->statement_)) {
      last_value_set_.expression_ = new EseqExpression(
          new SeqStatement(f_eseq->statement_, s_eseq->statement_),
          new BinOpExpression(expr->type_, f_eseq->expression_,
                              s_eseq->expression_));
      return;
    }
    Temp t;
    last_value_set_.expression_ = new EseqExpression(
        new SeqStatement(
            f_eseq->statement_,
            new SeqStatement(
                new MoveStatement(f_eseq->expression_, new TempExpression(t)),
                s_eseq->statement_)),
        new BinOpExpression(expr->type_, new TempExpression(t),
                            s_eseq->expression_));
    return;
  }

  if (first->GetType() == IRNodeType::Eseq) {
    auto f_eseq = dynamic_cast<EseqExpression*>(first);
    last_value_set_.expression_ = new EseqExpression(
        f_eseq->statement_,
        new BinOpExpression(expr->type_, f_eseq->expression_, second));
    return;
  }

  if (second->GetType() == IRNodeType::Eseq) {
    auto s_eseq = dynamic_cast<EseqExpression*>(second);
    Temp t;
    last_value_set_.expression_ = new EseqExpression(
        new MoveStatement(first, new TempExpression(t)),
        new BinOpExpression(expr->type_, new TempExpression(t),
                            s_eseq->expression_));
    return;
  }

  last_value_set_.expression_ = new BinOpExpression(expr->type_, first, second);
}

void ir_tree::EliminateEseq::Visit(ir_tree::ExpressionList* list) {
  auto new_list = new ExpressionList(std::vector<IRExpression*>());
  auto& value_list = new_list->expressions_;
  value_list.resize(list->expressions_.size());
  for (size_t i = 0; i < value_list.size(); ++i) {
    value_list[i] = VisitAndReturnVisitor(list->expressions_[i]).expression_;
  }
  last_value_set_.expression_list_ = new_list;
}

ir_tree::IRStatement* ir_tree::EliminateEseq::GetTree() {
  return last_value_set_.statement_;
}
