#pragma once
#include "Parser.h"

typedef struct _node {
	string subject;
	vector<string> edges;
} node;

void match(vector<string>& sentence, vector<string>& parser, vector<string>::iterator& sentenceI, vector<string>::iterator& parserI, vector<string>& nodes);
void sentenceCompare(vector<string>& sentence, vector<string>& parser, vector<string>& nodes);

void redundancyCorrection(vector<vector<string>>& list);
void redundancyCorrection(vector<node>& list);

bool redundancyCheck(vector<node> list);
bool redundancyCheck(vector<string> list);
bool redundancyCheck(vector<vector<string>> list);
bool redundancyCheck(node list);
bool redundancyCheck(vector<vector<node>> list);

bool ignoreWord(string word);
void nodeCreation(vector<vector<string>>& sentences, vector<vector<string>>& parser, vector<string> stopWords);
bool compareSentences(vector<string> left, vector<string> right);
void findConnection(vector<vector<string>>& list, vector<vector<string>>& parser, vector<string>& nodes);

void display(vector<node> list);
void splitChars(stack<vector<string>>& theStack);
int quantityOld(vector<string> sentence, string find);
string combineString(vector<string> value);
void cleanStack(stack<vector<string>>& sCopy, vector<string> removeMe);