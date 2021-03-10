#ifndef SOMMET_HPP_
#define SOMMET_HPP_
#include <iostream>
#include <map>
#include <vector>

#include "board.hpp"

class Sommet
{
public:
    RR::Robot position;
    std::vector<RR::Robot> voisins;

    Sommet(RR::Robot r, std::vector<RR::Robot> sommets);

private:
};

#endif