////////////////////////////////////////////
//
//	BitMatrix.h
//
//	A simple BitMatrix class with only uncompressed data
//	Note: Name BitMatrixs are of this type
//
////////////////////////////////////////////

#ifndef BitMatrix_H
#define BitMatrix_H
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// BitTable[i] contains a 1 at only position i 
const int BitTable[32] = 
{ 
	2147483648UL, 1073741824, 536870912, 268435456,
	134217728, 67108864, 33554432, 16777216,
	8388608, 4194304, 2097152, 1048576,
	524288, 262144, 131072, 65536,
	32768, 16384, 8192, 4096,
	2048, 1024, 512, 256,
	128, 64, 32, 16,
	8, 4, 2, 1 
};
// CountTable[i] contains the number of 1's in the byte value of i
const int CountTable[256] =
{ 
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 
	2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 
	2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 
	3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 
};

//--------------------------------------------------------------------
// class BitMatrix
//
// Used to store bits in an array of ints
//--------------------------------------------------------------------
class BitMatrix
{

public:

	BitMatrix();
	BitMatrix(int row,int col);
	BitMatrix(int squ);
	BitMatrix(BitMatrix &);
	~BitMatrix();

	void FillRand(double p);//¹¹ÔìËæ»ú¾ØÕó
	void SetOne(int i,int j);
	void SetZero(int i,int j);
	void FillOnes();
	void Count();
	unsigned int CheckPosition(int i,int j);

	void Not();
	void Or(const BitMatrix &b1, const BitMatrix &b2);
	void XOR(const BitMatrix &b1, const BitMatrix &b2);
	void AndOnly(const BitMatrix &b1, const BitMatrix &b2);
	void NotAndOnly(const BitMatrix &b1, const BitMatrix &b2);
	bool Multiplication(const BitMatrix &b1, const BitMatrix &b2);
	bool Superset(const BitMatrix *subset);
	void Transpose(const BitMatrix &bT);
	void OutPut(); //just for debug;
	void savetofile(string str);
	friend class Count;
	int   _row,_col;
	int		_size;				// in number of INTs per line
	unsigned int*		_count;		// the number of ones in the every line in BitMatrix
	unsigned int		_Count;   // the number of ones in the BitMatrix (plus the _count[i])
	unsigned int**	_memory;	// where uncompressed data is stored
};

#endif
