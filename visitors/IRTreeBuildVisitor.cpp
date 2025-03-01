
#include "IRTreeBuildVisitor.h"
#include <include/sources.h>
#include <ClassMap.h>

void IRTreeBuildVisitor::Visit(StatementList* statements) {
  if (statements->statements_.empty()) {
    last_value_set_ = nullptr;
    return;
  }
  if (statements->statements_.size() == 1) {
    last_value_set_ = VisitAndReturnValue(statements->statements_.back());
    return;
  }
  std::vector<ir_tree::IRStatement*> stmts;
  for (auto statement : statements->statements_) {
    auto stmt = VisitAndReturnValue(statement);
    if (stmt) {
      stmts.push_back(stmt->ToStatement());
    }
  }
  ir_tree::IRStatement* prev = stmts.back();
  for (int i = stmts.size() - 2; i >= 0; --i) {
    prev = new ir_tree::SeqStatement(stmts[i], prev);
  }
  last_value_set_ = new ir_tree::StatementWrapper(prev);
}

void IRTreeBuildVisitor::Visit(Assignment* assignment) {
  auto source = VisitAndReturnValue(assignment->expression_)->ToExpression();
  auto destination = GetAddress(Symbol(assignment->variable_));
  last_value_set_ = new ir_tree::StatementWrapper(
      new ir_tree::MoveStatement(source, destination));
}

void IRTreeBuildVisitor::VisitBinaryExpression(BinaryExpression* expression,
                                               ir_tree::BinOperatorType type) {
  auto first = VisitAndReturnValue(expression->first_);
  auto second = VisitAndReturnValue(expression->second_);

  last_value_set_ = new ir_tree::ExpressionWrapper(new ir_tree::BinOpExpression(
      type, first->ToExpression(), second->ToExpression()));
}

void IRTreeBuildVisitor::Visit(AddExpression* expression) {
  VisitBinaryExpression(expression, ir_tree::BinOperatorType::PLUS);
}

void IRTreeBuildVisitor::Visit(MulExpression* expression) {
  VisitBinaryExpression(expression, ir_tree::BinOperatorType::MUL);
}

void IRTreeBuildVisitor::Visit(DivExpression* expression) {
  VisitBinaryExpression(expression, ir_tree::BinOperatorType::DIV);
}

void IRTreeBuildVisitor::Visit(SubstractExpression* expression) {
  VisitBinaryExpression(expression, ir_tree::BinOperatorType::MINUS);
}

void IRTreeBuildVisitor::Visit(IdentExpression* expression) {
  last_value_set_ =
      new ir_tree::ExpressionWrapper(GetAddress(Symbol(expression->name_)));
}

void IRTreeBuildVisitor::Visit(NumExpression* expression) {
  last_value_set_ = new ir_tree::ExpressionWrapper(
      new ir_tree::ConstExpression(expression->value_));
}

void IRTreeBuildVisitor::Visit(Program* program) {
  Visit(program->main_);
  Visit(program->classes_);
}

void IRTreeBuildVisitor::Visit(PrintStatement* print) {
  auto expr = VisitAndReturnValue(print->expr_);
  last_value_set_ = new ir_tree::StatementWrapper(
      new ir_tree::IRPrintStatement(expr->ToExpression()));
}

void IRTreeBuildVisitor::Visit(ReadStatement*) {
  last_value_set_ = nullptr;
}

void IRTreeBuildVisitor::Visit(EqualExpression* expression) {
  VisitLogicExpression(expression, ir_tree::LogicOperatorType::EQ);
}

void IRTreeBuildVisitor::VisitLogicExpression(BinaryExpression* expression,
                                              ir_tree::LogicOperatorType type) {
  auto first = VisitAndReturnValue(expression->first_);
  auto second = VisitAndReturnValue(expression->second_);

  last_value_set_ = new ir_tree::CompareConditionalWrapper(
      type, first->ToExpression(), second->ToExpression());
}

