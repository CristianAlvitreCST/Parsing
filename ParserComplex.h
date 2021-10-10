/* Project: Parsing
*  Author: Cristian Alvitre
*  Description:
*		ParserComplex is where all "complex" functions in the project go.
*		A complex function is defined as a function that makes use of other functions
*	other than another version of itself within the parser library.
*		For example, basic parser function "foo" being used in function "bar" would make bar "complex"
*/
#pragma once
#include "ParserBasic.h"

//typedef vector<string> associatedValues;
static vector<vector<string>> parserAssociation;

/* Build word lists
*	Builds a word list based on the filename string passed to it
*	TODO: turn these into functions based simply on their return value
*	but I need to differentiate the first two somehow. Rename one maybe?
*/
void buildWordList(string filename, vector<string>& list);
void buildWordList(string filename, vector<vector<string>>& list);
void buildWordList(string filename, vector<vector<string>>& list, char delim);

/* Parsing
*	Functions that perform data parsing to eventually be put into a DAG
*	TODO: Restructure these so that any boilerplate code is removed
*	TODO: Give a better name to worldSalad
*	TODO: stackCreation should be the last part of the process
*/
	//wordSalad - Find matches between the list and the parser, returning them through matches
void wordSalad(vector<vector<string>> list, vector<vector<string>> parser, vector<vector<string>>& matches);
	//redundancyClean - compare sentnces in a list and find if any of them are a complete match. If so, delete the later one
void redundancyClean(vector<vector<string>>& listA);
	//partition - detect forked pathway relationships and turn them into several singular pathed relationships
vector<vector<string>> partition(vector<string> sentence, vector<string> con, vector<string> split);
	//transformToSingle - Take relationships with more than two nodes (ex: x->y->x) and turn them into several l/r relationships
vector<vector<string>> transformToSingle(vector<string> list, vector<string> identifiers);
	//stackCreation - Return the final product
void stackCreation(vector<vector<string>>& sentences, vector<vector<string>>& parser);

/* Other
*	Temporary name, but a place where oddball functions go such as those that are just barely complex functions
*/
void increment(vector<int>& lower, vector<int>& upper);

	//Complex display functions - Only here because they use the basic funciton "reverse" for stack reversal
void display(vector<vector<vector<string>>> dddMat);
void displayEnd(stack<string>& list);