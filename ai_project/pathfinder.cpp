#include "pathfinder.h"
#include "public_define.h"
#include "inforetriever.h"
#include "safetymatrix.h"
#include "utils.h"
#include <algorithm>
#include <iostream>


PathFinder::PathFinder(const InfoRetriever& retriever) :
    m_retriever(retriever),
    m_generator(AStar::Generator())
{
    m_generator.setWorldSize({m_retriever.getWidth(), m_retriever.getHeight()});
    addCollisions();
    m_generator.setHeuristic(AStar::Heuristic::manhattan);
    m_generator.setDiagonalMovement(false);
}

void PathFinder::addCollisions()
{
    for (auto& crate : m_retriever.getCrates())
    {
        AStar::Vec2i collisionCoordinates = {crate.x, crate.y};
        m_generator.addCollision(collisionCoordinates);
    }

    for (auto& solid : m_retriever.getSolids())
    {
        AStar::Vec2i collisionCoordinates = {solid.x, solid.y};
        m_generator.addCollision(collisionCoordinates);
    }

    for (auto& bomb : m_retriever.getBombs())
    {
        if (bomb.loc.x != m_retriever.getMyLoc().x || bomb.loc.y != m_retriever.getMyLoc().y)
        {
         AStar::Vec2i collisionCoordinates = {bomb.loc.x, bomb.loc.y};
         m_generator.addCollision(collisionCoordinates);
        }
    }
}

Location PathFinder::getFleeingTile()
{
    AStar::Vec2i firstTile = {m_retriever.getMyLoc().x, m_retriever.getMyLoc().y};
    std::vector<AStar::Vec2i> fleeingTiles = findFleeingTiles(m_retriever.getMyLoc());

    if (fleeingTiles.size() > 0)
    {
        std::vector<int> distances;
        for (AStar::Vec2i tile : fleeingTiles)
        {
            int xDist = abs(tile.x - m_retriever.getWidth()/2);
            int yDist = abs(tile.y - m_retriever.getWidth()/2);
            distances.emplace_back(xDist + yDist);
        }
        int minDist = *min_element(distances.begin(), distances.end()); // tile that is closest to center
        auto it = std::find(distances.begin(), distances.end(), minDist);
        int minDistIndex = std::distance(distances.begin(), it); // if there are multiple tiles equally close to the center, the lowest index is returned
        firstTile = fleeingTiles[minDistIndex];
    }
    return Location(firstTile.x, firstTile.y);
}

Location PathFinder::getFleeingTile2()
{
    AStar::Vec2i firstTile = {m_retriever.getMyLoc().x, m_retriever.getMyLoc().y};
    std::vector<AStar::Vec2i> fleeingTiles = findFleeingTiles(m_retriever.getMyLoc());

    if (fleeingTiles.size() > 0)
    {
        std::vector<int> dofs;
        for (AStar::Vec2i tile : fleeingTiles)
        {
            int dof = m_retriever.getDegreesOfFreedom(Location(tile.x, tile.y));
            dofs.emplace_back(dof);
        }
        int maxDof = *max_element(dofs.begin(), dofs.end()); // tile with highest number of degrees of freedom
        auto it = std::find(dofs.begin(), dofs.end(), maxDof);
        int maxDofIndex = std::distance(dofs.begin(), it);
        firstTile = fleeingTiles[maxDofIndex];
    }
    return Location(firstTile.x, firstTile.y);
}

std::vector<AStar::CoordinateList> PathFinder::findReachableTiles(const Location currentLoc, const std::vector<AStar::Vec2i>& prospectLocs)
{
    std::vector<AStar::CoordinateList> paths;
    AStar::CoordinateList path;

    for (const auto& loc : prospectLocs)
    {
        path = m_generator.findPath({currentLoc.x, currentLoc.y}, loc);

        if (path.size() > 1)
        {
            if (path.front() == loc)
            {
                paths.push_back(path);
            }
        }
    }
    return paths;
}

std::vector<AStar::Vec2i> PathFinder::findFleeingTiles(Location loc)
{
    SafetyMatrix safetyMatrix(m_retriever);
    safetyMatrix.buildMatrix();

    std::vector<AStar::Vec2i> fleeingTiles;
    std::vector<Location> nearWalkableTiles = m_retriever.getNearWalkableTiles(loc, 3, 3);
    std::vector<Location> nearSafeTiles = safetyMatrix.findNearSafeTiles(loc);
    std::vector<Location> safeWalkableTiles = Utils::findLocVecIntersect(nearWalkableTiles, nearSafeTiles);
    AStar::CoordinateList safeWalkableTiles_AStar = Utils::locationVec_to_AStarVec(safeWalkableTiles);
    std::vector<AStar::CoordinateList> fleeingPaths = findReachableTiles(loc, safeWalkableTiles_AStar);
    std::vector<AStar::CoordinateList> safeFleeingPaths = selectSafeFleeingPaths(fleeingPaths, safetyMatrix);

    if (safeFleeingPaths.size() > 0)
    {
        for (AStar::CoordinateList path : safeFleeingPaths)
        {
            fleeingTiles.push_back(path[path.size() - 2]); // second to last element is the tile you want to move to
        }
    }
    return fleeingTiles;
}

std::vector<AStar::CoordinateList> PathFinder::selectSafeFleeingPaths(std::vector<AStar::CoordinateList>& paths, SafetyMatrix& safetyMatrix)
{
    std::vector<AStar::CoordinateList> safeFleeingPaths;
    for (AStar::CoordinateList& path : paths)
    {
        if (checkPathSafety(path, safetyMatrix))
        {
            safeFleeingPaths.push_back(path);
        }
    }
    return safeFleeingPaths;
}

bool PathFinder::checkPathSafety(AStar::CoordinateList path, SafetyMatrix tempMatrix)
{
    std::reverse(path.begin(), path.end()); // input parameter path is originally from end location to start location
    for (AStar::Vec2i loc : path)
    {
        if (tempMatrix.getMatrixVal(Location(loc.x, loc.y)) == 0)
        {
            return false;
        }

        for (int xLoc = 0; xLoc < m_retriever.getWidth(); ++xLoc)
        {
            for (int yLoc = 0; yLoc < m_retriever.getHeight(); ++yLoc)
            {
                int currentVal = tempMatrix.getMatrixVal(Location(xLoc, yLoc));
                tempMatrix.updateMatrixVal(Location(xLoc, yLoc), currentVal-1);
            }
        }
    }
    return true;
}
