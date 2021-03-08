#include "sommet.hpp"

Sommet::Sommet(RR::Location l, RR::Robot::Status d, std::vector<Sommet> sommets) {
    location = l;
    direction = d;
    voisin = sommets;
}