#include "infomatrix.h"
#include "public_define.h"
#include "inforetriever.h"
#include <iostream>


InfoMatrix::InfoMatrix(const InfoRetriever& retriever) :
    m_retriever(retriever)
{}

void InfoMatrix::printMatrix() const
{
    std::string matRow;
    for (int y = 0; y < m_matrix.at(0).size(); y++)
    {
        for (int x = 0; x < m_matrix.size(); x++)
        {
            int val = getMatrixVal(Location(x, y));
            if (val > -1)
            {
                matRow = matRow + "+" + std::to_string(val) + ", ";
            } else
            {
                matRow = matRow + std::to_string(val) + ", ";
            }

        }
        std::cout << matRow << std::endl;
        matRow.clear();
    }
}


int InfoMatrix::getMatrixVal(Location loc) const
{
    return m_matrix[loc.x][loc.y];
}
