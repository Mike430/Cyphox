#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include "FirstCryptor.h"
#include "Application.h"

using namespace std;

int main()
{
	/*FirstCryptor fc;

	string msg1 = "5ecret_Me55age-87iO0883";
	string msg2 = "<Astar_Light\>";
	string msg3 = "Fiddle$$St1cks";
	string msg4 = "Ch@ty-1";
	string dud = "/9/-65/1/-9/13/21/9/"; // supposed to be 8103/9/-65/1/-9/13/21/9/
	int seed1 = 0;
	int seed2 = 27;
	int seed3 = 110;
	int seed4 = 8103;
	string encMsg1;
	string encMsg2;
	string encMsg3;
	string encMsg4;

	encMsg1 = fc.Encrypt( seed1, msg1 );
	encMsg2 = fc.Encrypt( seed2, msg2 );
	encMsg3 = fc.Encrypt( seed3, msg3 );
	encMsg4 = fc.Encrypt( seed4, msg4 );

	fc.Decrypt( encMsg1 );
	fc.Decrypt( encMsg2 );
	fc.Decrypt( encMsg3 );
	fc.Decrypt( encMsg4 );
	fc.Decrypt( dud );

	system( "pause" );*/


	Application app = {};
	return app.RunApplication();
}