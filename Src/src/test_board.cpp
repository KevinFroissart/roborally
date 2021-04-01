#include "../headers/board.hpp"
#include "../headers/graphe.hpp"
#include "../headers/joueurArtificiel.hpp"

#include <iostream>
#include <string>

int main()
{
  RR::Board b("board.txt");
  b.save("/tmp/cpy.txt");

  Graphe g(b);

  RR::Robot start;
  start.location.line = 2;
  start.location.column = 3;
  start.status = RR::Robot::Status::WEST;

  RR::Robot end;
  end.location.line = 3;
  end.location.column = 3;
  end.status = RR::Robot::Status::EAST;

  g.parcours(start, end);

  JoueurArtificiel ja;

  std::vector<RR::Robot::Move> tirage = ja.tirage(9);

  std::cout << std::endl;

  for (int i = 0; i < tirage.size(); i++)
  {
    std::cout << RR::MovesToString(tirage[i]) << std::endl;
  }

  return 0;
}