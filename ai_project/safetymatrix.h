#ifndef SAFETYMATRIX_H
#define SAFETYMATRIX_H

#include "infomatrix.h"

class SafetyMatrix : public InfoMatrix
{
public:
    SafetyMatrix(const InfoRetriever& retriever);
    virtual void buildMatrix() override;
    virtual void updateMatrixVal(Location loc, int val) override;
    void placeBomb(Location loc, int duration);
    std::vector<Location> findNearSafeTiles(Location loc) const;
    bool isSafe(Location loc) const;
};

#endif // SAFETYMATRIX_H
