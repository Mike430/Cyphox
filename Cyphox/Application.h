#pragma once
#include <iostream>
#include <string>
#include <map>
#include <windows.h>
#include <fstream>
#include <ctime>

#include "FirstCryptor.h"

using namespace std;

#define CMD_QUIT "0_QUIT"
#define CMD_DECRYPT "1_DECRYPT"
#define CMD_ENCRYPT "2_ENCRYPT"
#define CMD_DECRYPT_FILE "3_DECRYPT_FILE"
#define CMD_ENCRYPT_FILE "4_ENCRYPT_FILE"
#define CMD_SET_SEED "5_SET_SEED"
#define CMD_HELP "6_HELP"

typedef enum AppStatusCode
{
	APP_CODE_SUCCESS = 0,
	APP_CODE_FAILURE_GENERIC = 1
};

typedef enum ConsoleColours
{
	COLOUR_GREEN = 10,
	COLOUR_BLUE = 11,
	COLOUR_RED = 12,
	COLOUR_PURPLE = 13,
	COLOUR_YELLOW = 14,
	COLOUR_WHITE = 15
};

class Application
{
private:
	map<string, pair<string, string>> _mCommands = {
		{ CMD_QUIT, {"quit", "This will shutdown this application."} },
		{ CMD_DECRYPT, {"decrypt", "This will prompt an input for decryption."} },
		{ CMD_ENCRYPT, {"encrypt", "This will prompt an input for encryption." } },
		{ CMD_DECRYPT_FILE, {"decryptFile", "This will decrypt a previously encrypted .txt file."}},
		{ CMD_ENCRYPT_FILE, {"encryptFile", "This will encrypt a unencrypted .txt file."}},
		{ CMD_SET_SEED, {"seed", "This will prompt an input for the seed value." } },
		{ CMD_HELP, {"help", "This will print the guide you're currently reading." } }
	};

	HANDLE _mConsoleHandle;
	bool _mQuit;
	uint64_t _mSeed;
	FirstCryptor _mCryptograph;

	string GetGenericInput();
	int RetriveValidNumberInput();
	AppStatusCode IsInputValid( string input );

	string ReadInFileAsStr(string path);
	AppStatusCode WriteNewTxtFile( string outPath, string content);
	AppStatusCode IsGivenPathValid(string path);
	AppStatusCode DecryptTxtFile(string path);
	AppStatusCode EncryptTxtFile(string inPath, string outPath);
	void PrintHelp();
public:
	Application();
	~Application();

	int RunApplication();
};