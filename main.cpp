#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "block.hpp"
#include <papi.h>


using namespace std;

typedef unsigned int uint;

void multBlocks(BlockMatrix left, BlockMatrix right, BlockMatrix &result, int type);


int main(int argc, char **argv)
{
	if ((string(argv[1])=="-generate") && (argc==2))
	{
	    Matrix m(100, 100, -100, 100);
        m.writeToBinaryFile("a2000.bin");
        
        Matrix k(100, 100, -100, 100);
        k.writeToBinaryFile("b2000.bin");
	}
	else if ((string(argv[1])=="-time") && (argc==4))
	{
		Matrix left(argv[2]);
		Matrix right(argv[3]);
		
		BlockMatrix left32(left, 32);
		BlockMatrix right32(right, 32);
		
		BlockMatrix left52(left, 52);
		BlockMatrix right52(right, 52);
		
		BlockMatrix res32(left.getRows(), right.getCols(), 32, 0, 0);
		BlockMatrix res52(left.getRows(), right.getCols(), 52, 0, 0);
		
		long start = clock();
		multBlocks(left32, right32, res32, 0);
		long stop = clock();
		cout << 0 << " " << (float)(stop-start)/(float)CLOCKS_PER_SEC << endl;
		
		start = clock();
		multBlocks(left32, right32, res32, 1);
		stop = clock();
		cout << 1 << " " << (float)(stop-start)/(float)CLOCKS_PER_SEC << endl;
		
		start = clock();
		multBlocks(left52, right52, res52, 1);
		stop = clock();
		cout << 2 << " " << (float)(stop-start)/(float)CLOCKS_PER_SEC << endl;
		
	}
	else if ((string(argv[1])=="-test") && (argc==5))
	{
		Matrix left(argv[3]);
		Matrix right(argv[4]);
		    
		BlockMatrix left32(left, 32);
		BlockMatrix right32(right, 32);
		
		BlockMatrix left52(left, 52);
		BlockMatrix right52(right, 52);
		
		BlockMatrix res32(left.getRows(), right.getCols(), 32, 0, 0);
		BlockMatrix res52(left.getRows(), right.getCols(), 52, 0, 0);
		
		int c;
		if (string(argv[2])=="flops")
		{
			c=PAPI_FP_OPS;
		} else if (string(argv[2])=="l1")
		{
			c=PAPI_L1_DCM;
		} else if (string(argv[2])=="l2")
		{
			c=PAPI_L2_DCM;
		} else if (string(argv[2])=="tlb")
		{
			c=PAPI_TLB_DM;
		} else if (string(argv[2])=="tot")
		{
			c=PAPI_TOT_CYC;
		} else return -1;
		
		long long r1,r2,r3;
		
		PAPI_start_counters(&c, 1);
		multBlocks(left32, right32, res32, 0);
		PAPI_stop_counters(&r1, 1);
		cout << 0 << " " << r1 << endl;
		
		PAPI_start_counters(&c, 1);
		multBlocks(left32, right32, res32, 1);
		PAPI_stop_counters(&r2, 1);
		cout << 1 << " " << r2 << endl;
		
		PAPI_start_counters(&c, 1);
		multBlocks(left52, right52, res52, 1);
		PAPI_stop_counters(&r3, 1);
		cout << 2 << " " << r3 << endl;
	}
	else
	{
	    throw "You're in trouble!\n";
	}
    return 0;
}