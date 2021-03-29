#ifndef SOMMET_HPP_
#define SOMMET_HPP_
#include <iostream>
#include <map>
#include <vector>

#include "board.hpp"

class Sommet
{
public:
    RR::Robot robot;
    std::vector<RR::Robot> voisins;
    bool visite;
    //RR::Robot::Move move;

    Sommet();
    Sommet(RR::Robot r, std::vector<RR::Robot> sommets);

private:
};

#endif