void IRTreeBuildVisitor::Visit(LessExpression* expression) {
  VisitLogicExpression(expression, ir_tree::LogicOperatorType::LT);
}

void IRTreeBuildVisitor::Visit(GreaterExpression* expression) {
  VisitLogicExpression(expression, ir_tree::LogicOperatorType::GT);
}

void IRTreeBuildVisitor::Visit(LessOrEqualExpression* expression) {
  VisitLogicExpression(expression, ir_tree::LogicOperatorType::LE);
}

void IRTreeBuildVisitor::Visit(GreaterOrEqualExpression* expression) {
  VisitLogicExpression(expression, ir_tree::LogicOperatorType::GE);
}

void IRTreeBuildVisitor::Visit(IfStatement* if_stmt) {
  auto cond = VisitAndReturnValue(if_stmt->ifExpression_);
  auto true_stmt = VisitAndReturnValue(if_stmt->then_);

  ir_tree::SubtreeWrapper* false_stmt = nullptr;
  if (if_stmt->else_) {
    false_stmt = VisitAndReturnValue(if_stmt->else_);
  }

  ir_tree::Label true_label;
  ir_tree::Label false_label;
  ir_tree::Label after_label;

  ir_tree::Label* jump_true_label = &after_label;
  ir_tree::Label* jump_false_label = &after_label;

  ir_tree::IRStatement* suffix = new ir_tree::LabelStatement(after_label);

  if (false_stmt) {
    jump_false_label = &false_label;
    suffix = new ir_tree::SeqStatement(
        new ir_tree::LabelStatement(false_label),
        new ir_tree::SeqStatement(false_stmt->ToStatement(), suffix));

    if (true_stmt) {
      suffix = new ir_tree::SeqStatement(
          new ir_tree::JumpStatement(after_label), suffix);
    }
  }
  if (true_stmt) {
    jump_true_label = &true_label;
    suffix = new ir_tree::SeqStatement(
        new ir_tree::LabelStatement(true_label),
        new ir_tree::SeqStatement(true_stmt->ToStatement(), suffix));
  }
  last_value_set_ = new ir_tree::StatementWrapper(new ir_tree::SeqStatement(
      cond->ToConditional(*jump_true_label, *jump_false_label), suffix));
}

void IRTreeBuildVisitor::Visit(Scope* scope) {
  current_frame_->BeginScope();
  VisitAndReturnValue(scope->statements_);
  current_frame_->EndScope();
}

void IRTreeBuildVisitor::Visit(VariableDeclaration* vardecl) {
  ++decl_count_;
  current_frame_->AddLocalVariable(Symbol(vardecl->name_));
  auto expr = VisitAndReturnValue(vardecl->expression_);
  last_value_set_ = expr;
  if (expr != nullptr) {
    last_value_set_ = new ir_tree::StatementWrapper(new ir_tree::MoveStatement(
        expr->ToExpression(),
        current_frame_->GetAddress(Symbol(vardecl->name_))->ToExpression()));
  }
}

void IRTreeBuildVisitor::Visit(ModuloExpression* expression) {
  VisitBinaryExpression(expression, ir_tree::BinOperatorType::MOD);
}

void IRTreeBuildVisitor::Visit(WhileStatement* while_stmt) {
  auto cond = VisitAndReturnValue(while_stmt->check_expression_);
  auto stmts = VisitAndReturnValue(while_stmt->scope_);
  ir_tree::Label check_label;
  ir_tree::Label start_label;
  ir_tree::Label done_label;

  last_value_set_ = new ir_tree::StatementWrapper(new ir_tree::SeqStatement(
      new ir_tree::LabelStatement(check_label),
      new ir_tree::SeqStatement(
          cond->ToConditional(start_label, done_label),
          new ir_tree::SeqStatement(
              new ir_tree::LabelStatement(start_label),
              new ir_tree::SeqStatement(
                  stmts->ToStatement(),
                  new ir_tree::SeqStatement(
                      new ir_tree::JumpStatement(check_label),
                      new ir_tree::LabelStatement(done_label)))))));
}

