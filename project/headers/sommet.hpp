#ifndef SOMMET_HPP_
#define SOMMET_HPP_
#include <iostream>
#include <vector>
#include "sommet.hpp"

struct Location
{

    Location(int l, int c);
    Location() {}

    bool operator==(const Location &rhs) const;

    int line;
    int column;
};

enum struct Status
{
    EAST,
    NORTH,
    WEST,
    SOUTH,
    DEAD
};

class sommet
{
public:
    Location location;
    Status direction;
    vector<sommet> voisin;

private:
};

#endif