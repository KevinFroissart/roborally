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
  start.location.line = 0;
  start.location.column = 1;
  start.status = RR::Robot::Status::WEST;

  RR::Robot end;
  end.location.line = 3;
  end.location.column = 3;
  end.status = RR::Robot::Status::EAST;

  g.parcours(start, end);

  JoueurArtificiel ja(start, end);

  std::vector<RR::Robot::Move> tirage = ja.tirage(9);

  /*for (unsigned int i = 0; i < tirage.size(); i++)
  {
    std::cout << RR::MovesToString(tirage[i]) << std::endl;
  }*/

  std::vector<RR::Robot::Move> coups = ja.JouerTour(tirage, b, g);
  std::cout << "résultat du tour: " << std::endl;
  for(RR::Robot::Move coup : coups) {
    std::cout << RR::MovesToString(coup) << std::endl;
  }

  std::cout << std::endl;

  return 0;
}