#ifndef JOUEURARTIFICIEL_HPP_
#define JOUEURARTIFICIEL_HPP_
#include <iostream>
#include <vector>

#include "board.hpp"
#include "graphe.hpp"
class JoueurArtificiel
{
public:
    RR::Robot position;
    RR::Robot objectif;
    const int MAX_CARTES_MAIN;

    JoueurArtificiel(RR::Robot position);
    std::vector<RR::Robot::Move> tirage(int nbCarte);
    std::vector<RR::Robot::Move> JouerTour(std::vector<RR::Robot::Move> tirage, RR::Board board);

private:
};

#endif