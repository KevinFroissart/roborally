#include "../headers/joueurArtificiel.hpp"
#include <time.h>
#include <stdlib.h>

std::vector<RR::Robot::Move> JoueurArtificiel::tirage(int nbCarte)
{
    std::vector<RR::Robot::Move> tirage;
    srand(time(NULL));
    for (int i = 0; i < nbCarte; i++)
        tirage.push_back((RR::Robot::Move)(rand() % 7));
    return tirage;
}

void JoueurArtificiel::method(Graphe graphe, RR::Robot robot, std::vector<RR::Robot::Move> actions)
{
}