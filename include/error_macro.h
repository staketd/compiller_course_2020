
#ifndef MYCOMPILLER_INCLUDE_ERROR_MACRO_H_
#define MYCOMPILLER_INCLUDE_ERROR_MACRO_H_
#include <iostream>

#define ERROR(msg) {std::cerr << msg << std::endl; exit(1);}

#endif  // MYCOMPILLER_INCLUDE_ERROR_MACRO_H_
