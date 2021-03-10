#include "../headers/sommet.hpp"

Sommet::Sommet(RR::Robot r, std::vector<RR::Robot> voisin)
{
    robot = r;
    voisin = voisin;
}