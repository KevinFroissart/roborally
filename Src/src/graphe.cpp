#include <queue>
#include <set>
#include "../headers/graphe.hpp"

using namespace std;

/**
 * Constructeur par défaut avec une liste vide
 */
Graphe::Graphe()
{
    map = std::unordered_map<RR::Robot, Sommet, RR::RobotHash>();
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

        for (RR::Robot::Status direction : directions)
        {
            //pour chaque direction, faire jouer le robot
            robot.status = direction;
            std::vector<std::pair<RR::Robot, RR::Robot::Move>> voisins;
            for (RR::Robot::Move move : moves)
            {
                RR::Robot copie = robot;
                board.play(copie, move);

                if (copie.status != RR::Robot::Status::DEAD)
                {
                    //ajoute la position a la liste des voisins
                    voisins.push_back(std::pair<RR::Robot, RR::Robot::Move>(copie, move));
                }
            }
            Sommet sommet(robot, voisins); //construit le sommet a inserer
            map.insert(std::pair<RR::Robot, Sommet>(robot, sommet));
        }
    }
}

std::string printRobotData(RR::Robot r, std::unordered_map<RR::Robot, int, RR::RobotHash> poids)
{
    return "Sommet " + std::to_string(poids[r]) + ": " +
           std::to_string(r.location.line) + ":" +
           std::to_string(r.location.column) + " - " +
           r.StatusToString() + " - ";
}

bool operator<(const PQitem &s1, const PQitem &s2)
{
    return s1.distance < s2.distance;
}

PQitem::PQitem(int distance, RR::Robot robot)
{
    this->distance = distance;
    this->robot = robot;
}

int Graphe::parcours(RR::Robot start, RR::Robot end)
{
    std::priority_queue<PQitem> pq;
    std::unordered_map<RR::Robot, int, RR::RobotHash> poids;
    std::unordered_map<RR::Robot, std::pair<RR::Robot, RR::Robot::Move>, RR::RobotHash> pred;

    //initialize weights
    for (std::pair<const RR::Robot, Sommet> sommet : map)
    {
        poids[sommet.first] = INT16_MAX;
    }
    poids[start] = 0;
    pq.push(PQitem(0, start));

    while (!pq.empty())
    {
        RR::Robot courant = pq.top().robot; //courant -> elt de la file avec prio minimale
        pq.pop();

        for (std::pair<RR::Robot, RR::Robot::Move> voisin : map[courant].voisins)
        {
            RR::Robot posVoisin = voisin.first;
            //le poids de l'arrete c'est le nombre de sauts necessaires pour aller du point courant
            //a son voisin. Toujours 1 ici
            if (poids[posVoisin] > poids[courant] + 1)
            {
                poids[posVoisin] = poids[courant] + 1;
                pred[posVoisin] = {courant, voisin.second};
                pq.push(PQitem(poids[posVoisin], posVoisin));
            }
        }
    }

    if (poids[end] == INT16_MAX || poids[end] == 0)
    {
        std::cout << "Le chemin n'existe pas" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "le chemin s'effectue en " << poids[end];
        poids[end] == 1 ? std::cout << " mouvement" : std::cout << " mouvements";
        std::cout << std::endl;
    }

    RR::Robot r = end;
    std::vector<std::pair<RR::Robot, RR::Robot::Move>> chemin;
    std::string parcours = "Arrivée";
    while (r != start)
    {
        std::pair<RR::Robot, RR::Robot::Move> p = pred[r];
        parcours = printRobotData(r, poids) + RR::MovesToString(p.second) + "\n" + parcours;
        chemin.push_back(p);
        r = p.first;
    }

    parcours = printRobotData(start, poids) + parcours;
    parcours = "Départ\n" + parcours;

    //std::cout << parcours << std::endl;

    return poids[end];
}