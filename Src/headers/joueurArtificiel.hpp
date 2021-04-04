#ifndef JOUEURARTIFICIEL_HPP_
#define JOUEURARTIFICIEL_HPP_
#include <iostream>
#include <vector>
#include <queue>

#include "board.hpp"
#include "graphe.hpp"
class JoueurArtificiel
{
public:
    RR::Robot position;
    RR::Robot objectif;
    const int NB_COUPS = 5;

    JoueurArtificiel(RR::Robot position);
    std::vector<RR::Robot::Move> tirage(int nbCarte);
    std::vector<RR::Robot::Move> JouerTour(std::vector<RR::Robot::Move> tirage, RR::Board board);

private:
    struct MTC
    {
        int etape;
        int poids;
        RR::Robot robot;
        std::pair<RR::Robot, RR::Robot::Move> pred;
        std::vector<MTC> fils;
        std::vector<RR::Robot::Move> tirage;
        std::vector<RR::Robot::Move> coups;
    };

    void recurs(MTC mtc, RR::Board board, std::queue<MTC> *queue);
};

#endif