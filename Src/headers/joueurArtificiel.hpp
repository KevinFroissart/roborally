#ifndef JOUEURARTIFICIEL_HPP_
#define JOUEURARTIFICIEL_HPP_
#include <iostream>
#include <vector>

#include "board.hpp"

class JoueurArtificiel
{
public:
    std::vector<RR::Robot::Move> tirage(int nbCarte);

private:
};

#endif