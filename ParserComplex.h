#pragma once
#include "ParserBasic.h"

//typedef vector<string> associatedValues;
static vector<vector<string>> parserAssociation;

	//Build word lists
	//I want to turn these into functions based simply on their return value, but I need to differentiate the first two somehow. Rename one maybe?
void buildWordList(string filename, vector<string>& list);
void buildWordList(string filename, vector<vector<string>>& list);
void buildWordList(string filename, vector<vector<string>>& list, char delim);

	//Parsing
	//Restructure these so that any boilerplate code is removed, give a better name to worldSalad
void wordSalad(vector<vector<string>> list, vector<vector<string>> parser, vector<vector<string>>& matches);
void stackCreation(vector<vector<string>>& sentences, vector<vector<string>>& parser);
void redundancyClean(vector<vector<string>>& listA);

//Data manipulation
vector<vector<string>> transformToSingle(vector<string> list, vector<string> identifiers);
vector<vector<string>> partition(vector<string> sentence, vector<string> con, vector<string> split);
void increment(vector<int>& lower, vector<int>& upper);

//Complex display functions
void display(vector<vector<vector<string>>> dddMat);
void displayEnd(stack<string>& list);