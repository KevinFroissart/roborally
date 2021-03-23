#include "../headers/board.hpp"
#include "../headers/graphe.hpp"

#include <iostream>
#include <string>

std::string get_status(RR::Robot::Status s)
{
  return s == RR::Robot::Status::EAST    ? "EAST"
         : s == RR::Robot::Status::NORTH ? "NORTH"
         : s == RR::Robot::Status::WEST  ? "WEST"
                                         : "SOUTH";
}

int main()
{
  RR::Board b("board.txt");
  b.save("/tmp/cpy.txt");

  Graphe g(b);

  std::cout << "ENTITY : Line:Column - STATUS" << std::endl;
  std::map<RR::Robot, Sommet>::iterator itr = g.map.begin();
  while (itr != g.map.end())
  {
    std::cout << "Sommet : " << itr->first.location.line << ":" << itr->first.location.column << " - " << get_status(itr->first.status) << std::endl;
    for (std::vector<RR::Robot>::iterator it = itr->second.voisins.begin(); it != itr->second.voisins.end(); ++it)
    {
      std::cout << "   Voisins : " << it->location.line << ":" << it->location.column << " - " << get_status(it->status) << std::endl;
    }
    itr++;
  }

  return 0;
}
