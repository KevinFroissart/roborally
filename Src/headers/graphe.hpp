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
    Graphe(RR::Board b);
    std::string ToString();
    std::unordered_map<RR::Robot, Sommet, RR::RobotHash> map;
    void parcours(RR::Robot start, RR::Robot end);
    //std::string plus_court_chemin(RR::Robot target);

private:
    const std::array<RR::Robot::Move, 7> moves = {
        RR::Robot::Move::FORWARD_1,
        RR::Robot::Move::FORWARD_2,
        RR::Robot::Move::FORWARD_3,
        RR::Robot::Move::BACKWARD_1,
        RR::Robot::Move::TURN_LEFT,
        RR::Robot::Move::TURN_RIGHT,
        RR::Robot::Move::U_TURN};

    const std::array<RR::Robot::Status, 4> directions = {
        RR::Robot::Status::EAST,
        RR::Robot::Status::NORTH,
        RR::Robot::Status::WEST,
        RR::Robot::Status::SOUTH,
    };
};

bool operator<(const Sommet &s1, const Sommet &s2);

struct PQitem {
    int distance;
    RR::Robot pos;

    PQitem(int distance, RR::Robot pos);
};

#endif