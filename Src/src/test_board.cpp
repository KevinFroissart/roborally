#include "../headers/board.hpp"
#include "../headers/graphe.hpp"

#include <iostream>
#include <string>

int main()
{
  RR::Board b("board.txt");
  b.save("/tmp/cpy.txt");

  Graphe g(b);
  std::unordered_map<RR::Robot, Sommet, RR::RobotHash>::iterator itr_map;

  RR::Robot start;
  start.location.line = 2;
  start.location.column = 3;
  start.status = RR::Robot::Status::WEST;

  RR::Robot end;
  end.location.line = 3;
  end.location.column = 3;
  end.status = RR::Robot::Status::EAST;

  g.parcours(start, end);

  return 0;
}