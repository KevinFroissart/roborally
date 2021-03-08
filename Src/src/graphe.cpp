#include <queue>

#include "graphe.hpp"
#include "board.hpp"

using namespace std;

/**
 * Constructeur par défaut avec une liste vide
 */
Graphe::Graphe() {
    map = std::map<RR::Location, Sommet>();
}

/**
 * Construit un graphe a partir d'un robot et d'un plateau
 */
Graphe::Graphe(RR::Robot r, RR::Board b) {
    std::queue<RR::Robot> aTraiter;
    aTraiter.push(r);

    RR::Robot r();
    while(!aTraiter.empty()) {
        r = aTraiter.front();
        aTraiter.pop();
        std::vector<Sommet> voisins;

        //pour chaque direction, faire jouer le robot
        for(RR::Robot::Move move : moves) {
            RR::Robot copie = r;
            b.play(copie, move);
            if (copie.status != RR::Robot::Status::DEAD) {
                // ajouter la cible à la liste des voisins
                //TODO modifier la liste de voisins? Si les voisins sont des sommets on passe sur du recursif,
                // complexite +++++++++++++
                //Sommet temp = Sommet(copie.location, copie.status, )
                
                aTraiter.push(copie);
            }
        }
        Sommet s = Sommet(r.location, r.status, voisins);
        map.insert(std::pair<RR::Location, Sommet>(r.location, s));
    }
}


/*entrées:
- R robot
- J jeu
structures:
- G graphe
- P pile
variables:
- C robot
algo:
- P <- R
- tant que P non vide:
  - P -> R
  - G <- sommet R
  - pour chaque direction D:
    - C <- clone de R
    - J.play(C, D)
    - P <- C
    - G <- arrête (R, D, C)*/