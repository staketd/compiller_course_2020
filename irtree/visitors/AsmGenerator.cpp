
#include "AsmGenerator.h"
#include <sources.h>
#include <Print.h>
#include <macros.h>
#include <algorithm>

void ir_tree::AsmGenerator::Visit(ir_tree::LabelStatement* statement) {
  MyPrint(stream_, statement->label_.ToString(), ":\n");
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

std::string ir_tree::AsmGenerator::BinOp(ir_tree::IRExpression* first,
                                         ir_tree::IRExpression* second,
                                         ir_tree::BinOperatorType type,
                                         const std::string& asm_op) {
  if (type == BinOperatorType::MOD || type == BinOperatorType::DIV) {
    return Div(first, second, type);
  }
  if (first->GetType() == IRNodeType::Const &&
      second->GetType() == IRNodeType::Const) {
    auto const1 = dynamic_cast<ConstExpression*>(first);
    auto const2 = dynamic_cast<ConstExpression*>(second);
    Temp t;
    MyPrint(stream_, '\t', "mov ", t.ToString(), " ",
            ArithOperation(const1->Value(), const2->Value(), type), '\n');
    return t.ToString();
  } else if (first->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(second);
    Temp t;
    auto const1 = dynamic_cast<ConstExpression*>(first);
    MyPrint(stream_, '\t', "mov ", t.ToString(), " ", const1->Value(), '\n');
    MyPrint(stream_, '\t', asm_op, " ", t.ToString(), " ", name, '\n');
  } else if (second->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(first);
    auto const1 = dynamic_cast<ConstExpression*>(second);
    MyPrint(stream_, '\t', asm_op, " ", name, " ", const1->Value(), '\n');
    return name;
  } else {
    auto name1 = VisitAndReturnValue(first);
    auto name2 = VisitAndReturnValue(second);
    MyPrint(stream_, '\t', asm_op, " ", name1, " ", name2, "\n");
    return name1;
  }
  return "kek";
}

void ir_tree::AsmGenerator::Visit(ir_tree::BinOpExpression* expression) {
  auto& first = expression->first_;
  auto& second = expression->second_;
  switch (expression->type_) {
    case BinOperatorType::PLUS:
      last_value_set_ = BinOp(first, second, BinOperatorType::PLUS, "add");
      break;
    case BinOperatorType::MINUS:
      last_value_set_ = BinOp(first, second, BinOperatorType::MINUS, "sub");
      break;
    case BinOperatorType::MUL:
      last_value_set_ = BinOp(first, second, BinOperatorType::MUL, "imul");
      break;
    case BinOperatorType::DIV:
      last_value_set_ = BinOp(first, second, BinOperatorType::DIV, "idiv");
      break;
    case BinOperatorType::AND:
      last_value_set_ = BinOp(first, second, BinOperatorType::AND, "and");
      break;
    case BinOperatorType::OR:
      last_value_set_ = BinOp(first, second, BinOperatorType::OR, "or");
      break;
    case BinOperatorType::MOD:
      last_value_set_ = BinOp(first, second, BinOperatorType::MOD, "idiv");
      break;
  }
}

void ir_tree::AsmGenerator::Visit(ir_tree::ConstExpression* expression) {
  Temp t;
  auto reg_name = t.ToString();
  MyPrint(stream_, "\t", "mov ", reg_name, " ", expression->Value(), "\n");
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
  MyPrint(stream_, "\tjmp ", statement->label_.ToString(), "\n");
}

void ir_tree::AsmGenerator::Visit(ir_tree::SeqStatement*) {
  UNREACHABLE("Seq found")
}

void ir_tree::AsmGenerator::Visit(ir_tree::MemExpression* expression) {
  Temp reg;
  auto reg_name = reg.ToString();
  auto expr = expression->expression_;
  if (expr->GetType() == IRNodeType::Const) {
    auto con = dynamic_cast<ConstExpression*>(expr);
    MyPrint(stream_, "\tmov ", reg_name, " [", con->Value(), "]\n");
    last_value_set_ = reg_name;
    return;
  }

  if (expr->GetType() != IRNodeType::BinOp) {
    auto name = VisitAndReturnValue(expr);
    MyPrint(stream_, "\tmov ", reg_name, " [", name, "]\n");
    last_value_set_ = reg_name;
    return;
  }

  auto binop = dynamic_cast<BinOpExpression*>(expr);

  if ((binop->first_->GetType() == IRNodeType::Const) ==
          (binop->second_->GetType() == IRNodeType::Const) ||
      binop->type_ != BinOperatorType::PLUS) {
    auto name = VisitAndReturnValue(expr);
    MyPrint(stream_, "\tmov ", reg_name, " [", name, "]\n");
    last_value_set_ = reg_name;
    return;
  }

  if (binop->first_->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(binop->second_);
    auto con = dynamic_cast<ConstExpression*>(binop->first_);
    MyPrint(stream_, "\tmov ", reg_name, " [", name, " + ", con->Value(),
            "]\n");
    last_value_set_ = reg_name;
    return;
  }

  auto name = VisitAndReturnValue(binop->first_);
  auto con = dynamic_cast<ConstExpression*>(binop->second_);
  MyPrint(stream_, "\tmov ", reg_name, " [", name, " + ", con->Value(), "]\n");
  last_value_set_ = reg_name;
}

void ir_tree::AsmGenerator::Visit(ir_tree::NameExpression* expression) {
  last_value_set_ = expression->label_.ToString();
}

void ir_tree::AsmGenerator::Visit(
    ir_tree::JumpConditionalStatement* statement) {
  auto left = statement->left_;
  auto right = statement->right_;

  if (left->GetType() == IRNodeType::Const &&
      right->GetType() == IRNodeType::Const) {
    auto left_const = dynamic_cast<ConstExpression*>(left)->Value();
    auto right_const = dynamic_cast<ConstExpression*>(right)->Value();

    switch (statement->operator_) {
      case LogicOperatorType::LT:
        if (left_const < right_const) {
          MyPrint(stream_, "\tjmp ", statement->label_true_.ToString(), "\n");
        }
        break;
      case LogicOperatorType::GT:
        if (left_const > right_const) {
          MyPrint(stream_, "\tjmp ", statement->label_true_.ToString(), "\n");
        }
        break;
      case LogicOperatorType::LE:
        if (left_const <= right_const) {
          MyPrint(stream_, "\tjmp ", statement->label_true_.ToString(), "\n");
        }
        break;
      case LogicOperatorType::GE:
        if (left_const >= right_const) {
          MyPrint(stream_, "\tjmp ", statement->label_true_.ToString(), "\n");
        }
        break;
      case LogicOperatorType::EQ:
        if (left_const == right_const) {
          MyPrint(stream_, "\tjmp ", statement->label_true_.ToString(), "\n");
        }
        break;
      case LogicOperatorType::NE:
        if (left_const != right_const) {
          MyPrint(stream_, "\tjmp ", statement->label_true_.ToString(), "\n");
        }
        break;
    }
    return;
  }

  std::string jump;

  switch (statement->operator_) {
    case LogicOperatorType::LT:
      jump = "jl";
      break;
    case LogicOperatorType::GT:
      jump = "jg";
      break;
    case LogicOperatorType::LE:
      jump = "jle";
      break;
    case LogicOperatorType::GE:
      jump = "jge";
      break;
    case LogicOperatorType::EQ:
      jump = "jz";
      break;
    case LogicOperatorType::NE:
      jump = "jnz";
      break;
  }

  if (left->GetType() == IRNodeType::Const) {
    auto left_const = dynamic_cast<ConstExpression*>(left)->Value();
    auto name = VisitAndReturnValue(right);
    Temp t;
    MyPrint(stream_, "\tmov ", t.ToString(), " ", left_const, "\n");
    MyPrint(stream_, "\tcmp ", t.ToString(), " ", name, "\n");
  }

  if (right->GetType() == IRNodeType::Const) {
    auto right_const = dynamic_cast<ConstExpression*>(right)->Value();
    auto name = VisitAndReturnValue(right);
    MyPrint(stream_, "\tcmp ", name, " ", right_const, "\n");
  }

  if (left->GetType() != IRNodeType::Const &&
      right->GetType() != IRNodeType::Const) {
    auto name1 = VisitAndReturnValue(left);
    auto name2 = VisitAndReturnValue(right);

    MyPrint(stream_, "\tcmp ", name1, " ", name2, "\n");
  }

  MyPrint(stream_, "\t", jump, " ", statement->label_true_.ToString(), "\n");
}

void ir_tree::AsmGenerator::Visit(ir_tree::ExpressionList* list) {
  UNREACHABLE("")
}

void ir_tree::AsmGenerator::Visit(ir_tree::MoveStatement* statement) {
  bool print_epilogue = false;
  if (statement->source_->GetType() == IRNodeType::Temp) {
    auto temp = dynamic_cast<TempExpression*>(statement->source_);
    if (temp->temp_.ToString() == "::return_value") {
      print_epilogue = true;
    }
  }

  if (statement->destination_->GetType() != IRNodeType::Mem) {
    auto reg1 = VisitAndReturnValue(statement->source_);
    auto reg2 = VisitAndReturnValue(statement->destination_);
    MyPrint(stream_, "\tmov ", reg1, " ", reg2, "\n");
  } else {
    auto src = VisitAndReturnValue(statement->source_);
    auto mem = dynamic_cast<MemExpression*>(statement->destination_);
    switch (mem->expression_->GetType()) {
      case IRNodeType::Const: {
        auto con = dynamic_cast<ConstExpression*>(mem->expression_);
        MyPrint(stream_, "\tmov [", con->Value(), "] ", src, "\n");
        break;
      }
      case IRNodeType::BinOp: {
        auto binop = dynamic_cast<BinOpExpression*>(mem->expression_);
        if (binop->type_ == BinOperatorType::PLUS) {
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
            MyPrint(stream_, "\tmov [", name, " + ", con, "] ", src, "\n");
            break;
          }
        }
      }
      default: {
        auto dst = VisitAndReturnValue(mem->expression_);
        MyPrint(stream_, "\tmov [", dst, "] ", src, "\n");
      }
    }
  }

  if (print_epilogue) {
    PrintEpilogue();
  }
}

