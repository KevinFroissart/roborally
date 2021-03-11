#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_
#include <iostream>

#include "graphe.hpp"
#include "sommet.hpp"

class Dijkstra
{
public:
    void parcours(Graphe graphe, Sommet start, std::priority_queue<Sommet> pq);

private:
};

#endif