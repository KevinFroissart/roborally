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

    //initialiser tous les sommets a nullptr, +infini
    //initialiser le sommet de depart a lui-même, 0
    /*for (std::pair<const RR::Robot, Sommet> elem : map)
    {
        elem.second.parcours = 9999999;
        elem.second.parent = nullptr;
    }*/

    courant.parcours = 0;
    courant.parent = nullptr;

    mset.insert(courant);
    while (mset.size() != 0)
    {

        multiset<Sommet, compare>::iterator itr_ms = mset.begin();
        courant = *itr_ms; //courant -> elt de la file avec prio minimale
        //std::cout << mset.size() << std::endl;
        //std::cout << "Sommet : " << courant.robot.location.line << ":" << courant.robot.location.column << " - " << getstatus(courant.robot.status) << " - " << courant.parcours << std::endl;
        // for (std::vector<RR::Robot>::iterator it2 = courant.voisins.begin(); it2 != courant.voisins.end(); ++it2)
        // {
        //     std::cout << "   Voisins : " << it2->location.line << ":" << it2->location.column << " - " << getstatus(it2->status) << std::endl;
        // }
        multiset<Sommet, less<int>>::iterator itr_test;
        cout << "\n\n\nNOUVEAU PARCOURS - " << mset.size();
        for (itr_test = mset.begin(); itr_test != mset.end(); ++itr_test)
        {
            cout << "\nSommet : " << itr_test->robot.location.line << ":" << itr_test->robot.location.column << " - " << getstatus(itr_test->robot.status) << " - " << itr_test->parcours;
        }
        //std::cout << courant.voisins.size() << std::endl;
        for (RR::Robot robot : courant.voisins)
        {
            std::cout << "test" << std::endl;
            //le poids de l'arrete c'est le nombre de sauts necessaires pour aller du point courant
            //a son voisin. Toujours 1 ici
            Sommet sommet = start;
            std::cout << getstatus(robot.status) << std::endl;
            std::map<RR::Robot, Sommet>::iterator itr_map;
            if ((itr_map = map.find(robot)) != map.end())
                sommet = itr_map->second;
            else
            {
                std::cout << "break";
                break;
            } // à modifier
            if (sommet.visite == true)
                std::cout << "true" << std::endl;
            if (sommet.visite == false)
                std::cout << "false" << std::endl;
            else
                std::cout << "jsp" << std::endl;
            /*for (std::multiset<Sommet>::const_iterator i(mset.begin()), end(mset.end()); i != end; ++i)
            {
                std::cout << "\n\n\nNOUVEAU PARCOURS - " << mset.size() << "\nSommet : " << i->robot.location.line << ":" << i->robot.location.column << " - " << getstatus(i->robot.status) << " - " << i->parcours << std::endl;
            }*/
            if (sommet.parcours > courant.parcours + 1 && sommet.visite == false)
            {
                sommet.visite = true;
                sommet.parent = &courant;
                sommet.parcours = courant.parcours + 1;
                mset.insert(sommet);
            }
        }
        mset.erase(mset.begin());
    }
    while (courant.parent != nullptr)
    {
        std::cout << " " << courant.robot.location.line << " " << courant.robot.location.column << " " << getstatus(courant.robot.status) << std::endl;
        courant = *courant.parent;
    }
}