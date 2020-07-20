
#ifndef MYCOMPILLER_PRINT_H
#define MYCOMPILLER_PRINT_H

template <typename Stream>
inline void MyPrint(Stream& stream) {
}

template <typename Stream, typename Head, typename ... Tail>
inline void MyPrint(Stream& stream, const Head& head, const Tail&... t) {
  stream << head;
  MyPrint(stream, t...);
}

#endif  // MYCOMPILLER_PRINT_H
