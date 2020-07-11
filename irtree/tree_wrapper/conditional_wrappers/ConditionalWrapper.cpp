
#include "ConditionalWrapper.h"
#include <macros.h>
#include <TempExpression.h>
#include <Temp.h>
#include <EseqExpression.h>
#include <SeqStatement.h>
#include <MoveStatement.h>
#include <ConstExpression.h>
#include <LabelStatement.h>

ir_tree::IRExpression* ir_tree::ConditionalWrapper::ToExpression() {
  auto* temp_expr = new TempExpression(Temp());
  Label true_label;
  Label false_label;
  return new EseqExpression(
      new SeqStatement(
          new MoveStatement(temp_expr, new ConstExpression(1)),
          new SeqStatement(
              ToConditional(true_label, false_label),
              new SeqStatement(
                  new LabelStatement(false_label),
                  new SeqStatement(
                      new MoveStatement(temp_expr, new ConstExpression(0)),
                      new LabelStatement(true_label)
                      )
                  )
              )
          ),
        temp_expr
      );
}

ir_tree::IRStatement* ir_tree::ConditionalWrapper::ToStatement() {
  return nullptr;
}
