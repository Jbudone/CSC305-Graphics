#include <string.h>

using namespace std;

// trim a given line from a scenefile
// trims out spaces, tabs, and comments from left and right ends
static string trim(string line) {
	string trimmed="";
	char buf[1024]; // placeholder for trimmed string
	memset(buf,0,sizeof(buf));
	int captured=0; // length of placeholder

	bool onToken=false;
	for (int i=0; i<line.length(); i++) {
		if ((!onToken && line[i]==' ') || (line[i]=='\t' || line[i]=='\n' || line[i]=='\r')) { onToken=false; continue; } // trimmed
		if (line[i]=='#') break; // comment
		if (line[i]==' ') onToken=false;
		else onToken=true;

		buf[captured]=line[i];
		captured++;
	}

	trimmed=string(buf,captured);
	return trimmed;
}

// gets the first token from a given string (first word)
// NOTE: expects the string to be trimmed already
static string getToken(string line) {
	string token="";
	char buf[1024]; // placeholder for token
	memset(buf,0,sizeof(buf));
	int captured=0; // length of placeholder

	for (int i=0; i<line.length(); i++) {
		if (line[i]==' ' || line[i]=='\r' || line[i]=='\n') break;
		buf[captured]=line[i];
		captured++;
	}

	token=string(buf,captured);
	return token;
}

