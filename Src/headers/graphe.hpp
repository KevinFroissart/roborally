#ifndef GRAPHE_HPP_
#define GRAPHE_HPP_
#include <map>
#include <iostream>

#include "sommet.hpp"
#include "board.hpp"

class Graphe
{
public:
    Graphe();
    Graphe(RR::Robot r, RR::Board b);
    std::string ToString();
private:
    std::map<RR::Location, Sommet> map;

    std::vector<RR::Robot::Move> moves = {
        RR::Robot::Move::FORWARD_1,
        RR::Robot::Move::FORWARD_2,
        RR::Robot::Move::FORWARD_3,
        RR::Robot::Move::BACKWARD_1,
        RR::Robot::Move::TURN_LEFT,
        RR::Robot::Move::TURN_RIGHT,
        RR::Robot::Move::U_TURN
    };
};

#endif