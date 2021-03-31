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
    std::vector<std::pair<RR::Robot, RR::Robot::Move>> voisins;
    bool visite;

    Sommet();
    Sommet(RR::Robot r, std::vector<std::pair<RR::Robot, RR::Robot::Move>> sommets);

private:
};

#endif