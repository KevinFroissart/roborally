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

std::string getstatus(RR::Robot::Status s)
{
    return s == RR::Robot::Status::EAST    ? "EAST"
           : s == RR::Robot::Status::NORTH ? "NORTH"
           : s == RR::Robot::Status::WEST  ? "WEST"
                                           : "SOUTH";
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

bool operator<(const PQitem &s1, const PQitem &s2)
{
    return s1.distance < s2.distance;
}

PQitem::PQitem(int distance, RR::Robot pos) {
    this->distance = distance;
    this->pos = pos;
}

void Graphe::parcours(RR::Robot start, RR::Robot end)
{
    std::priority_queue<PQitem> pq;
    std::unordered_map<RR::Robot, int, RR::RobotHash> poids;
    std::unordered_map<RR::Robot, RR::Robot, RR::RobotHash> pred;
    //std::set<RR::Robot> visites; idee pour checker les sommets deja visites

    //initialize weights
    for(std::pair<const RR::Robot, Sommet> sommet: map) {
        poids[sommet.first] = INT16_MAX;
    }
    poids[start] = 0;
    pq.push(PQitem(0, start));

    while (!pq.empty())
    {
        RR::Robot courant = pq.top().pos; //courant -> elt de la file avec prio minimale
        pq.pop();
        cout << "\n\nNOUVEAU PARCOURS - " << pq.size() << std::endl;
        //std::cout << courant.voisins.size() << std::endl;
        for (RR::Robot voisin : map[courant].voisins)
        {
            //le poids de l'arrete c'est le nombre de sauts necessaires pour aller du point courant
            //a son voisin. Toujours 1 ici
            if (poids[voisin] > poids[courant] + 1)
            {
                poids[voisin] = poids[courant] + 1;
                pred[voisin] = courant;
                pq.push(PQitem(poids[voisin], voisin));
            }
        }
    }

    if (poids[end] == INT16_MAX) {
        std::cout << "Le chemin n'existe pas" << std::endl;
        return;
    } else std::cout << "le chemin s'effectue en " << poids[end] << " mouvements" << std::endl;

    //saves the positions of the path
    std::vector<RR::Robot> chemin;
    RR::Robot r = end;
    while(r != start) {
        std::cout << pred[r].location.column << " " << pred[r].location.line << " " << pred[r].StatusToString() << endl;

        chemin.push_back(pred[r]);
        r = pred[r];
    }

    //display the path on the console
    for(RR::Robot r : chemin) {
        std::cout << "Sommet: " <<
                          std::to_string(r.location.line) + ":" +
                          std::to_string(r.location.column) + " - " +
                          getstatus(r.status) + " - " << std::endl;
    }
}

/*string Graphe::plus_court_chemin(Sommet *target)
{
    std::string res = "";
    Sommet *tmpt = target;
    while (tmpt->parent != nullptr)
    {
        std::string tmp = "Sommet: " +
                          std::to_string(tmpt->robot.location.line) + ":" +
                          std::to_string(tmpt->robot.location.column) + " - " +
                          getstatus(tmpt->robot.status) + " - " +
                          std::to_string(tmpt->parcours) + "\n";
        res = tmp + res;

        //std::cout << tmp << std::endl;
        tmpt = tmpt->parent;
    }
    std::cout << "\n\n CHEMIN LE PLUS COURT" << std::endl;
    std::cout << res << std::endl;
    return res;
}*/