void ir_tree::AsmGenerator::Visit(ir_tree::CallExpression* expression) {
  std::vector<std::string> names;
  for (auto expr : expression->args_->expressions_) {
    auto name = VisitAndReturnValue(expr);
    names.push_back(name);
  }
  for (auto name : names) {
    MyPrint(stream_, "\tpush ", name, "\n");
  }
  auto func_name = VisitAndReturnValue(expression->function_name_);

  Temp t;

  MyPrint(stream_, "\tcall ", func_name, "\n");

  MyPrint(stream_, "\tmov ", t.ToString(), " rax\n");

  std::reverse(names.begin(), names.end());

  for (auto name : names) {
    MyPrint(stream_, "\tpop ", name, "\n");
  }
  last_value_set_ = t.ToString();
}

void ir_tree::AsmGenerator::Visit(ir_tree::IRPrintStatement* statement) {
  auto name = VisitAndReturnValue(statement->expression_);
  MyPrint(stream_, "\tpush ", name, "\n");
  MyPrint(stream_, "\tcall print ; joke\n");
  MyPrint(stream_, "\tpop ", name, "\n");
}

void ir_tree::AsmGenerator::PrintEpilogue() {
  MyPrint(stream_, "\tmov rsp rbp\n");
  MyPrint(stream_, "\tpop rbp\n");
  MyPrint(stream_, "\tret\n");
}

