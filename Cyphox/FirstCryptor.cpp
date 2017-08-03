#include "FirstCryptor.h"


char FirstCryptor::_mCharSet[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'-', '_', '*', '+', '&', '^', '%', '$', SPECIAL_CHAR_GBP, '!', '?', '/', SPECIAL_CHAR_BACKSLASH, '>', '<', '@', '|', ' ', '\'',	':', ';', '\(', '\)', '\[', '\]', '\{', '\}', '\#', '\~', ',', '.', '\n', '\r'
};


FirstCryptor::FirstCryptor()
{
}


FirstCryptor::~FirstCryptor()
{
}


string FirstCryptor::Encrypt( uint64_t seed, string decMsg )
{
	string encMsg = "";
	srand( seed );
	//srand( UINT64_MAX );
	for( int i = 0; i < decMsg.length(); i++ )
	{
		int ZeroIndex = FindNextZeroIndex();
		int charPos = FindVecForCharFromZeroIndex( decMsg.at( i ), ZeroIndex );
		if( charPos == ERROR_CODE )
		{
			return "\nEncryption abandoned due to unqualified character\n";
		}
		encMsg = AppendEnc( encMsg, charPos );
	}

	return encMsg;
}


string FirstCryptor::Decrypt( uint64_t seed, string encMsg )
{
	string decMsg = "";
	srand( seed );

	while( encMsg.length() > 0 )
	{
		vector<string> catcher = BreakStringInTwo( encMsg, _mSeparator );

		if( catcher.size() != 2 )
		{
			decMsg = "Decryption Aborted.";
			break;
		}

		string nextString = catcher.at( 0 );
		encMsg = catcher.at( 1 );

		int nextNumber;
		istringstream( nextString ) >> nextNumber;//when encryption abandoned this returns -858993460
		int zeroIndex = FindNextZeroIndex();
		char nextChar = FindCharWithVecFromZero( nextNumber, zeroIndex );
		decMsg += nextChar;
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
	while( desiredIndex >= _mCharSetLength || desiredIndex < 0 )
	{
		if( desiredIndex >= _mCharSetLength )
		{
			desiredIndex -= _mCharSetLength;
		}
		if( desiredIndex < 0 )
		{
			desiredIndex += _mCharSetLength;
		}
	}

	return _mCharSet[ desiredIndex ];
}


// Utils

int FirstCryptor::FindNextZeroIndex()
{
	return rand() % _mCharSetLength;
}


int FirstCryptor::FindCharGlobalIndex( char c )
{
	int returnIndex = 0;

	while( _mCharSet[ returnIndex ] != c )
	{
		returnIndex++;
		if( returnIndex >= _mCharSetLength )
		{
			printf( "%c is not a valid character, you may have:\n", c );
			PrintCharSet();
			return ERROR_CODE;
		}
	}

	return returnIndex;
}


string FirstCryptor::AppendEnc( string base, int extension )
{
	return base + to_string( extension ) + _mSeparator;
}


void FirstCryptor::PrintCharSet()
{
	cout << "a - z ( lowercase and uppercase )" << endl;
	cout << "0 - 9" << endl;
	cout << "- _ * + & ^ % $ " << SPECIAL_CHAR_GBP << " ! ? / " << SPECIAL_CHAR_BACKSLASH << " > < @ |   ' : ; ( ) [ ] { } # ~ , ." << endl;
}


vector<string> FirstCryptor::BreakStringInTwo( string str, string target )
{
	// http://www.cplusplus.com/forum/beginner/85856/
	// http://stackoverflow.com/questions/1181079/stringsize-type-instead-of-int
	// Using unsigned int to maximise size and allow manipulation over string::size_type

	vector<string> returnVal;
	unsigned int firstCutPos = str.find( target );

	if( firstCutPos == UINT_MAX )
	{
		cout << DecryptionErrorMSG << endl;
		return returnVal;
	}
	returnVal.push_back( str.substr( 0, firstCutPos ) );
	firstCutPos += target.length();
	returnVal.push_back( str.substr( firstCutPos, str.length() ) );
	return returnVal;
}