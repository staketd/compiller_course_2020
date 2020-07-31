
#include "AsmGenerator.h"
#include <sources.h>
#include <Print.h>
#include <macros.h>
#include <algorithm>
#include <Instructions.h>

void ir_tree::AsmGenerator::Visit(ir_tree::LabelStatement* statement) {
  Add(new LabelInstruction(statement->label_.ToString()));
}

inline int ArithOperation(int a, int b, ir_tree::BinOperatorType type) {
  switch (type) {
    case ir_tree::BinOperatorType::PLUS:
      return a + b;
    case ir_tree::BinOperatorType::MINUS:
      return a - b;
    case ir_tree::BinOperatorType::MUL:
      return a * b;
    case ir_tree::BinOperatorType::DIV:
      return a / b;
    case ir_tree::BinOperatorType::AND:
      return a & b;
    case ir_tree::BinOperatorType::OR:
      return a | b;
    case ir_tree::BinOperatorType::MOD:
      return a % b;
  }
  return 0;
}

inline AsmInstruction* BinOpInst(ir_tree::BinOperatorType type,
                                 const std::string dst, const std::string src) {
  switch (type) {
    case ir_tree::BinOperatorType::PLUS:
      return new AddInstruction(dst, src);
    case ir_tree::BinOperatorType::MINUS:
      return new SubInstruction(dst, src);
    case ir_tree::BinOperatorType::MUL:
      return new IMulInstruction(dst, src);
    case ir_tree::BinOperatorType::DIV:
      return new IDivInstruction(src);
    case ir_tree::BinOperatorType::AND:
      return new AndInstruction(dst, src);
    case ir_tree::BinOperatorType::OR:
      return new AndInstruction(dst, src);
    case ir_tree::BinOperatorType::MOD:
      return new IDivInstruction(src);
  }
  return nullptr;
}

std::string ir_tree::AsmGenerator::BinOp(ir_tree::IRExpression* first,
                                         ir_tree::IRExpression* second,
                                         ir_tree::BinOperatorType type) {
  if (type == BinOperatorType::MOD || type == BinOperatorType::DIV) {
    return Div(first, second, type);
  }
  if (first->GetType() == IRNodeType::Const &&
      second->GetType() == IRNodeType::Const) {
    auto const1 = dynamic_cast<ConstExpression*>(first)->Value();
    auto const2 = dynamic_cast<ConstExpression*>(second)->Value();
    Temp t;
    Add(new MovInstruction(t.ToString(),
                           std::to_string(ArithOperation(const1, const2, type)),
                           0, 0, false, false));
    return t.ToString();
  } else if (first->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(second);
    Temp t;
    auto const1 = dynamic_cast<ConstExpression*>(first)->Value();
    Add(new MovInstruction(t.ToString(), std::to_string(const1), 0, 0, false,
                           false));
    Add(BinOpInst(type, t.ToString(), name));
  } else if (second->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(first);
    if (name[0] == ':') {
      Temp t;
      Add(new MovInstruction(t.ToString(), name));
      name = t.ToString();
    }
    auto const1 = dynamic_cast<ConstExpression*>(second);
    Add(BinOpInst(type, name, std::to_string(const1->Value())));
    return name;
  } else {
    auto name1 = VisitAndReturnValue(first);
    auto name2 = VisitAndReturnValue(second);
    if (name1[0] == ':') {
      Temp t;
      Add(new MovInstruction(t.ToString(), name1));
      name1 = t.ToString();
    }
    Add(BinOpInst(type, name1, name2));
    return name1;
  }
  UNREACHABLE("")
}

void ir_tree::AsmGenerator::Visit(ir_tree::BinOpExpression* expression) {
  auto& first = expression->first_;
  auto& second = expression->second_;
  switch (expression->type_) {
    case BinOperatorType::PLUS:
      last_value_set_ = BinOp(first, second, BinOperatorType::PLUS);
      break;
    case BinOperatorType::MINUS:
      last_value_set_ = BinOp(first, second, BinOperatorType::MINUS);
      break;
    case BinOperatorType::MUL:
      last_value_set_ = BinOp(first, second, BinOperatorType::MUL);
      break;
    case BinOperatorType::DIV:
      last_value_set_ = BinOp(first, second, BinOperatorType::DIV);
      break;
    case BinOperatorType::AND:
      last_value_set_ = BinOp(first, second, BinOperatorType::AND);
      break;
    case BinOperatorType::OR:
      last_value_set_ = BinOp(first, second, BinOperatorType::OR);
      break;
    case BinOperatorType::MOD:
      last_value_set_ = BinOp(first, second, BinOperatorType::MOD);
      break;
  }
}

