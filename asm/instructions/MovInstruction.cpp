
#include "MovInstruction.h"


MovInstruction::MovInstruction(const std::string& destination,
                               const std::string& source, int dst_offset,
                               int src_offset, bool dst_mem, bool src_mem)
    : AsmInstruction(AsmType::Mov),
      destination_(destination),
      source_(source),
      dst_offset_(dst_offset),
      src_offset_(src_offset),
      dst_mem_(dst_mem),
      src_mem_(src_mem) {
  ChangeRegName(destination_);
  ChangeRegName(source_);
}


void MovInstruction::Print(std::ostream& stream) {
  if (!dst_mem_ && !src_mem_) {
    MyPrint(stream, "\tmov ", destination_, ", ", source_, "\n");
  }
  if (dst_mem_) {
    std::string offset;
    if (dst_offset_ != 0) {
      auto sign = " + ";
      int factor = 1;
      if (dst_offset_ < 0) {
        factor = -1;
        sign = " - ";
      }
      offset = sign + std::to_string(factor * dst_offset_);
    }
    MyPrint(stream, "\tmov [", destination_, offset, "], ", source_, "\n");
  }
  if (src_mem_) {
    std::string offset;
    if (src_offset_ != 0) {
      auto sign = " + ";
      int factor = 1;
      if (src_offset_ < 0) {
        factor = -1;
        sign = " - ";
      }
      offset = sign + std::to_string(src_offset_ * factor);
    }
    MyPrint(stream, "\tmov ", destination_, ", [", source_, offset, "]\n");
  }
}

std::vector<std::string> MovInstruction::GetDef() {
  return {destination_};
}

std::vector<std::string> MovInstruction::GetUse() {
  if (CheckConst(source_)) {
    return {};
  }
  return {source_};
}

void MovInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
  ChangeRegToPhysical(destination_, support, change);
  if (!CheckConst(source_)) {
    ChangeRegToPhysical(source_, support, change);
  }
}
