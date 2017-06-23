#pragma once
#include <iostream>
#include <string>
#include <map>
#include <windows.h>
#include "FirstCryptor.h"

using namespace std;

#define CMD_QUIT "0_QUIT"
#define CMD_DECRYPT "1_DECRYPT"
#define CMD_ENCRYPT "2_ENCRYPT"
#define CMD_SET_SEED "3_SET_SEED"
#define CMD_HELP "4_HELP"

typedef enum AppStatusCode
{
	APP_CODE_SUCCESS = 0,
	APP_CODE_FAILURE_GENERIC = 1
};

typedef enum ConsoleColours
{
	GREEN = 10,
	BLUE = 11,
	RED = 12,
	PURPLE = 13,
	YELLOW = 14,
	WHITE = 15
};

class Application
{
private:
	map<string, pair<string, string>> _mCommands = {
		{ CMD_QUIT, {"quit", "This will shutdown this application."} },
		{ CMD_DECRYPT, {"decrypt", "This will prompt an input for decryption."} },
		{ CMD_ENCRYPT, {"encrypt", "This will prompt an input for encryption." } },
		{ CMD_SET_SEED, {"seed", "This will prompt an input for the seed value. This defines the randomisation for the encryption and decryption system and will not change until this command is run again." } },
		{ CMD_HELP, {"help", "This will print the guide you're currently reading." } }
	};

	HANDLE _mConsoleHandle;
	bool _mQuit;
	int _mSeed;
	FirstCryptor _mCryptograph;

	string GetGenericInput();
	int RetriveValidNumberInput();
	AppStatusCode IsInputValid( string input );
	void PrintHelp();
public:
	Application();
	~Application();

	int RunApplication();
};