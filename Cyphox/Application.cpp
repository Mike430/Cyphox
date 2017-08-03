#include "Application.h"


Application::Application()
{
	_mConsoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleTextAttribute( _mConsoleHandle, BLUE );
	cout << "Thankyou for choosing Cyphox. Please type 'help' for instructions:" << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

	_mQuit = false;
	_mSeed = 0;
}


Application::~Application()
{
}


int Application::RunApplication()
{
	do
	{
		string input;
		input = GetGenericInput();
		if( IsInputValid( input ) != APP_CODE_SUCCESS ) continue;

		if( input == _mCommands[ CMD_QUIT ].first )
		{
			_mQuit = true;
		}
		else if( input == _mCommands[ CMD_DECRYPT ].first )
		{
			cout << "Please enter your encrypted message and we'll decrypt it with the current seed value:" << endl;
			string strToDecrypt;
			strToDecrypt = GetGenericInput();

			cout << "output: " << endl << _mCryptograph.Decrypt( _mSeed, strToDecrypt );
		}
		else if( input == _mCommands[ CMD_ENCRYPT ].first )
		{
			cout << "Please enter your message and we'll encrypt it with the current seed value ( " << _mSeed << " ):" << endl;
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
			SetConsoleTextAttribute( _mConsoleHandle, GREEN );
			cout << "The new seed is: " << _mSeed << endl;
			SetConsoleTextAttribute( _mConsoleHandle, WHITE );
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
	int returnNumber;

	do
	{
		try
		{
			integerStr = GetGenericInput();
			returnNumber = stoi( integerStr );
			isInputValid = true;
		}
		catch( exception e )
		{
			SetConsoleTextAttribute( _mConsoleHandle, RED );
			cout << integerStr << " is not a valid integer, try again:" << endl;
			SetConsoleTextAttribute( _mConsoleHandle, WHITE );
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

	SetConsoleTextAttribute( _mConsoleHandle, RED );
	cout << "You have entered invalid input. Please type 'help' for the manual." << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

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
	SetConsoleTextAttribute( _mConsoleHandle, BLUE );
	cout << "Here are all your possible commands:" << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

	for( pair<string, pair<string, string>> element : _mCommands )
	{
		pair<string, string> elem = element.second;
		cout << "-\t " << elem.first << " = " << elem.second << endl;
	}
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
	SetConsoleTextAttribute( _mConsoleHandle, RED );
	cout << fileAsString << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

	cout << endl << "Decrypted: " << endl;
	SetConsoleTextAttribute( _mConsoleHandle, GREEN );
	cout << _mCryptograph.Decrypt( _mSeed,  fileAsString) << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

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
	SetConsoleTextAttribute( _mConsoleHandle, RED );
	cout << FileLines << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

	cout << endl << "Encrypted: " << endl;
	SetConsoleTextAttribute( _mConsoleHandle, GREEN );
	cout << FileLinesEnc << endl;
	SetConsoleTextAttribute( _mConsoleHandle, WHITE );

	WriteNewTxtFile( outPath, FileLinesEnc );

	return returnCode;
}