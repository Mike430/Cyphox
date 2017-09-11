#include "FirstCryptor.h"


char FirstCryptor::_mCharSet[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'-', '_', '*', '+', '&', '^', '%', '$', SPECIAL_CHAR_GBP, '!', '?', '/', SPECIAL_CHAR_BACKSLASH, '>', '<', '@', '|', ' ', '\'',	':', ';', '\(', '\)', '\[', '\]', '\{', '\}', '\#', '\~', ',', '.', '\n', '\r'
};


char FirstCryptor::_mNegativeCharSet[] = {};


FirstCryptor::FirstCryptor()
{
	for( int i = 0; i < CHAR_SET_SIZE; i++ )
	{
		_mNegativeCharSet[ i ] = _mCharSet[ i ];
		_mNegativeCharSet[ i ] ^= UINT8_MAX - 3;
		//cout << _mCharSet[ i ] << " = " << _mNegativeCharSet[ i ] << " is " << ( _mCharSet[ i ] == _mNegativeCharSet[ i ] ? "BAD" : "OKAY" ) << endl;
	}
}


FirstCryptor::~FirstCryptor()
{
}


string FirstCryptor::Encrypt( uint64_t seed, string decMsg )
{
	string encMsg = "";
	srand( seed );
	float randomPercentage = 0.01f * ( rand() % 100 );

	for( int i = 0; i < decMsg.length(); i++ )
	{
		int ZeroIndex = FindNextZeroIndex();
		int charPos = FindVecForCharFromZeroIndex( decMsg.at( i ), ZeroIndex );
		if( charPos == ERROR_CODE )
		{
			return "\nEncryption abandoned due to unqualified character\n";
		}
		char next = charPos < 0 ? _mNegativeCharSet[ charPos * -1 ] : _mCharSet[ charPos ];
		//next ^= seed;
		encMsg += next;
	}

	encMsg = BitwiseShift( encMsg, randomPercentage );

	return encMsg;
}


string FirstCryptor::Decrypt( uint64_t seed, string encMsg )
{
	string decMsg = "";
	bool charFound;
	uint8_t currentIndex;
	char queryChar;
	int zeroIndex;
	srand( seed );
	float randomPercentage = 0.01 * ( rand() % 100 );

	encMsg = BitwiseShift( encMsg, randomPercentage );

	for( int i = 0; i < encMsg.size(); i++ )
	{
		zeroIndex = FindNextZeroIndex();
		charFound = false;
		currentIndex = 0;

		//encMsg[ i ] ^= seed;

		// Find char index
		while( charFound == false && currentIndex < CHAR_SET_SIZE * 2 )
		{
			queryChar = ( currentIndex >= CHAR_SET_SIZE ? _mNegativeCharSet[ currentIndex - CHAR_SET_SIZE ] : _mCharSet[ currentIndex ] );
			if( encMsg[ i ] == queryChar )
			{
				charFound = true;
				int queryCharVec = currentIndex >= CHAR_SET_SIZE ? ( ( currentIndex - CHAR_SET_SIZE ) * -1 ) : currentIndex;
				char nextChar = FindCharWithVecFromZero( queryCharVec, zeroIndex );
				decMsg += nextChar;
			}
			currentIndex++;
		}
	}

	return decMsg;
}



// PrivateEncryption
int FirstCryptor::FindVecForCharFromZeroIndex( char c, int zeroIndex )
{
	int globalPos = FindCharGlobalIndex( c );
	if( globalPos == ERROR_CODE )
	{
		return ERROR_CODE;
	}

	globalPos -= zeroIndex;

	return globalPos;
}



// PrivateDecryption

char FirstCryptor::FindCharWithVecFromZero( int vec, int zeroIndex )
{
	int desiredIndex = zeroIndex + vec;

	// Perform wrap around to make decypering harder
	while( desiredIndex >= CHAR_SET_SIZE || desiredIndex < 0 )
	{
		if( desiredIndex >= CHAR_SET_SIZE )
		{
			desiredIndex -= CHAR_SET_SIZE;
		}
		if( desiredIndex < 0 )
		{
			desiredIndex += CHAR_SET_SIZE;
		}
	}

	return _mCharSet[ desiredIndex ];
}


// Utils

int FirstCryptor::FindNextZeroIndex()
{
	return rand() % CHAR_SET_SIZE;
}


int FirstCryptor::FindCharGlobalIndex( char c )
{
	int returnIndex = 0;

	while( _mCharSet[ returnIndex ] != c )
	{
		returnIndex++;
		if( returnIndex >= CHAR_SET_SIZE )
		{
			printf( "%c is not a valid character, you may have:\n", c );
			PrintCharSet();
			return ERROR_CODE;
		}
	}

	return returnIndex;
}

string FirstCryptor::BitwiseShift( string stringToShift, float percentage )
{
	string finalOutput = "";
	int startingValue = ( int ) UINT8_MAX * percentage;

	long test = UINT8_MAX;
	cout << endl << startingValue << " / 255 - UINT8_MAX = " << test << endl;

	for( size_t i = 0; i < stringToShift.size(); i++ )
	{
		finalOutput += stringToShift.at( i ) ^ startingValue % UINT8_MAX;
		//finalOutput.at( i ) << 2;
		if( startingValue >= UINT8_MAX )
		{
			startingValue = 0;
		}
		else
		{
			startingValue += 1;
		}
	}

	return finalOutput;
}


void FirstCryptor::PrintCharSet()
{
	cout << "a - z ( lowercase and uppercase )" << endl;
	cout << "0 - 9" << endl;
	cout << "- _ * + & ^ % $ " << SPECIAL_CHAR_GBP << " ! ? / " << SPECIAL_CHAR_BACKSLASH << " > < @ |   ' : ; ( ) [ ] { } # ~ , ." << endl;
}