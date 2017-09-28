//////////////////////////////////////////
//
//	BitMatrix.cpp
//
///////////////////////////////////////////

#include "BitMatrix.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <fstream>
using namespace std;
#define BYTE_COUNT (sizeof(unsigned int) / sizeof(unsigned char))

BitMatrix::BitMatrix()
{
	_memory = NULL;
	_row=_col=0;
	_count= NULL;
	_Count=0;
	_size=0;
}

//--------------------------------------------------------------------
// BitMatrix::BitMatrix
//
// Input    : row,col
// Purpose  : Allocate the memory for the BitMatrix
//--------------------------------------------------------------------
BitMatrix::BitMatrix(int row,int col)
{
	// Convert bitsize to number of ints
	_row = row;
	_col = col;
	_size = (_col>>5)+1;
	_memory = new unsigned int *[_row];
	_count = new unsigned int [_row];
	for (int i = 0; i < _row; i++)
	{
		_memory[i] = new unsigned int[_size];
		// fill BitMatrix with zeroes
		for (int j = 0; j < _size; j++)
			_memory[i][j] = 0;
		_count[i]=0;
	}
	_Count=0;
}

BitMatrix::BitMatrix(int squ)
	{
	_row = squ;
	_col = squ;
	_size = (_col>>5)+1;
	_memory = new unsigned int *[_row];
	_count = new unsigned int [_row];
	for (int i = 0; i < _row; i++)
	{
		_memory[i] = new unsigned int[_size];
	// fill BitMatrix with zeroes
		for (int j = 0; j < _size; j++)
			_memory[i][j] = 0;
		_count[i]=0;
	}
	_Count=0;
	}
//--------------------------------------------------------------------
// BitMatrix::BitMatrix
//
// Input    : b - BitMatrix to copy 
// Purpose  : Copy constructor
//--------------------------------------------------------------------
BitMatrix::BitMatrix(BitMatrix &b)
{		
	// Copy information from source BitMatrix
	_size = b._size;
	_row = b._row;
	_col = b._col;
	_memory = new unsigned int *[_row];
	_count = b._count;
	for (int i = 0; i < _row; i++)
  {
		_memory[i] = new unsigned int[_size];
		for (int j = 0; j< _size; j++)
			_memory[i][j]=b._memory[i][j];
		_count[i] = b._count[i];
  }
  _Count=b._Count;
}

//--------------------------------------------------------------------
// BitMatrix::~BitMatrix
//
// Purpose  : Deallocate memory for the BitMatrix
//--------------------------------------------------------------------
BitMatrix::~BitMatrix()
{
	if (_memory)
		for(int i = 0; i < _row; i++)
			delete [] _memory[i];
	if (_count) delete [] _count;
}

//--------------------------------------------------------------------
// BitMatrix::FillRand
//
// Input    : p - probability of a bit being set to 1
// Purpose  : Fill the BitMatrix with random data
//--------------------------------------------------------------------
void BitMatrix::FillRand(double p)
{
	unsigned int randy;
	for (int i = 0; i< _row; i++)
		for (int j = 0; j < _size; j++)
		{
			randy = 0;
			for (int q=0; q<32; q++)
			{
				// Fill bit with 1 when above probability p
				if (j*32+q ==_col) break;
				if ((rand()/(float)RAND_MAX) < p)
					randy = randy + BitTable[q];
			}

			_memory[i][j] = randy;
		}
		Count();
}

//--------------------------------------------------------------------
// BitMatrix::SetOne
//
// Input    : i,j - bit position in BitMatrix to be changed
// Purpose  : Fill in a 1 in a certain position
//--------------------------------------------------------------------
void BitMatrix::SetOne(int i,int j)
{
	// Locate correct int in the BitMatrix
	// switch on correct bit
	if (CheckPosition(i,j) == 0)
		{ _count[i]++;_Count++;}
	_memory[i][j>>5] |= BitTable[(j % 32)];
}
//--------------------------------------------------------------------
// BitMatrix::SetZero
//
// Input    : i,j - bit position in BitMatrix to be changed
// Purpose  : Fill in a 0 in a certain position
//--------------------------------------------------------------------
void BitMatrix::SetZero(int i,int j)
{
	// Locate correct int in the BitMatrix
	// switch on correct bit
	if (CheckPosition(i,j) > 0)
		{ _count[i]--;_Count--;}
	_memory[i][j>>5] &= ~BitTable[(j % 32)];
}
//--------------------------------------------------------------------
// BitMatrix::FillOnes
//
// Purpose  : Fill the BitMatrix with ones
//--------------------------------------------------------------------
void BitMatrix::FillOnes()
{
	for (int i=0; i<_row; i++)
		for (int j=0; j<_size;j++)
		{
			_memory[i][j] = UINT_MAX;		
			_count[i]=_col;
		}
		_Count=_row*_col;
		
}

