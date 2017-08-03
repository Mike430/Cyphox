#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cypher
{
protected:
	static const string DecryptionErrorMSG;
public:
	Cypher();
	~Cypher();

	virtual string Encrypt( uint64_t seed, string decMsg ) = 0;
	virtual string Decrypt( uint64_t seed, string encMsg ) = 0;
};

