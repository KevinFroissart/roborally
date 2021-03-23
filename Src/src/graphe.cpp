#include <queue>
#include <set>

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
        //std::cout << "iterating on position " << r.location.column 
        //<< " " << r.location.line << " ";

        for(RR::Robot::Status dir : directions) {        
            //pour chaque direction, faire jouer le robot
            r.status = dir;
            //std::cout << r.StatusToString() << std::endl;
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
}

bool operator<(const Sommet &s1, const Sommet &s2)
{
    return s1.parcours < s2.parcours;
}

void Graphe::parcours(Sommet start)
{
    //std::multiset<Sommet> pq;
    std::priority_queue<Sommet> pq;
    Sommet courant = start;
    
    //initialiser tous les sommets a nullptr, +infini
    //initialiser le sommet de depart a lui-même, 0
    for (std::pair<const RR::Robot, Sommet> elem : map) {
        elem.second.parcours = INT16_MAX;
        elem.second.parent = nullptr;
    }

    courant.parcours = 0;
    courant.parent = nullptr;

    pq.push(start);
    while (pq.size() != 0)
    {
        courant = pq.top(); //courant -> elt de la file avec prio minimale
        pq.pop();
        for (RR::Robot robot : courant.voisins)
        {
            //le poids de l'arrete c'est le nombre de sauts necessaires pour aller du point courant 
            //a son voisin. Toujours 1 ici
            //peut-être faire la conversion robot->sommet ici
            Sommet s = start;
            std::map<RR::Robot, Sommet>::iterator itr;
            if ((itr = map.find(robot)) != map.end())
                s = itr->second;
            else
                break;
            if (s.parcours > courant.parcours + 1)
            {
                s.visite = true;
                s.parent = &courant;
                s.parcours = courant.parcours + 1;
                pq.push(s);
            }
            // recherche dans une map ? Clé : un robot Value: le sommet
        }
    }
    //courant = chemin le plus cours (normalement inchallah)
    //on utilise pas graphe ? à voir pk et où est le pb
}