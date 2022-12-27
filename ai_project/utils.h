#ifndef UTILS_H
#define UTILS_H

#include "AStar.hpp"
#include <vector>

struct Location;

enum direction
{
    North,
    East,
    South,
    West,
    Last
};

class Utils
{
public:
    Utils();
    static Location offsetLocation(Location loc, direction dir, int depth);
    static int getIndex(std::vector<int> vec, int elem);
    static std::vector<Location> findLocVecIntersect(std::vector<Location> vec1, std::vector<Location> vec2);
    static std::vector<Location> AStarVec_to_LocationVec(AStar::CoordinateList& AStarList);
    static AStar::CoordinateList locationVec_to_AStarVec(std::vector<Location>& locationVec);
};

#endif // UTILS_H
