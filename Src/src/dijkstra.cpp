#include "../headers/dijkstra.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
void Dijkstra::parcours(Graphe graphe, Sommet start)
{

    Sommet courant = start;

    std::vector<Sommet> candidats;
    bool arrive = false;

    while (!arrive)
    {
        for (RR::Robot robot : courant.voisins)
        {
            //if visite avant ?
            candidats.push_back(robot); //peut-être faire la conversion robot->sommet ici
            // recherche dans une map ? Clé : un robot Value: le sommet
            //le sommet deviens visite = true
        }
        int min = candidats[0].parcours; //même idée : un vecteur de sommet pour récupérer les infos
        for (Sommet sommet : candidats)
        {
            if (sommet.parcours < min)
            {
                min = sommet.parcours;
                courant = sommet;
            }
        }
        for (int i = 0; i < candidats.size(); i++)
        {
            if (candidats[i].robot.location == courant.robot.location)
                candidats.erase(candidats.begin() + i);
        }
        std::vector<Sommet>::iterator itr = std::find(candidats.begin(), candidats.end(), courant);
        candidats.erase(itr);
        if (candidats.size() == 0)
            arrive = true;
    }
}