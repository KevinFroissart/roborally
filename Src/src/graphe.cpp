#include <queue>
#include <set>

#include "../headers/graphe.hpp"

using namespace std;

/**
 * Constructeur par défaut avec une liste vide
 */
Graphe::Graphe()
{
    map = std::map<RR::Robot, Sommet>();
}

/**
 * Construit un graphe a partir d'un robot et d'un plateau
 */
Graphe::Graphe(RR::Board board)
{
    RR::Robot robot;
    // itere sur toutes les cases
    for (std::pair<RR::Location, RR::Board::TileType> tile : board.tiles)
    {
        robot.location.line = tile.first.line;
        robot.location.column = tile.first.column;
        //std::cout << "iterating on position " << r.location.column
        //<< " " << r.location.line << " ";

        for (RR::Robot::Status direction : directions)
        {
            //pour chaque direction, faire jouer le robot
            robot.status = direction;
            //std::cout << r.StatusToString() << std::endl;
            std::vector<RR::Robot> voisins;
            for (RR::Robot::Move move : moves)
            {
                RR::Robot copie = robot;
                board.play(copie, move);
                if (copie.status != RR::Robot::Status::DEAD)
                {
                    //ajoute la position a la liste des voisins
                    voisins.push_back(copie);
                }
            }
            Sommet sommet(robot, voisins); //construit le sommet a inserer
            map.insert(std::pair<RR::Robot, Sommet>(robot, sommet));
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
    for (std::pair<const RR::Robot, Sommet> elem : map)
    {
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
            Sommet sommet = start;
            std::map<RR::Robot, Sommet>::iterator itr;
            if ((itr = map.find(robot)) != map.end())
                sommet = itr->second;
            else
                break; // à modifier
            if (sommet.parcours > courant.parcours + 1)
            {
                sommet.visite = true;
                sommet.parent = &courant;
                sommet.parcours = courant.parcours + 1;
                pq.push(sommet);
            }
        }
    }
}