void ir_tree::AsmGenerator::PrintPrologue() {
  MyPrint(stream_, "\tpush rbp\n");
  MyPrint(stream_, "\tmov rbp rsp\n");
}

std::string ir_tree::AsmGenerator::Div(ir_tree::IRExpression* first,
                                       ir_tree::IRExpression* second,
                                       BinOperatorType type) {
  MyPrint(stream_, "\tpush rax\n");
  MyPrint(stream_, "\tpush rdx\n");
  std::string to_return;
  auto src = "rax";
  if (type == BinOperatorType::MOD) {
    src = "rdx";
  }
  if (first->GetType() == IRNodeType::Const &&
      second->GetType() == IRNodeType::Const) {
    auto const1 = dynamic_cast<ConstExpression*>(first);
    auto const2 = dynamic_cast<ConstExpression*>(second);
    Temp t;
    MyPrint(stream_, '\t', "mov ", t.ToString(), " ",
            ArithOperation(const1->Value(), const2->Value(), type), '\n');
    to_return = t.ToString();
  } else if (first->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(second);
    auto const1 = dynamic_cast<ConstExpression*>(first)->Value();
    MyPrint(stream_, '\t', "mov rax", " ", const1, '\n');
    MyPrint(stream_, "\tidiv ", name, '\n');

    MyPrint(stream_, "\tmov ", name, " ", src, "\n");
    to_return = name;
  } else if (second->GetType() == IRNodeType::Const) {
    auto name = VisitAndReturnValue(first);
    auto const1 = dynamic_cast<ConstExpression*>(second)->Value();
    MyPrint(stream_, "\tmov rax ", name, '\n');
    MyPrint(stream_, "\tmov ", name, " ", const1, "\n");
    MyPrint(stream_, "\tidiv ", name, '\n');

    MyPrint(stream_, "\tmov ", name, " ", src, "\n");
    to_return = name;
  } else {
    auto name1 = VisitAndReturnValue(first);
    auto name2 = VisitAndReturnValue(second);
    MyPrint(stream_, "\tmov rax ", name1, '\n');
    MyPrint(stream_, "\tidiv ", name2, "\n");
    MyPrint(stream_, "\tmov ", name1, " ", src, "\n");
    to_return = name1;
  }
  MyPrint(stream_, "\tpop rdx\n");
  MyPrint(stream_, "\tpop rax\n");
  return to_return;
}

ir_tree::AsmGenerator::AsmGenerator(const std::string& file,
                                    const std::string& start)
    : stream_(file) {
  MyPrint(stream_, ".intel_syntax noprefix\n");
  MyPrint(stream_, "global _start\n");
  MyPrint(stream_, "_start:\n");
  MyPrint(stream_, "\tjmp ", start, "\n");
}