void IRTreeBuildVisitor::Visit(CallArgumentList*) {
}

void IRTreeBuildVisitor::Visit(ClassMethod* method) {
  current_frame_ = new ir_tree::IRFrameTranslator(Symbol(method->name_));
  VisitAndReturnValue(method->arguments_);
  auto stmts = VisitAndReturnValue(method->statements_);
  auto asm_method_name = current_class_name_ + "__" + method->name_;
  ir_tree::Label method_label(asm_method_name);
  methods_[Symbol(asm_method_name)] =
      new ir_tree::StatementWrapper(new ir_tree::SeqStatement(
          new ir_tree::LabelStatement(method_label), stmts->ToStatement()));
  method_decl_count_[Symbol(asm_method_name)] = decl_count_;
  decl_count_ = 0;
}

void IRTreeBuildVisitor::Visit(ClassBody* class_body) {
  for (auto method : class_body->methods_) {
    Visit(method);
  }
}

void IRTreeBuildVisitor::Visit(MethodArgumentList* args) {
  for (auto arg : args->names_) {
    current_frame_->AddArgument(Symbol(arg));
  }
}

void IRTreeBuildVisitor::Visit(MethodCallExpression* expression) {
  auto obj = VisitAndReturnValue(expression->expression_);
  std::vector<ir_tree::IRExpression*> args;
  args.push_back(obj->ToExpression());
  for (auto arg : expression->arguments_->arguments_) {
    args.push_back(VisitAndReturnValue(arg)->ToExpression());
  }
  last_value_set_ = new ir_tree::ExpressionWrapper(new ir_tree::CallExpression(
      new ir_tree::NameExpression(ir_tree::Label(expression->class_type_name_ +
                                                 "__" + expression->name_)),
      new ir_tree::ExpressionList(args), expression->has_return_value_));
}

void IRTreeBuildVisitor::Visit(ReturnStatement* return_stmt) {
  auto return_expr = VisitAndReturnValue(return_stmt->expression_);
  last_value_set_ = new ir_tree::StatementWrapper(new ir_tree::MoveStatement(
      return_expr->ToExpression(),
      current_frame_->GetReturnValueAddress()->ToExpression()));
}

void IRTreeBuildVisitor::Visit(MethodCallStmt* stmt) {
  Visit(stmt->expression_);
}

void IRTreeBuildVisitor::Visit(Class* class_ast) {
  current_class_name_ = class_ast->name_;
  Visit(class_ast->body_);
}

void IRTreeBuildVisitor::Visit(ClassList* list) {
  for (auto x : list->classes_) {
    Visit(x);
  }
}

void IRTreeBuildVisitor::Visit(ClassField*) {
}

void IRTreeBuildVisitor::Visit(ClassMain* main) {
  current_class_name_ = main->name_;
  Visit(main->main_);
}

void IRTreeBuildVisitor::Visit(ThisExpression* expression) {
  last_value_set_ = new ir_tree::ExpressionWrapper(
      new ir_tree::MemExpression(new ir_tree::BinOpExpression(
          ir_tree::BinOperatorType::PLUS,
          new ir_tree::TempExpression(ir_tree::Temp("::fp")),
          new ir_tree::ConstExpression(16))));
}

