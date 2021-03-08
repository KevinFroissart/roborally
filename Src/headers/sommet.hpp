#ifndef SOMMET_HPP_
#define SOMMET_HPP_
#include <iostream>
#include <vector>

#include "sommet.hpp"
#include "board.hpp"

class Sommet
{
public:
    RR::Location location;
    RR::RobotStatus direction;
    vector<Sommet> voisin;

    Sommet(RR::Location, RR::Robot::Status, std::vector<Sommet>);

private:
};

#endif