#ifndef INFOMATRIX_H
#define INFOMATRIX_H

#include <vector>

class InfoRetriever;
struct Location;

class InfoMatrix
{
public:
    InfoMatrix(const InfoRetriever& retriever);
    virtual ~InfoMatrix() = default;
    virtual void buildMatrix() = 0;
    virtual void updateMatrixVal(Location loc, int val) = 0;
    void printMatrix() const;
    int getMatrixVal(Location loc) const;
protected:
    const InfoRetriever& m_retriever;
    std::vector< std::vector<int> > m_matrix;
};

#endif // INFOMATRIX_H
