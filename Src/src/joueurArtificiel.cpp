#include "../headers/joueurArtificiel.hpp"
#include <time.h>
#include <stdlib.h>

std::vector<RR::Robot::Move> JoueurArtificiel::tirage(int nbCarte)
{
    std::vector<RR::Robot::Move> tirage;
    srand(time(NULL));
    for (int i = 0; i < nbCarte; i++)
    {
        int random = rand() % 7 + 1;
        switch (random)
        {
        case 1:
            tirage.push_back(RR::Robot::Move::BACKWARD_1);
            break;
        case 2:
            tirage.push_back(RR::Robot::Move::FORWARD_1);
            break;
        case 3:
            tirage.push_back(RR::Robot::Move::FORWARD_2);
            break;
        case 4:
            tirage.push_back(RR::Robot::Move::FORWARD_3);
            break;
        case 5:
            tirage.push_back(RR::Robot::Move::TURN_LEFT);
            break;
        case 6:
            tirage.push_back(RR::Robot::Move::TURN_RIGHT);
            break;
        case 7:
            tirage.push_back(RR::Robot::Move::U_TURN);
            break;
        }
    }
    return tirage;
}