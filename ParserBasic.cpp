#include "ParserBasic.h"
/*
* Project: Parsing
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

/* Informational/Relational
*	Informational - Gives information on specific data not inherently given by the data type being passed
*	Relational - Finds a relationship between two pieces of data even if asymetric(ex: vector<string> and string */
vector<int> quantity(vector<string> sentence, string find) {
	vector<int> temp;
	for (int i = 0; i < sentence.size(); i++) {
		if (sentence[i] == find) {
			temp.push_back(i);
		}
	}
	return temp;
}
vector<int> quantity(vector<string> sentence, vector<string> find)
{
	vector<int> retVal, temp;
	for (int i = 0; i < find.size(); i++) {
		temp = quantity(sentence, find[i]);
		retVal.insert(retVal.end(), temp.begin(), temp.end());
		temp.clear();
	}
	return retVal;
}

bool overlap(vector<string>& sentence, vector<string>& compliment) {
	for (int i = 0; i < sentence.size(); i++) {
		for (int g = 0; g < compliment.size(); g++) {
			if (sentence[i] == compliment[g]) {
				return true;
			}
		}
	}
	return false;
}

bool present(vector<string> words, vector<string> sentence) {
	for (int i = 0; i < words.size(); i++) {
		if (present(words[i], sentence)) {
			return true;
		}
	}
	return false;
}
bool present(vector<string> list, vector<vector<string>> sentences)
{
	for (int a = 0; a < list.size(); a++) {
		if (present(list[a], sentences)) {
			return true;
		}
	}
	return false;
}
bool present(string word, vector<vector<string>> sentences) {
	for (int a = 0; a < sentences.size(); a++) {
		if (present(word, sentences[a])) {
			return true;
		}
	}
	return false;
}
bool present(string word, vector<string> sentence) {
	vector<string>::iterator parseI;
	for (parseI = sentence.begin(); parseI != sentence.end(); parseI++) {
		if (*parseI == word) {
			return true;
		}
	}
	return false;
}
bool present(char character, vector<string> sentence)
{
	for (int i = 0; i < sentence.size(); i++) {
		for (int g = 0; g < sentence[i].size(); g++)
			if (character == sentence[i][g]) {
				return true;
			}
	}
	return false;
}
bool present(string a, char value) {
	if (a.find(value) < a.size() && a.find(value) >= 0) {
		return true;
	}
	else {
		return false;
	}
}

int position(vector<string> sentence, string find) {
	for (int pos = 0; pos < sentence.size(); pos++) {
		if (find == sentence[pos]) {
			return pos;
		}
	}
	return -1;
}
int position(vector<string> sentence, string find, int a) {
	if (a > sentence.size()) {
		return -1;
	}
	for (int pos = a; pos < sentence.size(); pos++) {
		if (find == sentence[pos]) {
			return pos;
		}
	}
	return -1;
}

bool maxCount(vector<int> lower, vector<int> upper)
{
	for (int i = 0; i < lower.size() && i < upper.size(); i++) {
		if (lower[i] < upper[i] - 1) {
			return false;
		}
	}
	return true;
}
bool lowestPossible(vector<int> lower, vector<int> upper, int i)
{
	if (i >= lower.size() - 1) {
		return true;
	}
	for (int g = i + 1; g < lower.size(); g++) {
		if (lower[g] < upper[g] - 1) {
			return false;
		}
	}
	return true;
}

/* Manipulators
* Manipulators - Alters the data passed through it based on certain parameters
*/
void resetCounter(vector<int>& counter, int size)
{
	counter.clear();
	counter.resize(size);
}
void lowerString(string* convert) {
	transform(convert->begin(), convert->end(), convert->begin(), ::tolower);
}
void reverse(stack<vector<string>>& original) {
	stack<vector<string>> copy;
	while (!original.empty()) {
		copy.push(original.top());
		original.pop();
	}
	original = copy;
}
void reverse(stack<string>& list) {
	stack<string> copy;
	while (!list.empty()) {
		copy.push(list.top());
		list.pop();
	}
	list = copy;
}
void reverseRecursion(int i, vector<int>& tracker, vector<int>& counter) {
	if (i != 0) {
		if (counter[i] + 1 < tracker[i]) {

		}

		i--;
		reverseRecursion(i, tracker, counter);
	}
}
void recursiveConstruct(int i, vector<int>& tracker, vector<int>& counter, vector<string>& tempVec, vector<vector<vector<string>>>& sentences)
{
	if (i < sentences.size()) {
		tempVec.insert(tempVec.end(), sentences[i][counter[i]].begin(), sentences[i][counter[i]].end()); //Exception
		if (i != sentences.size() - 1) {
			tempVec.push_back("affects");
		}
		i++;
		recursiveConstruct(i, tracker, counter, tempVec, sentences);
	}
}

/* Display functions
*	Functions used to output data to the console.
*	I honestly want to replace these with a logger object instead
*	but that isn't a priority right now.
*/
void display(vector<string> list) {
	vector<string>::iterator i;
	for (i = list.begin(); i != list.end(); ++i) {
		if (i->empty()) {
			cout << "[] ";
		}
		else {
			cout << *i << " ";
		}
	}
	cout << endl;
}
void display(vector<vector<vector<string>>> dMat) {
	for (vector<vector<vector<string>>>::iterator sentences = dMat.begin(); sentences != dMat.end(); sentences++) {
		for (vector<vector<string>>::iterator middle = sentences->begin(); middle != sentences->end(); middle++) {
			cout << "[";
			for (vector<string>::iterator word = middle->begin(); word != middle->end(); word++) {
				cout << *word << " ";
			}
			cout << "]";
		}
		cout << endl;
	}
}
void display(stack<vector<string>> list) {
	vector<string> temp;
	while (!list.empty()) {
		temp = list.top();
		list.pop();
		cout << "(";
		for (int i = 0; i < temp.size(); i++) {
			cout << temp[i] << " ";
		}
		cout << ")";
	}
	cout << endl;
}
void display(vector<vector<string>> list) {
	vector<vector<string>>::iterator i;
	for (i = list.begin(); i != list.end(); ++i) {
		display(*i);
	}
	cout << endl;
}
void display(vector<int> list) {
	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << " ";
	}
	cout << endl;
}