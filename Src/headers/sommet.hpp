#ifndef SOMMET_HPP_
#define SOMMET_HPP_
#include <iostream>
#include <vector>

#include "sommet.hpp"
#include "board.hpp"

class Sommet
{
public:
    RR::Robot robot;
    std::vector<RR::Robot> voisin;

    Sommet(RR::Robot, std::vector<RR::Robot>);

private:
};

#endif