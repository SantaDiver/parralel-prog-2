#include "block.hpp"

BlockMatrix::BlockMatrix(Matrix m, uint blockSize)
{
    uint xSize = (m.getCols()-1)/blockSize + 1;
    uint ySize = (m.getRows()-1)/blockSize + 1;
	for (uint i=0; i<ySize; ++i)
	{
	    values.push_back(vector<Matrix>());
		for (uint j=0; j<xSize; ++j)
		{
			uint rows = (i == ySize-1) ? m.getRows() % blockSize : blockSize;
			uint cols = (j == xSize-1) ? m.getCols() % blockSize : blockSize;
		    values[i].push_back(Matrix(rows, cols, 0, 0));
		    for (uint k=0; k<rows; ++k)
		    {
		    	for (uint l=0; l<cols; ++l)
		    	{
		    		//cerr << i << " " << j << " " << k << " " << l <<" "<< rows << " " << cols << "\n";
		    		values[i][j].setElem(k, l, m(i*xSize + k, j*ySize + l));
		    	}
		    }
		}
	}
	
	rows = ySize;
	cols = xSize;
}

BlockMatrix::BlockMatrix(uint qrows, uint qcols, uint blockSize, float minv, float maxv)
{
	//cerr << rows << " " << cols;
    uint xSize = (qcols-1)/blockSize + 1;
    uint ySize = (qrows-1)/blockSize + 1;
    
	for (uint i=0; i<ySize; ++i)
	{
	    values.push_back(vector<Matrix>());
		for (uint j=0; j<xSize; ++j)
		{
			uint nrows = (i == ySize-1) ? qrows % blockSize : blockSize;
			uint ncols = (j == xSize-1) ? qcols % blockSize : blockSize;
		    values[i].push_back(Matrix(nrows, ncols, minv, maxv));
		}
	}
	
	rows = ySize;
	cols = xSize;
}

inline uint BlockMatrix::getCols() const
{
	return cols;
}

inline uint BlockMatrix::getRows() const
{
	return rows;
}

Matrix BlockMatrix::operator() (uint i, uint j) const
{
    if (i < 0 || j < 0 || i > rows || j > cols)
        throw "Некорректные значения индексов!";
    else return values[i][j];
}

void multiplicate(Matrix left, Matrix right, Matrix &result, uint type);

void multBlocks(BlockMatrix left, BlockMatrix right, BlockMatrix &result, int type)
{
	if (left.getCols() != right.getRows() || result.getRows() != left.getRows() 
        || result.getCols() != right.getCols())
        throw "Некорректные размеры матриц!";

	for (uint i=0; i<result.getCols(); ++i)
	{
		for (uint j=0; j<result.getRows(); ++j)
		{
			for (uint k=0; k<left.getRows(); ++k)
			{
				Matrix m = result(i,j);
				multiplicate(left(i,k), right(k,j), m, type);
				result(i,j) = m;
			}
		}
	}
}
