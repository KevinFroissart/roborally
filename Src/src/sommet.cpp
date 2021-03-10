#include "../headers/sommet.hpp"

Sommet::Sommet(RR::Robot r, std::vector<RR::Robot> sommets) {
    position = r;
    voisins = sommets;
}