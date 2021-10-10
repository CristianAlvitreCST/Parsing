/*Project: Parsing
* Author: Cristian Alvitre
* Description:
*		ParserBasic is where all "basic" functions in the project go.
*		A basic function is defined as a function that does not make use of other functions
*	other than another version of itself within the library.
*		For example, a function from the <cctype> libary does not make a function "complex"
*		However, a function originally declared within the Parser files that makes use of
*	another function within the library will give it the designation of "complex function"
*		The only exception to the above is in a case such as one present function calling another
*	because its goal is to perform the same action with a different set of methods.
*/
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

/* Informational/Relational
*	Informational - Gives information on specific data not inherently given by the data type being passed
*	Relational - Finds a relationship between two pieces of data even if asymetric(ex: vector<string> and string */
	//Quantity - detects the number of instances of the second argument in the first and their positions
vector<int> quantity(vector<string> sentence, string find);
vector<int> quantity(vector<string> sentence, vector<string> find);

	//Overlap - Determines if there is overlap between two sentences... isn't this just present?
bool overlap(vector<string>& sentence, vector<string>& compliment);

	//Present - Determines the presence of one value in another
bool present(vector<string> list, vector<vector<string>> sentences);
bool present(vector<string> words, vector<string> sentence);
bool present(string word, vector<vector<string>> sentences);
bool present(string word, vector<string> sentence);
bool present(char character, vector<string> sentence);
bool present(string a, char value);

	//Position - Returns the position of one value in another
int position(vector<string> sentence, string find);
int position(vector<string> sentence, string find, int a);

	//maxCount - Determines if the v<i> counter(lower) is at its limit(upper)
bool maxCount(vector<int> lower, vector<int> upper);
	//lowestPossible - Determines if the current position of interest([i]) is the lowest possible value to imcrement
bool lowestPossible(vector<int> lower, vector<int> upper, int i);


/* Manipulators
* Manipulators - Alters the data passed through it based on certain parameters
*/
void resetCounter(vector<int>& counter, int size);
void lowerString(string* convert);
void reverse(stack<vector<string>>& original);
void reverse(stack<string>& list);
void reverseRecursion(int i, vector<int>& tracker, vector<int>& counter);
void recursiveConstruct(int i, vector<int>& tracker, vector<int>& counter, vector<string>& tempVec, vector<vector<vector<string>>>& sentences);


/* Display functions
*	Functions used to output data to the console.
*	I honestly want to replace these with a logger object instead
*	but that isn't a priority right now.
*/
void display(vector<string> list);
void display(vector<vector<string>> list);
void display(stack<vector<string>> list);
void display(stack<string>& list);
void display(vector<int> list);