void IRTreeBuildVisitor::Visit(NewExpression* expression) {
  auto class_layout = class_map_.GetClassLayout(Symbol(expression->type_));
  auto class_body = class_map_.GetClass(Symbol(expression->type_))->body_;
  ir_tree::Temp t;
  ir_tree::IRStatement* alloc = new ir_tree::MoveStatement(
      new ir_tree::AllocExpression(std::max(8ul, class_layout->GetSize())),
      new ir_tree::TempExpression(t));
  ir_tree::IRStatement* stmts = nullptr;
  for (auto field : class_body->fields_) {
    if (class_map_.HasClass(Symbol(field->type_))) {
      size_t offset = class_layout->GetOffset(Symbol(field->name_));
      auto move = new ir_tree::MoveStatement(
          new ir_tree::ConstExpression(0),
          new ir_tree::MemExpression(new ir_tree::BinOpExpression(
              ir_tree::BinOperatorType::PLUS, new ir_tree::TempExpression(t),
              new ir_tree::ConstExpression(offset))));
      if (stmts == nullptr) {
        stmts = move;
      } else {
        stmts = new ir_tree::SeqStatement(move, stmts);
      }
    }
  }
  if (stmts != nullptr) {
    stmts = new ir_tree::SeqStatement(alloc, stmts);
  } else {
    stmts = alloc;
  }
  last_value_set_ = new ir_tree::ExpressionWrapper(
      new ir_tree::EseqExpression(stmts, new ir_tree::TempExpression(t)));
}

void IRTreeBuildVisitor::Visit(ArrayDeclaration*) {
  last_value_set_ = nullptr;
}

void IRTreeBuildVisitor::Visit(ArrayAssignment* assignment) {
  auto expr = VisitAndReturnValue(assignment->expression_);
  auto ind_expr = VisitAndReturnValue(assignment->ind_expression_);

  last_value_set_ = new ir_tree::StatementWrapper(new ir_tree::MoveStatement(
      new ir_tree::BinOpExpression(
          ir_tree::BinOperatorType::PLUS,
          current_frame_->GetAddress(Symbol(assignment->array_name_))
              ->ToExpression(),
          ind_expr->ToExpression()),
      expr->ToExpression()));
}
void IRTreeBuildVisitor::Visit(ArrayExpression* expression) {
  auto ind_expr = VisitAndReturnValue(expression->expression_);
  last_value_set_ = new ir_tree::ExpressionWrapper(new ir_tree::BinOpExpression(
      ir_tree::BinOperatorType::PLUS,
      current_frame_->GetAddress(Symbol(expression->name_))->ToExpression(),
      ind_expr->ToExpression()));
}

void IRTreeBuildVisitor::Visit(LogicOrExpression* expression) {
  auto left = VisitAndReturnValue(expression->first_);
  auto right = VisitAndReturnValue(expression->second_);

  last_value_set_ = new ir_tree::AndConditionalWrapper(left, right);
}

void IRTreeBuildVisitor::Visit(LogicAndExpression* expression) {
  auto left = VisitAndReturnValue(expression->first_);
  auto right = VisitAndReturnValue(expression->second_);

  last_value_set_ = new ir_tree::OrConditionalWrapper(left, right);
}
void IRTreeBuildVisitor::Build(Program* program) {
  Visit(program);
}

std::unordered_map<Symbol, ir_tree::SubtreeWrapper*>
IRTreeBuildVisitor::GetMethods() {
  return std::move(methods_);
}

IRTreeBuildVisitor::IRTreeBuildVisitor(ClassMap& class_map)
    : class_map_(class_map), decl_count_(0) {
}

ir_tree::IRExpression* IRTreeBuildVisitor::GetAddress(const Symbol& symbol) {
  ir_tree::IRExpression* address;
  if (current_frame_->HasVariable(symbol)) {
    address = current_frame_->GetAddress(symbol)->ToExpression();
  } else {
    auto class_layout = class_map_.GetClassLayout(Symbol(current_class_name_));
    size_t offset = class_layout->GetOffset(symbol);
    address = new ir_tree::MemExpression(new ir_tree::BinOpExpression(
        ir_tree::BinOperatorType::PLUS,
        new ir_tree::MemExpression(new ir_tree::BinOpExpression(
            ir_tree::BinOperatorType::MINUS,
            new ir_tree::TempExpression(ir_tree::Temp("::fp")),
            new ir_tree::ConstExpression(8))),
        new ir_tree::ConstExpression(offset)));
  }
  return address;
}

std::unordered_map<Symbol, size_t> IRTreeBuildVisitor::GetDecls() {
  return std::move(method_decl_count_);
}
