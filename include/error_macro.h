
#ifndef MYCOMPILLER_INCLUDE_ERROR_MACRO_H_
#define MYCOMPILLER_INCLUDE_ERROR_MACRO_H_
#include <iostream>

#define ERROR(msg, node)                                       \
  {                                                            \
    std::cerr << "line:" << node->loc.begin.line << " column:" \
              << node->loc.begin.column << "\n"                \
              << msg << std::endl;                             \
    exit(1);                                                   \
  }

#endif  // MYCOMPILLER_INCLUDE_ERROR_MACRO_H_
