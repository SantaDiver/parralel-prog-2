#include "matrix.hpp"

float eps = 0.0001;

Matrix::Matrix(uint nrows, uint ncols, float fMin, float fMax)
{
    cols = ncols;
    rows = nrows;
    FORALLELEMS
        if (j == 0) values.push_back(vector<float>());
        values[i].push_back(0);
    EXEC
    
    fillRandElems(fMin, fMax);
}

Matrix::Matrix(string path)
{
    ifstream matrixFileStream(path.c_str());
    matrixFileStream >> rows;
    matrixFileStream >> cols;
    
    FORALLELEMS
            float readValue;
            matrixFileStream >> readValue;
            if (j == 0) values.push_back(vector<float>());
            values[i].push_back(readValue);
    EXEC
}

float Matrix::operator() (uint i, uint j) const
{
    if (i < 0 || j < 0 || i > rows || j > cols)
        throw "Некорректные значения индексов!";
    else return values[i][j];
}

void Matrix::addToElem(Matrix left, Matrix right, uint i, uint j, uint k)
{
    values[i][j] += left(i, k)*right(k, j);
}

void Matrix::setElem(uint i, uint j, float value)
{
    values[i][j] = value;
}

inline uint Matrix::getCols() const
{
    return cols;
}

inline uint Matrix::getRows() const
{
    return rows;
}

void Matrix::writeToBinaryFile(string path) const
{
    ofstream outputFile;
    outputFile.open(path.c_str(), ios::out | ios::binary);
    outputFile << rows << " ";
    outputFile << cols << " ";
    FORALLELEMS
        outputFile << values[i][j] << " ";
    EXEC
}

void Matrix::print() const
{
    FORALLELEMS
        cout << values[i][j] << "  ";
        if (j == cols-1) cout << endl;
    EXEC
}

void Matrix::fillRandElems(float fMin, float fMax)
{
    srand(time(0));
    FORALLELEMS
        float f = (float)rand() / RAND_MAX;
        values[i][j] = fMin + f * (fMax - fMin);
    EXEC
}

float calcDif(Matrix f, Matrix s)
{
    float result = 0;
    
    for (uint i=0; i<f.getRows(); ++i)
    {
        for (uint j=0; j<f.getCols(); ++j)
        {
            result = max (fabs(f(i, j) - s(i, j)), result);
        }
    }
    
    return result;
}

void multiplicate(Matrix left, Matrix right, Matrix &result, uint type)
{
    if (left.getCols() != right.getRows() || result.getRows() != left.getRows() 
        || result.getCols() != right.getCols())
        throw "Некорректные размеры матриц!";
        
    switch (type)
    {
        case 0: ii jj kk calc matrix break;
        case 1: ii kk jj calc matrix break;
        case 2: jj ii kk calc matrix break;
        case 3: jj kk ii calc matrix break;
        case 4: kk ii jj calc matrix break;
        case 5: kk jj ii calc matrix break;
        default: throw "Нет такого типа умножения!";
    }
}