#include "board.hpp"

#include <iostream>

int main() {
  RR::Board b("board.txt") ;
  b.save("/tmp/cpy.txt") ;

  return 0 ;
}
