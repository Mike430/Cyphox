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

			_mCryptograph.Decrypt( strToDecrypt );
		}
		else if( input == _mCommands[ CMD_ENCRYPT ].first )
		{
			cout << "Please enter your message and we'll encrypt it with the current seed value ( " << _mSeed << " ):" << endl;
			string strToEncrypt;
			strToEncrypt = GetGenericInput();

			cout << "We're going for: " << strToEncrypt << endl;
			_mCryptograph.Encrypt( _mSeed, strToEncrypt );
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