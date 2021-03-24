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

struct compare
{
    bool operator()(const Sommet &s1, const Sommet &s2) const
    {
        return s1.parcours < s2.parcours;
    }
};

void Graphe::parcours(Sommet start)
{
    std::multiset<Sommet, compare> mset;
    Sommet courant = start;

    courant.parcours = 0;
    courant.parent = nullptr;

    mset.insert(courant);
    while (mset.size() != 0)
    {

        multiset<Sommet, compare>::iterator itr_ms = mset.begin();
        courant = *itr_ms; //courant -> elt de la file avec prio minimale
        multiset<Sommet, less<int>>::iterator itr_test;
        cout << "\n\n\nNOUVEAU PARCOURS - " << mset.size();
        for (itr_test = mset.begin(); itr_test != mset.end(); ++itr_test)
        {
            cout << "\nSommet : " << itr_test->robot.location.line << ":" << itr_test->robot.location.column << " - " << getstatus(itr_test->robot.status) << " - " << itr_test->parcours;
        }
        //std::cout << courant.voisins.size() << std::endl;
        for (RR::Robot robot : courant.voisins)
        {
            //le poids de l'arrete c'est le nombre de sauts necessaires pour aller du point courant
            //a son voisin. Toujours 1 ici
            Sommet sommet = start;
            std::map<RR::Robot, Sommet>::iterator itr_map;
            if ((itr_map = map.find(robot)) != map.end())
                sommet = itr_map->second;
            else
                break;

            if (sommet.parcours > courant.parcours + 1 && sommet.visite == false)
            {
                sommet.visite = true;
                sommet.parent = &courant;
                sommet.parcours = courant.parcours + 1;
                std::cout << "\nParent : " << courant.robot.location.line << ":" << courant.robot.location.column << " - " << getstatus(courant.robot.status) << " - " << courant.parcours << std::endl;
                std::cout << "Sommet : " << sommet.robot.location.line << ":" << sommet.robot.location.column << " - " << getstatus(sommet.robot.status) << " - " << sommet.parcours << std::endl;
                mset.insert(sommet);
                map.erase(itr_map);
                map.insert(std::pair<RR::Robot, Sommet>(robot, sommet));
            }
        }
        mset.erase(mset.begin());
    }
    std::cout << "\n\n CHEMIN LE PLUS COURS" << std::endl;
    /*Sommet test = courant;
    int i = 0;
    while (test.parent != nullptr && i < 20)
    {
        std::cout << "Sommet : " << test.robot.location.line << ":" << test.robot.location.column << " - " << getstatus(test.robot.status) << " - " << test.parcours << std::endl;
        std::cout << "Parent : " << test.parent->robot.location.line << ":" << test.parent->robot.location.column << " - " << getstatus(test.parent->robot.status) << " - " << test.parent->parcours << std::endl;
        test = *test.parent;
        i++;
    }*/
}