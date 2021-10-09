#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stack>

using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stack;

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

	// Data validation
	// genericize the present functions
//Present - detects presence of one argument in another, but not position
bool overlap(vector<string>& sentence, vector<string>& compliment);
//Templateable? It's possible
bool present(vector<string> list, vector<vector<string>> sentences);
bool present(vector<string> words, vector<string> sentence);
bool present(string word, vector<vector<string>> sentences);
bool present(string word, vector<string> sentence);
bool present(char character, vector<string> sentence);
bool present(string a, char value);
void recursiveConstruct(int i, vector<int>& tracker, vector<int>& counter, vector<string>& tempVec, vector<vector<vector<string>>>& sentences);
void reverseRecursion(int i, vector<int>& tracker, vector<int>& counter);
bool maxCount(vector<int> lower, vector<int> upper);
bool lowestPossible(vector<int> lower, vector<int> upper, int i);

//Position - detects position of the second argument in the first, the third argument being to start from that position. -1 signifies the lack of a variable's presence
int position(vector<string> sentence, string find);
int position(vector<string> sentence, string find, int a);

//Quantity - detects the number of instances of the second argument in the first and their positions
vector<int> quantity(vector<string> sentence, string find);
vector<int> quantity(vector<string> sentence, vector<string> find);

	//Display functions
void display(vector<string> list);
void display(vector<vector<string>> list);
void display(stack<vector<string>> list);
void display(stack<string>& list);
void display(vector<vector<vector<string>>> dddMat);
void displayEnd(stack<string>& list);
void display(vector<int> list);

	//Data manipulation
vector<vector<string>> transformToSingle(vector<string> list, vector<string> identifiers);
vector<vector<string>> partition(vector<string> sentence, vector<string> con, vector<string> split);
void increment(vector<int>& lower, vector<int>& upper);
void resetCounter(vector<int>& counter, int size);
void lowerString(string* convert);
void reverse(stack<vector<string>>& original);
void reverse(stack<string>& list);