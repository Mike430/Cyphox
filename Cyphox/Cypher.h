#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cypher
{
public:
	Cypher();
	~Cypher();

	virtual string Encrypt( int seed, string decMsg ) = 0;
	virtual string Decrypt( string encMsg ) = 0;
};