void ir_tree::AsmGenerator::Visit(ir_tree::ConstExpression* expression) {
  Temp t;
  auto reg_name = t.ToString();
  Add(new MovInstruction(reg_name, std::to_string(expression->Value())));
  last_value_set_ = reg_name;
}

void ir_tree::AsmGenerator::Visit(ir_tree::EseqExpression*) {
  UNREACHABLE("Eseq found")
}

void ir_tree::AsmGenerator::Visit(ir_tree::TempExpression* expression) {
  last_value_set_ = expression->temp_.ToString();
}

void ir_tree::AsmGenerator::Visit(ir_tree::ExpStatement* statement) {
  statement->expression_->AcceptVisitor(this);
}

void ir_tree::AsmGenerator::Visit(ir_tree::JumpStatement* statement) {
  Add(new JumpInstruction(statement->label_.ToString(), JumpType::jmp));
}

void ir_tree::AsmGenerator::Visit(ir_tree::SeqStatement*) {
  UNREACHABLE("Seq found")
}

void ir_tree::AsmGenerator::Visit(ir_tree::MemExpression* expression) {
  Temp reg;
  auto reg_name = reg.ToString();
  auto expr = expression->expression_;
  if (expr->GetType() == IRNodeType::Const) {
    auto con = dynamic_cast<ConstExpression*>(expr)->Value();
    Add(new MovInstruction(reg_name, std::to_string(con), 0, 0, false, true));
    last_value_set_ = reg_name;
    return;
  }

  if (expr->GetType() != IRNodeType::BinOp) {
    auto name = VisitAndReturnValue(expr);
    Add(new MovInstruction(reg_name, name, 0, 0, false, true));
    last_value_set_ = reg_name;
    return;
  }

  auto binop = dynamic_cast<BinOpExpression*>(expr);

  if ((binop->first_->GetType() == IRNodeType::Const) ==
          (binop->second_->GetType() == IRNodeType::Const) ||
      (binop->type_ != BinOperatorType::PLUS &&
       binop->type_ != BinOperatorType::MINUS)) {
    auto name = VisitAndReturnValue(expr);
    Add(new MovInstruction(reg_name, name, 0, 0, false, true));
    last_value_set_ = reg_name;
    return;
  }

  int factor = 1;
  if (binop->type_ == BinOperatorType::MINUS) {
    factor = -1;
  }

  if (binop->first_->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(binop->second_);
    auto con = dynamic_cast<ConstExpression*>(binop->first_)->Value();
    Add(new MovInstruction(reg_name, name, 0, con * factor, false, true));
    last_value_set_ = reg_name;
    return;
  }

  auto name = VisitAndReturnValue(binop->first_);
  auto con = dynamic_cast<ConstExpression*>(binop->second_)->Value();
  Add(new MovInstruction(reg_name, name, 0, con * factor, false, true));

  last_value_set_ = reg_name;
}

void ir_tree::AsmGenerator::Visit(ir_tree::NameExpression* expression) {
  last_value_set_ = expression->label_.ToString();
}

