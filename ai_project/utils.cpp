#include "utils.h"
#include "public_define.h"


Location Utils::offsetLocation(Location loc, direction dir, int depth)
{
    int xLoc = loc.x;
    int yLoc = loc.y;
    switch (dir)
    {
    case North:
        xLoc = loc.x;
        yLoc = loc.y - depth; // up
        break;
    case East:
        xLoc = loc.x + depth; // right
        yLoc = loc.y;
        break;
    case South:
        xLoc = loc.x;
        yLoc = loc.y + depth; // down
        break;
    case West:
        xLoc = loc.x - depth; // left
        yLoc = loc.y;
        break;
    }
    return Location(xLoc, yLoc);
}

int Utils::getIndex(std::vector<int> vec, int elem)
{
    auto it = find(vec.begin(), vec.end(), elem);

    if (it != vec.end())
    {
        int index = it - vec.begin();
        return index;
    }
    else {
        return -1;
    }
}

std::vector<Location> Utils::findLocVecIntersect(std::vector<Location> vec1, std::vector<Location> vec2)
{
    std::vector<Location> intersection;
    for (auto location1 : vec1)
    {
        for (auto location2 : vec2)
        {
            if (location1.x == location2.x && location1.y == location2.y)
            {
                intersection.emplace_back(location1);
            }
        }
    }
    return intersection;
}

std::vector<Location> Utils::AStarVec_to_LocationVec(AStar::CoordinateList& AStarList)
{
    std::vector<Location> locationVec;
    for (AStar::Vec2i vec2i : AStarList)
    {
        Location loc = Location(vec2i.x, vec2i.y);
        locationVec.emplace_back(loc);
    }
    return locationVec;
}

AStar::CoordinateList Utils::locationVec_to_AStarVec(std::vector<Location>& locationVec)
{
    AStar::CoordinateList AStarVec;
    for (Location loc : locationVec)
    {
        AStar::Vec2i AStarLoc = {loc.x, loc.y};
        AStarVec.emplace_back(AStarLoc);
    }
    return AStarVec;
}

// int Utils::manhattanDistance(Location loc1, Location loc2)
