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

	virtual string Encrypt( int seed, string decMsg ) = 0;
	virtual string Decrypt( int seed, string encMsg ) = 0;
};