void ir_tree::AsmGenerator::Visit(
    ir_tree::JumpConditionalStatement* statement) {
  auto left = statement->left_;
  auto right = statement->right_;
  auto true_label = statement->label_true_.ToString();

  if (left->GetType() == IRNodeType::Const &&
      right->GetType() == IRNodeType::Const) {
    auto left_const = dynamic_cast<ConstExpression*>(left)->Value();
    auto right_const = dynamic_cast<ConstExpression*>(right)->Value();
    bool flag = false;
    switch (statement->operator_) {
      case LogicOperatorType::LT:
        if (left_const < right_const) {
          flag = true;
        }
        break;
      case LogicOperatorType::GT:
        if (left_const > right_const) {
          flag = true;
        }
        break;
      case LogicOperatorType::LE:
        if (left_const <= right_const) {
          flag = true;
        }
        break;
      case LogicOperatorType::GE:
        if (left_const >= right_const) {
          flag = true;
        }
        break;
      case LogicOperatorType::EQ:
        if (left_const == right_const) {
          flag = true;
        }
        break;
      case LogicOperatorType::NE:
        if (left_const != right_const) {
          flag = true;
        }
        break;
    }
    if (flag) {
      Add(new JumpInstruction(true_label, JumpType::jmp));
    }
    return;
  }

  JumpType type;

  switch (statement->operator_) {
    case LogicOperatorType::LT:
      type = JumpType::jl;
      break;
    case LogicOperatorType::GT:
      type = JumpType::jg;
      break;
    case LogicOperatorType::LE:
      type = JumpType::jle;
      break;
    case LogicOperatorType::GE:
      type = JumpType::jge;
      break;
    case LogicOperatorType::EQ:
      type = JumpType::jz;
      break;
    case LogicOperatorType::NE:
      type = JumpType::jnz;
      break;
  }

  if (left->GetType() == IRNodeType::Const) {
    auto left_const = dynamic_cast<ConstExpression*>(left)->Value();
    auto name = VisitAndReturnValue(right);
    Temp t;
    Add(new MovInstruction(t.ToString(), std::to_string(left_const)));
    Add(new CmpInstruction(t.ToString(), name));
  }

  if (right->GetType() == IRNodeType::Const) {
    auto right_const = dynamic_cast<ConstExpression*>(right)->Value();
    auto name = VisitAndReturnValue(left);
    Add(new CmpInstruction(name, std::to_string(right_const)));
  }

  if (left->GetType() != IRNodeType::Const &&
      right->GetType() != IRNodeType::Const) {
    auto name1 = VisitAndReturnValue(left);
    auto name2 = VisitAndReturnValue(right);
    Add(new CmpInstruction(name1, name2));
  }
  Add(new JumpInstruction(true_label, type));
}

void ir_tree::AsmGenerator::Visit(ir_tree::ExpressionList* list) {
  UNREACHABLE("")
}

void ir_tree::AsmGenerator::Visit(ir_tree::MoveStatement* statement) {
  bool print_epilogue = false;
  if (statement->destination_->GetType() == IRNodeType::Temp) {
    auto temp = dynamic_cast<TempExpression*>(statement->destination_);
    if (temp->temp_.ToString() == "::return_value") {
      print_epilogue = true;
    }
  }

  if (statement->destination_->GetType() != IRNodeType::Mem) {
    auto reg2 = VisitAndReturnValue(statement->source_);
    auto reg1 = VisitAndReturnValue(statement->destination_);
    Add(new MovInstruction(reg1, reg2));
  } else {
    std::string src;
    if (statement->source_->GetType() == IRNodeType::Const) {
      auto con = dynamic_cast<ConstExpression*>(statement->source_);
      src = std::to_string(con->Value());
    } else {
      src = VisitAndReturnValue(statement->source_);
    }
    auto mem = dynamic_cast<MemExpression*>(statement->destination_);
    switch (mem->expression_->GetType()) {
      case IRNodeType::Const: {
        auto con = dynamic_cast<ConstExpression*>(mem->expression_)->Value();
        Add(new MovInstruction(std::to_string(con), src, 0, 0, true, false));
        break;
      }
      case IRNodeType::BinOp: {
        auto binop = dynamic_cast<BinOpExpression*>(mem->expression_);
        if (binop->type_ == BinOperatorType::PLUS ||
            binop->type_ == BinOperatorType::MINUS) {
          auto left = binop->first_->GetType();
          auto right = binop->second_->GetType();
          if ((left == IRNodeType::Const) + (right == IRNodeType::Const) == 1) {
            IRExpression* node_to_visit = binop->first_;
            IRExpression* const_expr = binop->second_;
            if (left == IRNodeType::Const) {
              std::swap(node_to_visit, const_expr);
            }
            auto name = VisitAndReturnValue(node_to_visit);
            auto con = dynamic_cast<ConstExpression*>(const_expr)->Value();
            if (binop->type_ == BinOperatorType::MINUS) {
              con = -con;
            }
            Add(new MovInstruction(name, src, con, 0, true, false));
            break;
          }
        }
      }
      default: {
        auto dst = VisitAndReturnValue(mem->expression_);
        Add(new MovInstruction(dst, src, 0, 0, true, false));
      }
    }
  }

  if (print_epilogue) {
    AddEpilogue();
  }
}

