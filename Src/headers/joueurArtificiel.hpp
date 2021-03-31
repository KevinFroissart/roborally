#ifndef JOUEURARTIFICIEL_HPP_
#define JOUEURARTIFICIEL_HPP_
#include <iostream>
#include <vector>

#include "board.hpp"
#include "graphe.hpp"
class JoueurArtificiel
{
public:
    std::vector<RR::Robot::Move> tirage(int nbCarte);
    void method(Graphe graphe, RR::Robot robot, std::vector<RR::Robot::Move> actions);

private:
};

#endif