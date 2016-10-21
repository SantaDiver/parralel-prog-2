#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef unsigned int uint;

#define ii for(uint i=0; i<left.getRows(); ++i) { 
#define jj for(uint j=0; j<right.getCols(); ++j) { 
#define kk for(uint k=0; k<left.getCols(); ++k) {
#define matrix }}}
#define calc result.addToElem(left, right, i, j, k);

#define FORALLELEMS for(uint i=0; i<rows; ++i) { for(uint j=0; j<cols; ++j) {
#define EXEC }}

class Matrix 
{
    vector< vector <float> > values;
    uint cols;
    uint rows;
public:
    Matrix(uint nrows, uint ncols, float fMin, float fMax);
    
    Matrix(string path);
    
    float operator() (uint i, uint j) const;
    
    void addToElem(Matrix left, Matrix right, uint i, uint j, uint k);
    
    uint getCols() const;
    uint getRows() const;
    
    void writeToBinaryFile(string path) const;
    void print() const;
    
    void fillRandElems(float fMin, float fMax);
    void setElem(uint i, uint j, float value);
};