void ir_tree::AsmGenerator::Visit(ir_tree::CallExpression* expression) {
  for (auto expr : expression->args_->expressions_) {
    auto name = VisitAndReturnValue(expr);
    Add(new PushInstruction(name));
  }
  auto func_name = VisitAndReturnValue(expression->function_name_);

  Temp t;
  Add(new CallInstruction(func_name));

  Add(new MovInstruction(t.ToString(), "rax"));

  for (size_t i = 0; i < expression->args_->expressions_.size(); ++i) {
    Add(new PopInstruction());
  }
  last_value_set_ = t.ToString();
}

void ir_tree::AsmGenerator::Visit(ir_tree::IRPrintStatement* statement) {
  auto name = VisitAndReturnValue(statement->expression_);
  Add(new PushInstruction(name));
  Add(new CallInstruction("print"));
  Add(new PopInstruction(name));
}

void ir_tree::AsmGenerator::AddEpilogue() {
  Add(new MovInstruction("rsp", "rbp"));
  Add(new PopInstruction("rbp"));
  Add(new RetInstruction());
}

void ir_tree::AsmGenerator::AddPrologue() {
  Add(new PushInstruction("rbp"));
  Add(new MovInstruction("rbp", "rsp"));
}

std::string ir_tree::AsmGenerator::Div(ir_tree::IRExpression* first,
                                       ir_tree::IRExpression* second,
                                       BinOperatorType type) {
  std::string to_return;
  auto src = "rax";
  if (type == BinOperatorType::MOD) {
    src = "rdx";
  }
  if (first->GetType() == IRNodeType::Const &&
      second->GetType() == IRNodeType::Const) {
    auto const1 = dynamic_cast<ConstExpression*>(first)->Value();
    auto const2 = dynamic_cast<ConstExpression*>(second)->Value();
    Temp t;
    Add(new MovInstruction(
        t.ToString(), std::to_string(ArithOperation(const1, const2, type))));
    to_return = t.ToString();
  } else if (first->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(second);
    auto const1 = dynamic_cast<ConstExpression*>(first)->Value();
    Add(new MovInstruction("rax", std::to_string(const1)));
    Add(new IDivInstruction(name));
    Add(new MovInstruction(name, src));
    to_return = name;
  } else if (second->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(first);
    auto const1 = dynamic_cast<ConstExpression*>(second)->Value();
    Add(new MovInstruction("rax", name));
    Add(new MovInstruction(name, std::to_string(const1)));
    Add(new IDivInstruction(name));
    Add(new MovInstruction(name, src));
    to_return = name;
  } else {
    auto name1 = VisitAndReturnValue(first);
    auto name2 = VisitAndReturnValue(second);
    Add(new MovInstruction("rax", name1));
    Add(new IDivInstruction(name2));
    Add(new MovInstruction(name1, src));
    to_return = name1;
  }
  return to_return;
}

ir_tree::AsmGenerator::AsmGenerator(const std::string& start) {
  Add(new LabelInstruction("_start"));
  Add(new JumpInstruction(start, JumpType::jmp));
}

void ir_tree::AsmGenerator::Add(AsmInstruction* instruction) {
  instructions_.push_back(instruction);
}

void ir_tree::AsmGenerator::PrintHead(std::ostream& stream) {
  MyPrint(stream, "\t.intel_syntax noprefix\n");
  MyPrint(stream, "\tglobal _start\n");
  MyPrint(stream, "\t.text\n");
}

void ir_tree::AsmGenerator::PrintInstructions(std::ostream& stream) {
  for (auto inst : instructions_) {
    inst->Print(stream);
  }
}
void ir_tree::AsmGenerator::PrintAll(std::ostream& stream) {
  PrintHead(stream);
  PrintInstructions(stream);
}

std::vector<AsmInstruction*>& ir_tree::AsmGenerator::GetInstructions() {
  return instructions_;
}
