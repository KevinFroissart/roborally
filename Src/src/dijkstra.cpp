#include "../headers/dijkstra.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

bool operator<(const Sommet &s1, const Sommet &s2)
{
    return s1.parcours < s2.parcours;
}

void Dijkstra::parcours(Graphe graphe, Sommet start, std::priority_queue<Sommet> pq)
{
    Sommet courant = start;

    courant.parent = start;
    courant.parcours = 0;

    while (pq.size() != 0)
    {
        pq.pop();
        for (RR::Robot robot : courant.voisins)
        {
            //peut-être faire la conversion robot->sommet ici
            Sommet s = start;
            std::map<RR::Robot, Sommet>::iterator itr;
            if ((itr = graphe.map.find(robot)) != graphe.map.end())
                s = itr->second;
            else
                break;
            if (!s.visite)
            {
                s.visite = true;
                s.parent = courant;
                s.parcours = courant.parcours + 1;
                pq.push(s);
            }
            // recherche dans une map ? Clé : un robot Value: le sommet
        }
        courant = pq.top();
    }
    //courant = chemin le plus cours (normalement inchallah)
    //on utilise pas graphe ? à voir pk et où est le pb
}