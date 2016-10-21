#include "matrix.hpp"

class BlockMatrix
{
    vector< vector <Matrix> > values;
    uint cols;
    uint rows;
    
public:
    BlockMatrix(Matrix m, uint blockSize);
    BlockMatrix(uint rows, uint cols, uint blockSize, float minv, float maxv);
    
    uint getCols() const;
    uint getRows() const;
    
    Matrix operator() (uint i, uint j) const;
};