//--------------------------------------------------------------------
// BitMatrix::Count
//
// Purpose  : Count the ones in the BitMatrix
//--------------------------------------------------------------------
void BitMatrix::Count()
{
	_Count = 0;
	for (int i = 0; i < _row; i++)
	{
		int final = 0;
		unsigned char *p;
		p = (unsigned char *)_memory[i];
		for (int j=0; j<_size*4; j++)
		{
		// Count the 4 chars (1 int = 4 bytes/chars)
		// count 1s by dividing into chars and using a lookup table
			final += CountTable[*p];
			_Count += CountTable[*p];
			p++;
		}
		_count[i] = final; 
	}
}

//--------------------------------------------------------------------
// BitMatrix::CheckPosition
//
// Input    : i,j - bit position in BitMatrix to be checked
// Return	: 0 if bit j is 0, 1 otherwise
//--------------------------------------------------------------------
unsigned int BitMatrix::CheckPosition(int i,int j)
{
	return (_memory[i][j>>5] & BitTable[(j % 32)]);
}
//--------------------------------------------------------------------
// BitMatrix::Not
//Purpose	: Change 1 to 0 and 0 to 1
//--------------------------------------------------------------------
void BitMatrix::Not()
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _size; j++)
			_memory[i][j] = ~_memory[i][j];
		_count[i]=_col-_count[i];
	}	
	_Count=_row*_col-_Count;
}
//--------------------------------------------------------------------
// BitMatrix::Or 
// Input    : B1 - the first BitMatrix
//			  B2 - the second BitMatrix
// Purpose  : Bitwise OR 2 BitMatrixs and store the result
//--------------------------------------------------------------------
void BitMatrix::Or(const BitMatrix &B1, const BitMatrix &B2)
{
	unsigned int **b1ptr, **b2ptr;
	b1ptr = B1._memory;
	b2ptr = B2._memory;
	for ( int i = 0; i < B1._row; i++)
	{// for each INT in the row
		for ( int j = 0; j < B1._size; j++)
			// Bitwise OR the int
			_memory[i][j] = b1ptr[i][j] | b2ptr[i][j];
	}
	Count();
}
//--------------------------------------------------------------------
// BitMatrix::XOR
//
// Input    : B1 - the first BitMatrix
//			  B2 - the second BitMatrix
// Purpose  : Bitwise OR 2 BitMatrixs and store the result
//--------------------------------------------------------------------
void BitMatrix::XOR(const BitMatrix &b1, const BitMatrix &b2)
{
	unsigned int **b1ptr, **b2ptr;
	b1ptr = b1._memory;
	b2ptr = b2._memory;
	for ( int i = 0; i < b1._row; i++)
	{// for each INT in the row
		for ( int j = 0; j < b1._size; j++)
			// Bitwise OR the int
			_memory[i][j] = b1ptr[i][j] ^ b2ptr[i][j];
	}
	Count();
}
//--------------------------------------------------------------------
// BitMatrix::AndOnly
//
// Input    : B1 - the first BitMatrix
//			  B2 - the second BitMatrix
// Purpose  : Bitwise AND 2 BitMatrixs and store the result
//--------------------------------------------------------------------
void BitMatrix::AndOnly(const BitMatrix &B1, const BitMatrix &B2)
{
	unsigned int **b1ptr, **b2ptr;

	// AND the BitMatrixs
	
	b1ptr = B1._memory;
	b2ptr = B2._memory;
	for (int i = 0; i < B1._row; i++)
		for (int j = 0; j< B1._size; j++)
	{
		// and each int bitwise
		_memory[i][j] = b1ptr[i][j] & b2ptr[i][j];
	}
	Count();
}

//--------------------------------------------------------------------
// BitMatrix::NotAnd
//
// Input    : B1 - the first BitMatrix
//			  B2 - the second BitMatrix
// Output	:
// Purpose  : Bitwise AND a BitMatrixs and the negation and store the result
//--------------------------------------------------------------------
void BitMatrix::NotAndOnly(const BitMatrix &B1, const BitMatrix &B2)
{
	unsigned int **b1ptr, **b2ptr;

	// AND the BitMatrixs
	
	b1ptr = B1._memory;
	b2ptr = B2._memory;
	for (int i = 0; i < B1._row; i++)
		for (int j = 0; j< B1._size; j++)
	{
		// and each int bitwise
		_memory[i][j] = b1ptr[i][j] & ~b2ptr[i][j];
	}
	Count();
}

