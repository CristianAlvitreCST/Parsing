#include "Header.h"

int main() {
	vector<vector<string>> parserPhrases;
	vector<vector<string>> list;
	vector<vector<string>> matches;
	vector<vector<string>> tempMat;// , tempMat_2;
	vector<string> ignore, stop, con;
	
	buildWordList("Documents/Parsing/injury patterns", parserPhrases);
	buildWordList("Documents/Sources/injury", list, '.');
	buildWordList("Documents/Parsing/ignore", ignore);
	buildWordList("Documents/Parsing/stop", stop);
	buildWordList("Documents/Parsing/conjunctional", con);

	wordSalad(list, parserPhrases, matches);
	redundancyClean(matches);
	matches = partition(matches, con, stop);
	display(matches);

	//transformToSingle();
	stackCreation(matches, parserPhrases);
	/*
	wordSalad(); //find matching parsePhrases
	redundancyClean(); //remove redundant phrases
	partition(); //split node relations into single branch paths
	transformToSingle(); //Turns phrases with more than two nodes into simple l/r phrases
	stackCreation(); //Use behavior to determine output
	*/
	return 0;
}