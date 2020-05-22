
#include "FunctionCallVisitor.h"
#include <sources.h>
#include <iostream>
#include <algorithm>
#include <error_macro.h>
#include "objects/ObjectsSupport.cpp"
#include "types/TypesSupport.cpp"

void FunctionCallVisitor::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
    if (returned_) {
      return;
    }
  }
}

void FunctionCallVisitor::Visit(Assignment* assignment) {
  VisitAndReturnValue(assignment->expression_);
  SetValue(Symbol(assignment->variable_), last_value_set_);
}

void FunctionCallVisitor::Visit(AddExpression* add_expression) {
  auto result = VisitAndReturnValue(add_expression->first_)->ToInt() +
                VisitAndReturnValue(add_expression->second_)->ToInt();
  last_value_set_ = std::make_shared<Integer>(result);
}

void FunctionCallVisitor::Visit(MulExpression* expression) {
  auto result = VisitAndReturnValue(expression->first_)->ToInt() *
                VisitAndReturnValue(expression->second_)->ToInt();
  last_value_set_ = std::make_shared<Integer>(result);
}

void FunctionCallVisitor::Visit(DivExpression* expression) {
  auto result = VisitAndReturnValue(expression->first_)->ToInt() /
                VisitAndReturnValue(expression->second_)->ToInt();
  last_value_set_ = std::make_shared<Integer>(result);
}

void FunctionCallVisitor::Visit(SubstractExpression* expression) {
  auto result = VisitAndReturnValue(expression->first_)->ToInt() -
                VisitAndReturnValue(expression->second_)->ToInt();
  last_value_set_ = std::make_shared<Integer>(result);
}

void FunctionCallVisitor::Visit(IdentExpression* expression) {
  last_value_set_ = GetValue(Symbol(expression->name_));
}

void FunctionCallVisitor::Visit(NumExpression* expression) {
  last_value_set_ = std::make_shared<Integer>(expression->value_);
}

void FunctionCallVisitor::Visit(Program* program) {
}

void FunctionCallVisitor::Visit(PrintStatement* print) {
  std::cout << VisitAndReturnValue(print->expr_)->ToInt() << std::endl;
}

void FunctionCallVisitor::Visit(ReadStatement* read) {
  int value;
  std::cin >> value;
  last_value_set_ = std::make_shared<Integer>(value);
  SetValue(Symbol(read->GetVariableName()), last_value_set_);
}

void FunctionCallVisitor::Visit(EqualExpression* eq) {
  auto result = (VisitAndReturnValue(eq->first_)->ToInt() ==
                 VisitAndReturnValue(eq->second_)->ToInt());
  last_value_set_ = std::make_shared<BoolObject>(result);
}

void FunctionCallVisitor::Visit(LessExpression* less) {
  auto result = (VisitAndReturnValue(less->first_)->ToInt() <
                 VisitAndReturnValue(less->second_)->ToInt());
  last_value_set_ = std::make_shared<BoolObject>(result);
}

void FunctionCallVisitor::Visit(GreaterExpression* expr) {
  auto result = (VisitAndReturnValue(expr->first_)->ToInt() >
                 VisitAndReturnValue(expr->second_)->ToInt());
  last_value_set_ = std::make_shared<BoolObject>(result);
}

void FunctionCallVisitor::Visit(LessOrEqualExpression* expr) {
  auto result = (VisitAndReturnValue(expr->first_)->ToInt() <=
                 VisitAndReturnValue(expr->second_)->ToInt());
  last_value_set_ = std::make_shared<BoolObject>(result);
}

void FunctionCallVisitor::Visit(GreaterOrEqualExpression* expr) {
  auto result = (VisitAndReturnValue(expr->first_)->ToInt() >=
                 VisitAndReturnValue(expr->second_)->ToInt());
  last_value_set_ = std::make_shared<BoolObject>(result);
}

void FunctionCallVisitor::Visit(IfStatement* if_statement) {
  if (VisitAndReturnValue(if_statement->ifExpression_)->ToInt()) {
    if_statement->then_->AcceptVisitor(this);
    if (if_statement->else_ != nullptr) {
      current_children_.back()++;
    }
  } else {
    current_children_.back()++;
    if (if_statement->else_ != nullptr) {
      if_statement->else_->AcceptVisitor(this);
    }
  }
}

void FunctionCallVisitor::Visit(Scope* scope) {
  current_layer_ = current_layer_->GetChildren(current_children_.back()++);
  current_children_.push_back(0);

  frame_.BeginScope();
  table_.BeginScope();

  scope->statements_->AcceptVisitor(this);

  frame_.EndScope();
  table_.EndScope();

  current_children_.pop_back();

  current_layer_ = current_layer_->GetParent();
}

void FunctionCallVisitor::Visit(VariableDeclaration* decl) {
  table_.DeclareVariable(
      Symbol(decl->name_),
      frame_.AllocVariable(VisitAndReturnValue(decl->expression_)));
}

void FunctionCallVisitor::Visit(ModuloExpression* expression) {
  auto result = VisitAndReturnValue(expression->first_)->ToInt() %
                VisitAndReturnValue(expression->second_)->ToInt();
  last_value_set_ = std::make_shared<Integer>(result);
}

