#include "../headers/sommet.hpp"

Sommet::Sommet() {
    visite = false;
}

Sommet::Sommet(RR::Robot r, std::vector<RR::Robot> sommets) : robot(r), voisins(sommets)
{
    visite = false;
}