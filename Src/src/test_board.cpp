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
  start.location.line = 0;
  start.location.column = 1;
  start.status = RR::Robot::Status::EAST;

  std::cout << "\n\nParcous de la map du graphe" << std::endl;
  for (itr_map = g.map.begin(); itr_map != g.map.end(); itr_map++)
  {
    std::cout << "Sommet : "
              << itr_map->second.robot.location.line << ":"
              << itr_map->second.robot.location.column << " - "
              << itr_map->second.robot.StatusToString() << std::endl;
  }

  printf("\n\n");

  RR::Robot r;
  r.location.line = 3;
  r.location.column = 4;
  r.status = RR::Robot::Status::EAST;

  g.parcours(start, r);

  return 0;
}