#include "Application.h"


Application::Application()
{
	_mConsoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );
	cout << "Thank you for choosing Cyphox!" << endl << endl;
	PrintHelp();

	_mQuit = false;
	srand( time(NULL) );
	_mSeed = rand() % UINT64_MAX;// first number is always tighed t the system time
	_mSeed = rand() % UINT64_MAX;
}


Application::~Application()
{
}


int Application::RunApplication()
{
	do
	{
		SetConsoleTextAttribute( _mConsoleHandle, COLOUR_YELLOW );
		cout << endl << "Don't forget to update your seed! Your current seed is: " << _mSeed << endl;
		SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

		string input;
		input = GetGenericInput();
		if( IsInputValid( input ) != APP_CODE_SUCCESS ) continue;

		if( input == _mCommands[ CMD_QUIT ].first )
		{
			_mQuit = true;
		}
		else if( input == _mCommands[ CMD_DECRYPT ].first )
		{
			cout << "Please enter your encrypted message and we'll decrypt:" << endl;
			string strToDecrypt;
			strToDecrypt = GetGenericInput();

			cout << "output: " << endl << _mCryptograph.Decrypt( _mSeed, strToDecrypt );
		}
		else if( input == _mCommands[ CMD_ENCRYPT ].first )
		{
			cout << "Please enter your message and we'll encrypt it:" << endl;
			string strToEncrypt;
			strToEncrypt = GetGenericInput();

			cout << "output: " << endl << _mCryptograph.Encrypt( _mSeed, strToEncrypt );
		}
		else if( input == _mCommands[ CMD_DECRYPT_FILE ].first )
		{
			string inPath;
			bool inputOkay = false;

			while( !inputOkay )
			{
				cout << "Please enter the complete filepath and txt file name so we can decrypt it.";
				inPath = GetGenericInput();
				inputOkay = APP_CODE_SUCCESS == IsGivenPathValid( inPath );//C:\Users\ymike\Desktop\MyPasswords.txt
			}


			DecryptTxtFile( inPath );
		}
		else if( input == _mCommands[ CMD_ENCRYPT_FILE ].first )
		{
			string inPath;
			string outPath;
			bool inputOkay = false;

			while( !inputOkay )
			{
				cout << "Please enter the complete filepath and txt file name so we can decrypt it.";
				inPath = GetGenericInput();
				inputOkay = APP_CODE_SUCCESS == IsGivenPathValid( inPath );//C:\Users\ymike\Desktop\MyPasswords.txt
			}

			inputOkay = false;

			while( !inputOkay )
			{
				cout << "Please enter the complete filepath and file name for where you would like the output to go.";
				outPath = GetGenericInput();
				inputOkay = APP_CODE_SUCCESS == IsGivenPathValid( outPath );//C:\Users\ymike\Desktop\CyphoxOutput.txt
			}

			EncryptTxtFile( inPath, outPath );
		}
		else if( input == _mCommands[ CMD_SET_SEED ].first )
		{
			_mSeed = RetriveValidNumberInput();
			SetConsoleTextAttribute( _mConsoleHandle, COLOUR_GREEN );
			cout << "The new seed is: " << _mSeed << endl;
			SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );
		}
		else if( input == _mCommands[ CMD_HELP ].first )
		{
			PrintHelp();
		}
		
	} while( !_mQuit );

	return APP_CODE_SUCCESS;
}


string Application::GetGenericInput()
{
	cout << endl << ">_ ";
	string returnString;
	getline( cin, returnString );
	return returnString;
}


int Application::RetriveValidNumberInput()
{
	cout << "Please enter an integer" << endl;

	bool isInputValid = false;
	string integerStr;
	uint64_t returnNumber;

	do
	{
		try
		{
			integerStr = GetGenericInput();
			returnNumber = stoull( integerStr );
			isInputValid = true;
		}
		catch( exception e )
		{
			SetConsoleTextAttribute( _mConsoleHandle, COLOUR_RED );
			cout << integerStr << " is not a valid integer, try again:" << endl;
			SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );
			isInputValid = false;
		}
	} while( !isInputValid );

	return returnNumber;
}


AppStatusCode Application::IsInputValid( string input )
{
	for( auto element : _mCommands )
	{
		if( element.second.first == input )
		{
			return APP_CODE_SUCCESS;
		}
	}

	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_RED );
	cout << "You have entered invalid input. Please type 'help' for the manual." << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

	return APP_CODE_FAILURE_GENERIC;
}


AppStatusCode Application::IsGivenPathValid( string path )
{
	ifstream file( path );

	if( !file )//|| !file.is_open  )
	{
		cout << "Filepath is invalid." << endl;
		return APP_CODE_FAILURE_GENERIC;
	}
	else
	{
		file.close();
		return APP_CODE_SUCCESS;
	}
}


void Application::PrintHelp()
{
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_BLUE );
	cout << "Here are all your possible commands:" << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

	for( pair<string, pair<string, string>> element : _mCommands )
	{
		pair<string, string> elem = element.second;
		cout << "-\t " << elem.first << " = " << elem.second << endl;
	}

	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_RED );
	cout << endl << "IMPORTANT NOTICE:" << endl;
	cout << "- Assert your seed value is what you want before running any commands!" << endl;
	cout << "- All commands involving cryptography use the current seed value." << endl;
	cout << "- A seed will be randomly generated every time Cyphox is started." << endl;
	cout << "- The seed can be any number between 0 and " << UINT64_MAX << " (a positive 64 bit integer)." << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );
}


string Application::ReadInFileAsStr( string path )
{
	ifstream file( path, std::ios::ate | std::ios::binary );
	size_t fileSize = ( size_t ) file.tellg();
	std::vector<char> buffer( fileSize );
	file.seekg( 0 );
	file.read( buffer.data(), fileSize );

	string txtFileLines = "";

	for( int i = 0; i < buffer.size(); i++ )
	{
		txtFileLines += buffer.at( i );
	}

	file.close();

	return txtFileLines;
}


AppStatusCode Application::WriteNewTxtFile( string outPath, string content )
{
	ofstream newFile( outPath, std::ios::ate | std::ios::binary );

	newFile.write( content.c_str(), content.size() );
	newFile.close();
	return APP_CODE_SUCCESS;
}



AppStatusCode Application::DecryptTxtFile( string path )
{
	AppStatusCode returnCode = APP_CODE_SUCCESS;
	string fileAsString = ReadInFileAsStr( path );

	cout << endl << "Original: " << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_RED );
	cout << fileAsString << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

	cout << endl << "Decrypted: " << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_GREEN );
	cout << _mCryptograph.Decrypt( _mSeed,  fileAsString) << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

	return returnCode;
}


AppStatusCode Application::EncryptTxtFile( string inPath, string outPath )
{
	AppStatusCode returnCode = APP_CODE_SUCCESS;

	string FileLines = ReadInFileAsStr( inPath );
	string FileLinesEnc = {};

	for( int i = 0; i < FileLines.size(); i++ )
	{
		FileLinesEnc = _mCryptograph.Encrypt( _mSeed, FileLines );
	}

	cout << endl << "Original: " << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_RED );
	cout << FileLines << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

	cout << endl << "Encrypted: " << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_GREEN );
	cout << FileLinesEnc << endl;
	SetConsoleTextAttribute( _mConsoleHandle, COLOUR_WHITE );

	WriteNewTxtFile( outPath, FileLinesEnc );

	return returnCode;
}