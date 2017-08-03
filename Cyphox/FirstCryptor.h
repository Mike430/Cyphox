#pragma once
#include "Cypher.h"
#include <sstream>
#include <vector>
#include <climits>

#define ERROR_CODE -1000001

static const char SPECIAL_CHAR_GBP = '\x9C';
static const char SPECIAL_CHAR_BACKSLASH = '\\';

class FirstCryptor : public Cypher
{
private:
	static char _mCharSet[];
	const string _mSeparator = "/";
	int _mCharSetLength = 95;

	int FindNextZeroIndex();
	int FindVecForCharFromZeroIndex( char c, int zeroIndex );
	char FindCharWithVecFromZero( int vec, int zeroIndex );
	int FindCharGlobalIndex( char c );
	string AppendEnc( string base, int extension );
	vector<string> BreakStringInTwo(string str, string target);
public:
	FirstCryptor();
	~FirstCryptor();

	string Encrypt( uint64_t seed, string decMsg );
	string Decrypt( uint64_t seed, string encMsg );

	void PrintCharSet();
};

