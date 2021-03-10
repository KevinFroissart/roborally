#include "../headers/board.hpp"
#include "../headers/graphe.hpp"

#include <iostream>

int main()
{
  RR::Board b("board.txt");
  b.save("/tmp/cpy.txt");

  Graphe g(b);

  for(std::pair<RR::Robot, Sommet> sommet : g.map) {
    std::cout << sommet.first.location.column 
      << " " << sommet.first.location.line  
      << " voisins: ";
      for (RR::Robot r : sommet.second.voisins) {
        std::cout << r.location.line
        << " " << r.location.column << std::endl ;
      }
  }

  return 0;
}
