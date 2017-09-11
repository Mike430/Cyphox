#pragma once
#include "Cypher.h"
#include <sstream>
#include <vector>
#include <climits>

#define ERROR_CODE -1000001
#define CHAR_SET_SIZE 95

static const char SPECIAL_CHAR_GBP = '\x9C';
static const char SPECIAL_CHAR_BACKSLASH = '\\';

class FirstCryptor : public Cypher
{
private:
	static char _mCharSet[ CHAR_SET_SIZE ];
	static char _mNegativeCharSet[ CHAR_SET_SIZE ];

	int FindNextZeroIndex();
	int FindVecForCharFromZeroIndex( char c, int zeroIndex );
	char FindCharWithVecFromZero( int vec, int zeroIndex );
	int FindCharGlobalIndex( char c );
	string BitwiseShift( string stringToShift, float percentage );
public:
	FirstCryptor();
	~FirstCryptor();

	string Encrypt( uint64_t seed, string decMsg );
	string Decrypt( uint64_t seed, string encMsg );

	void PrintCharSet();
};

