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

std::string visted(bool s)
{
  return s ? "VISTED" : "NOT VISITED";
}

int main()
{
  RR::Board b("board.txt");
  b.save("/tmp/cpy.txt");

  Graphe g(b);
  std::map<RR::Robot, Sommet>::iterator itr_map;

  RR::Robot start;
  start.location.line = 0;
  start.location.column = 1;
  start.status = RR::Robot::Status::NORTH;

  if ((itr_map = g.map.find(start)) != g.map.end())
    g.parcours(itr_map->second);

  std::cout << "\n\nParcous de la map du graphe" << std::endl;
  for (itr_map = g.map.begin(); itr_map != g.map.end(); itr_map++)
  {
    std::cout << "Sommet :"
              << itr_map->second.robot.location.line << ":"
              << itr_map->second.robot.location.column << " - "
              << get_status(itr_map->second.robot.status) << " - "
              << visted(itr_map->second.visite) << " - "
              << itr_map->second.parcours << std::endl;
  }

  RR::Robot r;
  r.location.line = 2;
  r.location.column = 2;
  r.status = RR::Robot::Status::EAST;

  if ((itr_map = g.map.find(r)) != g.map.end())
    g.plus_court_chemin(&itr_map->second);

  /*int nb = 0;
  std::cout << "ENTITY : Line:Column - STATUS" << std::endl;
  std::map<RR::Robot, Sommet>::iterator itr = g.map.begin();
  while (itr != g.map.end())
  {
    nb++;
    std::cout << "Sommet : " << itr->first.location.line << ":" << itr->first.location.column << " - " << get_status(itr->first.status) << std::endl;
    for (std::vector<RR::Robot>::iterator it = itr->second.voisins.begin(); it != itr->second.voisins.end(); ++it)
    {
      std::cout << "   Voisins : " << it->location.line << ":" << it->location.column << " - " << get_status(it->status) << std::endl;
    }
    itr++;
  }
  std::cout << nb << std::endl;*/
  return 0;
}
