#include "../headers/sommet.hpp"

Sommet::Sommet() {
    visite = false;
}

Sommet::Sommet(RR::Robot r, std::vector<std::pair<RR::Robot, RR::Robot::Move>> sommets) : robot(r), voisins(sommets)
{
    visite = false;
}