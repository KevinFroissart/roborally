#include "../headers/joueurArtificiel.hpp"
#include <time.h>
#include <stdlib.h>

JoueurArtificiel::JoueurArtificiel(RR::Robot position) {
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

std::vector<RR::Robot::Move> JoueurArtificiel::JouerTour(std::vector<RR::Robot::Move> tirage, RR::Board board) {
    RR::Robot posDepart = this->position;
    std::vector<RR::Robot::Move> meilleurChoix;

    //avec notre tirage, on cree un arbre à 9 branches representant les coups possibles. 
    for(RR::Robot::Move move : tirage) {
        //L'arbre aura une profondeur de 5 (on joue 5 coups par tour)
        for (int i = 0; i < MAX_CARTES_MAIN; i++) {
            //boucle sur toutes les cartes restantes que l'on peut jouer
            //chaque branche aura un enfant de moins que la precedente (carte deja jouee)
            board.play(posDepart, move);
            //On va parcourir l'arbre afin de trouver quelle branche nous permet d'arriver soit a la case 
            //objectif, soit a la case la plus proche de l'objectif (que l'on determine via un appel du plus court chemin)
            if (posDepart.status == RR::Robot::Status::DEAD) 
                break;
            if (posDepart == objectif) {
                //retourner la serie de coup qui a permis d'arriver a lo'bjectif, plus n'importes quelles autres
                // si il y a moins de 5 coups
            }

        }
        
    }

    return meilleurChoix;
}