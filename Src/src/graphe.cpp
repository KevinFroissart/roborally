#include <queue>

#include "../headers/graphe.hpp"

using namespace std;

/**
 * Constructeur par défaut avec une liste vide
 */
Graphe::Graphe() {
    map = std::map<RR::Robot, Sommet>();
}

/**
 * Construit un graphe a partir d'un robot et d'un plateau
 */
Graphe::Graphe(RR::Board b) {
    RR::Robot r;
    // itere sur toutes les cases
    for(std::pair<RR::Location, RR::Board::TileType> tile : b.tiles) {
        r.location.column = tile.first.column;
        r.location.line = tile.first.line;

        for(RR::Robot::Status dir : directions) {        
            //pour chaque direction, faire jouer le robot
            r.status = dir;
            std::vector<RR::Robot> voisins;
            for(RR::Robot::Move move : moves) {
                b.play(r, move);
                if (r.status != RR::Robot::Status::DEAD) {
                    //ajoute la position a la liste des voisins
                    voisins.push_back(r);
                }
            }
            Sommet s(r, voisins); //construit le sommet a inserer
            map.insert(std::pair<RR::Robot, Sommet>(r, s));
        }
    }

    /*while(!aTraiter.empty()) {
        r = aTraiter.front();
        aTraiter.pop();
        std::vector<RR::Robot> voisins;

        //pour chaque direction, faire jouer le robot
        for(RR::Robot::Move move : moves) {
            vector<RR::Robot> voisins;

            RR::Robot copie = r;
            b.play(copie, move);
            if (copie.status != RR::Robot::Status::DEAD) {
                //ajoute la position a la liste des voisins
                voisins.push_back(copie);
                aTraiter.push(copie);
            }
        }

        Sommet s(r, voisins); //construit le sommet a inserer
        map.insert(std::pair<RR::Robot, Sommet>(r, s));
    }*/
}

/* -- TENTER D'IMPLEMENTER AVEC CETTE BOUCLE AU LIEU DU PARCOURS --
*/