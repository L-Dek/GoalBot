#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "AStar.hpp"

class InfoRetriever;
class SafetyMatrix;
struct Location;

class PathFinder
{
public:
    PathFinder(const InfoRetriever& retriever);
    Location getFleeingTile();
    Location getFleeingTile2();
private:
    const InfoRetriever& m_retriever;
    AStar::Generator m_generator;

    void addCollisions();
    std::vector<AStar::Vec2i> findFleeingTiles(Location loc);
    std::vector<AStar::CoordinateList> findReachableTiles(const Location currentLoc, const std::vector<AStar::Vec2i>& prospectLocs);
    std::vector<AStar::CoordinateList> selectSafeFleeingPaths(std::vector<AStar::CoordinateList>& paths, SafetyMatrix& safetyMatrix);
    bool checkPathSafety(AStar::CoordinateList path, SafetyMatrix tempMatrix);
};

#endif // PATHFINDER_H