void FunctionCallVisitor::Visit(WhileStatement* statement) {
  while (true) {
    auto res = VisitAndReturnValue(statement->check_expression_)->ToInt();
    if (!res) {
      break;
    }
    Visit(statement->scope_);
    if (returned_) {
      return;
    }
    current_children_.back()--;
  }
  current_children_.back()++;
}

void FunctionCallVisitor::Visit(CallArgumentList* list) {
}

void FunctionCallVisitor::Visit(ClassMethod* function) {
  function->arguments_->AcceptVisitor(this);
  function->statements_->AcceptVisitor(this);
}

std::shared_ptr<BaseObject> FunctionCallVisitor::GetValue(
    const Symbol& symbol) {
  if (!table_.HasVariable(symbol)) {
    return current_class_->GetValue(symbol);
  }
  return frame_.GetValue(table_.GetIndex(symbol));
}

void FunctionCallVisitor::SetValue(const Symbol& symb,
                                   std::shared_ptr<BaseObject> value) {
  if (!table_.HasVariable(symb)) {
    current_class_->SetValue(symb, value);
  } else {
    frame_.SetValue(table_.GetIndex(symb), value);
  }
}

void FunctionCallVisitor::Visit(MethodArgumentList* list) {
  int index = -1;
  for (auto argument : list->names_) {
    table_.DeclareVariable(Symbol(argument), index);
    --index;
  }
}

void FunctionCallVisitor::Visit(ClassBody*) {
}

FunctionCallVisitor::FunctionCallVisitor(
    Frame frame, FunctionMap& functions, ScopeLayerTree& tree,
    ScopeLayer* layer, std::shared_ptr<ClassObject> current_class,
    ClassMap& c_map)
    : frame_(std::move(frame)),
      functions_(functions),
      tree_(tree),
      current_children_({0}),
      current_layer_(layer),
      current_class_(current_class),
      class_map_(c_map) {
}

void FunctionCallVisitor::ExecuteCode(ClassMethod* func) {
  Visit(func);
}

void FunctionCallVisitor::Visit(MethodCallExpression* expression) {
  std::vector<std::shared_ptr<BaseObject>> args;
  for (auto expr : expression->arguments_->arguments_) {
    args.push_back(VisitAndReturnValue(expr));
  }

  Frame frame(args);
  frame.SetParent(&frame_);

  auto expr_obj = VisitAndReturnValue(expression->expression_);

  std::shared_ptr<ClassObject> class_obj =
      std::dynamic_pointer_cast<ClassObject>(expr_obj);

  if (class_obj == nullptr) {
    throw std::runtime_error("Not a class type");
  }

  auto call_function =
      functions_.Get(Symbol(class_obj->GetType() + "::" + expression->name_));

  if (call_function == nullptr) {
    throw std::runtime_error("Class \"" + class_obj->GetType() +
                             "\" has no \"" + expression->name_ + "\" method");
  }

  if (call_function->arguments_->names_.size() != args.size()) {
    ERROR(std::to_string(call_function->arguments_->names_.size()) +
          " Arguments expected, but " + std::to_string(args.size()) +
          " were given\n");
  }

  FunctionCallVisitor visitor(
      std::move(frame), functions_, tree_,
      tree_.Get(Symbol(class_obj->GetType() + "::" + expression->name_)),
      class_obj, class_map_);
  visitor.ExecuteCode(call_function);
  last_value_set_ = frame_.GetReturnValue();
}

void FunctionCallVisitor::Visit(ReturnStatement* statement) {
  if (statement->expression_ != nullptr) {
    VisitAndReturnValue(statement->expression_);
    if (frame_.HasParent()) {
      frame_.SetParentReturnValue(last_value_set_);
    }
  }
  returned_ = true;
}

void FunctionCallVisitor::Visit(MethodCallStmt* statement) {
  statement->expression_->AcceptVisitor(this);
}

void FunctionCallVisitor::Visit(Class*) {
}

void FunctionCallVisitor::Visit(ClassList*) {
}

void FunctionCallVisitor::Visit(ClassField*) {
}

void FunctionCallVisitor::Visit(ClassMain*) {
}

void FunctionCallVisitor::Visit(ThisExpression*) {
  last_value_set_ = current_class_;
}

void FunctionCallVisitor::Visit(NewExpression* expression) {
  last_value_set_ = InitClass(class_map_.GetClass(Symbol(expression->type_)));
}

std::shared_ptr<ClassObject> FunctionCallVisitor::InitClass(Class* cl) {
  std::shared_ptr<ClassObject> result =
      std::make_shared<ClassObject>(cl->name_);
  for (auto field : cl->body_->fields_) {
    if (IsPrimitiveType(field->type_)) {
      result->CreateField(Symbol(field->name_), CreateObjectPtr(field->name_));
    } else {
      result->CreateField(Symbol(field->name_),
                          InitClass(class_map_.GetClass(Symbol(field->type_))));
    }
  }
  return result;
}
