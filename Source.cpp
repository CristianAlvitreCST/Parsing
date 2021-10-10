#include "Header.h"

int main() {
	vector<vector<string>> parserPhrases;
	vector<vector<string>> list;
	vector<vector<string>> matches;
	
	buildWordList("Documents/Parsing/injury patterns", parserPhrases);
	buildWordList("Documents/Sources/injury", list, '.');
	
	wordSalad(list, parserPhrases, matches);
	redundancyClean(matches);
	//partition();
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