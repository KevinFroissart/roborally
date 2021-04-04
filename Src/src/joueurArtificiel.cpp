#include "../headers/joueurArtificiel.hpp"
#include <time.h>
#include <stdlib.h>

JoueurArtificiel::JoueurArtificiel(RR::Robot position)
{
    this->position = position;
}

std::vector<RR::Robot::Move> JoueurArtificiel::tirage(int nbCarte)
{
    std::vector<RR::Robot::Move> tirage;
    srand(time(NULL));
    for (int i = 0; i < nbCarte; i++)
        tirage.push_back((RR::Robot::Move)(rand() % 7));
    return tirage;
}

std::vector<RR::Robot::Move> JoueurArtificiel::JouerTour(std::vector<RR::Robot::Move> tirage, RR::Board board)
{
    MTC mtc;
    mtc.etape = 0;
    mtc.poids = 0;
    mtc.robot = this->position;
    mtc.tirage = tirage;
    //mtc.fils.push_back(mtc);

    std::queue<MTC> queue;
    queue.push(mtc);

    int possibilite = 0;

    while (!queue.empty())
    {

        MTC courant = queue.front();
        queue.pop();
        for (unsigned int i = 0; i < courant.tirage.size(); i++) // pour chaque move possible du MTC courant
        {

            RR::Robot copie = courant.robot;
            board.play(copie, courant.tirage.at(i)); // on essaie de jouer le coup
            if (copie.status != RR::Robot::Status::DEAD)
            {
                // si le coup passe, on assigne la nouvelle position au fils du MTC courant
                MTC tmp;
                tmp.etape = courant.etape + 1;
                tmp.poids = courant.poids + 1;
                tmp.robot = copie;
                tmp.pred = {courant.robot, courant.tirage.at(i)};
                tmp.coups = courant.coups;
                tmp.coups.push_back(courant.tirage.at(i));
                tmp.tirage = courant.tirage;
                tmp.tirage.erase(tmp.tirage.begin() + i);
                courant.fils.push_back(tmp);

                std::cout << "\nMTC\netape: " << tmp.etape
                          << "\npoids: " << tmp.poids
                          << "\nposition: " << tmp.robot.location.line << ":" << tmp.robot.location.column
                          << "\ncoup: " << RR::MovesToString(courant.tirage.at(i))
                          << "\ntaille tirage: " << tmp.tirage.size()
                          << "\ntaille coups: " << tmp.coups.size()
                          << "\nnb passage: " << ++possibilite
                          << "\n  |\n";

                if (tmp.tirage.size() >= 5)
                {
                    queue.push(tmp); // on ajoute le fils à la file pour qu'il soit traité plus tard
                    std::cout << "taille queue: " << queue.size() << std::endl
                              << std::endl;
                }
            }
        }
        std::cout << "ça boucle? " << std::endl;
    }

    std::cout << possibilite << std::endl;
    return tirage;
}