//--------------------------------------------------------------------
// BitMatrix::Superset
//
// Input    : subset - BitMatrix to check for a superset relation
// Purpose  : Determine whether this BitMatrix is a superset of the parameter
// Return	: True if this BitMatrix is a superset of the parameter BitMatrix 
//				(this BitMatrix has a 1 in ALL positions that parameter BitMatrix does )
// NOTE:  assumes the set of BitMatrixs is lexicographically ordered
//--------------------------------------------------------------------
bool BitMatrix::Superset(const BitMatrix *subset)
{
	// No need to check for superset when the count is too small
	for(int i = 0; i < _row; i++)
		if (_count[i] <= subset->_count[i])
			return false;
	// Start at the end of the BitMatrix
	// Leads to fewer bitwise ANDs
	unsigned int *b1ptr, *b2ptr;
	for(int i = 0; i < _row; i++)
	{
		b1ptr = &_memory[i][_size-1];
		b2ptr = &subset->_memory[i][subset->_size-1];
		// for each INT in the row
		for (int j = _size-1; j >=0; j--)
		{
		//Andy++;
		// bitwise AND them
			unsigned int a = (*b1ptr) & (*b2ptr);
		// if not a subset
			if (a != *b2ptr)
				return false;		
			b1ptr--;
			b2ptr--;
		}
	}
	return true;
}
//--------------------------------------------------------------------
// BitMatrix::Multiplication
//
// Input    : B1 - the first BitMatrix m*k
//			  B2 - the second BitMatrix (k*n)T
// Purpose  : Multiply 2 BitMatrixs and store the result
//--------------------------------------------------------------------
bool BitMatrix::Multiplication(const BitMatrix &b1, const BitMatrix &b2)
{
	unsigned int *b1p,*b2p;
	if (b1._col != b2._col) return false;
		else
			{
				for(int i=0;i<b1._row;i++)
					for(int j=0;j<b2._row;j++)
					{
						b1p=b1._memory[i];
						b2p=b2._memory[j];
						for(int k=0;k<b1._size;k++,b1p++,b2p++)
							if(*b1p & *b2p) {SetOne(i,j);break;}
					}
				Count();
			}
		return true;
}
	
//--------------------------------------------------------------------
// BitMatrix::Transpose
//
// Input    : bitmatrix to be transposed
// Purpose  : transpose the given bitmatrix and store it
//--------------------------------------------------------------------
void BitMatrix::Transpose(const BitMatrix &bT)
{
	_row = bT._col;
	_col = bT._row;
	_size = (_col>>5)+1;
	_memory = new unsigned int *[_row];
	_count = new unsigned int [_row];
	unsigned int p,*q;	
	int k;
	for (int i = 0; i < _row; i++)
	{
		_memory[i] = new unsigned int[_size];
		int k;
		//worked for char (1 int = 4 bytes/chars)
		q=_memory[i];
			p=0;
			for (k=0; k < bT._row; k++)
			{
				//for 1 unint in matrix bT can be 32 rows of new matrix
				p=p+(((bT._memory[k][i>>5] & BitTable[i%32])<<(i%32))>>(k%32));
				// 32 bits per unint
				if (k%32 == 31) 
				{
					*q=p;
					q++;
					p=0;
				}
			}
			*q=p;
	}
	Count();
}
//--------------------------------------------------------------------
// BitMatrix::Output
//
// Purpose  : out put the bitmatrix in screen just for debug
//--------------------------------------------------------------------
void BitMatrix::OutPut()
{
	for (int i = 0; i < _row; i++)
	{
		cout<<_count[i]<<"@";
		for(int j = 0; j < _col; j++)
			if (CheckPosition(i,j)) cout <<"1";
			else cout<<"0";
		cout<<endl;
	}
}
void BitMatrix::savetofile(string str)
{
			ofstream fou(str.c_str());
			for (int i=0;i< _row;i++)
			{
				for(int j=0;j<_col;j++) 
				{
					if(CheckPosition(i,j)) fou<<1;
						else fou<<0;
					if (j<_col-1) fou<<" ";
				}
				fou<<endl;
			}
			fou.close();
	}
