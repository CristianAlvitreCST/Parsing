#pragma once
#include "Parser.h"

	//Build word list
void buildWordList(string filename, vector<string>& list)
{
	string* strPtr;
	string tag = ".txt";
	for (int i = filename.size() - tag.size(), g = 0; i < filename.size(); i++, g++) {
		if (filename[i] != tag[g]) {
			filename += tag;
			break;
		}
	}

	ifstream input(filename);
	while (!input.eof()) {
		input >> filename;
		strPtr = &filename;
		lowerString(strPtr);
		list.push_back(filename);
	}
	input.close();
}
void buildWordList(string filename, vector<vector<string>>& list) { //Used by: Parser list
	string* strPtr;
	string tag = ".txt";
	string word;
	for (int i = filename.size() - tag.size(), g = 0; i < filename.size(); i++, g++) {
		if (filename[i] != tag[g]) {
			filename += tag;
			break;
		}
	}

	int i = 0;
	ifstream input(filename);
	while (!input.eof()) {
		vector<string> temp, blank;
		while (std::getline(input, word))
		{
			strPtr = &word;
			lowerString(strPtr);
			std::istringstream sentence(word);
			while (sentence >> word) { //Temp has words from the string stream pushed onto it.
				temp.push_back(word);
			}
			list.push_back(blank);
			list[i] = std::move(temp);
			i++;
		}
	}
	input.close();
	for (int a = 0; a < list.size(); a++) {
		for (int b = 0; b < list[a].size(); b++) {
			if (!list[a][b].empty()) {
				if (present(list[a][b], '[') && present(list[a][b], ']')) {
					int beg = list[a][b].find_first_of('[');
					int end = list[a][b].find_last_of(']');
					//cout << "Before: " << list[a][b] << endl;
					if (end != list[a][b].size()) {
						list[a][b].erase(list[a][b].begin() + beg, list[a][b].begin() + end + 1);
					}
					else {
						list[a][b].clear();
					}
					//cout << "After: " << list[a][b] << endl;
				}
				if (present(list[a][b], '(')) {
					//cout << "Before: " << list[a][b] << endl;
					int take = list[a][b].find_first_of('(');
					list[a][b].erase(list[a][b].begin() + take);
					//cout << "After: " << list[a][b] << endl;
				}
				if (present(list[a][b], ')')) {
					//cout << "Before: " << list[a][b] << endl;
					int take = list[a][b].find_first_of(')');
					list[a][b].erase(list[a][b].begin() + take);
					//cout << "After: " << list[a][b] << endl;
				}
				if (list[a][b].size() == 0) {
					list[a][b].clear();
				}
			}
		}
	}
}
void buildWordList(string filename, vector<vector<string>>& list, char delim) { //Used by the main list
	string* strPtr;
	string tag = ".txt";
	string word;
	for (int i = filename.size() - tag.size(), g = 0; i < filename.size(); i++, g++) {
		if (filename[i] != tag[g]) {
			filename += tag;
			break;
		}
	}

	int i = 0;
	ifstream input(filename);
	while (!input.eof()) {
		vector<string> temp, blank;
		while (std::getline(input, word, delim))
		{
			strPtr = &word;
			lowerString(strPtr);
			std::istringstream sentence(word);
			while (sentence >> word) { //Temp has words from the string stream pushed onto it.
				temp.push_back(word);
			}
			list.push_back(blank);
			list[i] = std::move(temp);
			i++;
		}
	}
	input.close();
	for (int a = 0; a < list.size(); a++) {
		for (int b = 0; b < list[a].size(); b++) {
			if (!list[a][b].empty()) {
				if (present(list[a][b], '[') && present(list[a][b], ']')) {
					int beg = list[a][b].find_first_of('[');
					int end = list[a][b].find_last_of(']');
					// << "Before: " << list[a][b] << endl;
					if (end != list[a][b].size()) {
						list[a][b].erase(list[a][b].begin() + beg, list[a][b].begin() + end + 1);
					}
					else {
						list[a][b].clear();
					}
					//cout << "After: " << list[a][b] << endl;
				}
				if (present(list[a][b], '(')) {
					//cout << "Before: " << list[a][b] << endl;
					int take = list[a][b].find_first_of('(');
					list[a][b].erase(list[a][b].begin() + take);
					//cout << "After: " << list[a][b] << endl;
				}
				if (present(list[a][b], ')')) {
					//cout << "Before: " << list[a][b] << endl;
					int take = list[a][b].find_first_of(')');
					list[a][b].erase(list[a][b].begin() + take);
					//cout << "After: " << list[a][b] << endl;
				}
				if (list[a][b].size() == 0) {
					list[a][b].clear();
				}
			}
		}
	}
}

	//Parsing
void wordSalad(vector<vector<string>> list, vector<vector<string>> parser, vector<vector<string>>& matches)
{	
	for (vector<vector<string>>::iterator listIt = list.begin(); listIt != list.end(); listIt++) {
		for (vector<vector<string>>::iterator parseIt = parser.begin(); parseIt != parser.end(); parseIt++) {
			bool flag = true;
			for (vector<string>::iterator wordIt = parseIt->begin(); wordIt != parseIt->end(); wordIt++) {
				if (!present(*wordIt, *listIt) && !wordIt->empty()) {
					flag = false;
					break;
				}
			}
			if (flag) {
				//parserAssociation.push_back(*parseIt);
				matches.push_back(*listIt);
			}
		}
	}
	//This should be redone so that there's only one level of complex functions
	stackCreation(matches, parser);
}

/*Keep pushing words onto a stack until a condition is met
* There are two checks when adding
* 1. Is the word a filter word.		Filter words are ignored, but the stack continues to be added on to
* 2. Is the word a stop word.		Stop words trigger the displaying of the stack, and its subsequent clearing*/
void stackCreation(vector<vector<string>>& sentences, vector<vector<string>>& parser) {
	vector<vector<string>> matrix, tempMat;
	stack<string> theStack;
	vector<string> ignore, stop, con, tempVec; //Ignore for words to move past, stop for words to trigger a stop
	string tempStr;
	vector<int> andPos, affectPos;
	int a, split;

	redundancyClean(sentences);

	buildWordList("Documents/Parsing/ignore", ignore);
	buildWordList("Documents/Parsing/stop", stop);
	buildWordList("Documents/Parsing/conjunctional", con);

	//display(sentences);
	for (int i = 0; i < sentences.size(); i++) {
		tempMat = partition(sentences[i], con, stop);
		matrix.insert(matrix.end(), tempMat.begin(), tempMat.end());
	}
	//display(matrix);
	for (int i = 0; i < matrix.size(); i++) {
		transformToSingle(matrix[i], stop);
	}

	tempMat = matrix;
	matrix.clear();
	sentences = tempMat;
	//display(sentences);
	for (int i = 0; i < sentences.size(); i++) {
		for (int g = 0; g < sentences[i].size(); g++) {
			if (!present(sentences[i][g], ignore)) {
				if (!present(sentences[i][g], stop)) {
					if (present(sentences[i][g], con)) {
						for (int j = g + 1; j < sentences[i].size(); j++) {
							tempVec.push_back(sentences[i][j]);
						}
						matrix.push_back(tempVec);
						tempVec.clear();
						int j = g;
						while (!present(sentences[i][j], con) && !present(sentences[i][j], stop) && j <= sentences[i].size() - 1) {
							j++;
						}
						sentences[i].erase(sentences[i].begin() + g, sentences[i].begin() + j);
					}
					//Add to the stack
					theStack.push(sentences[i][g]);
				} else {
					//Pop off the stack
					display(theStack);
				}
			}
		}
		//Display and pop off the remainder
		displayEnd(theStack);
	}
}

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

void redundancyClean(vector<vector<string>>& listA)
{
	for (int x = listA.size(); x > 0; x--) {
		bool flag;
		for (int i = 0; i < listA.size(); i++) {
			for (int g = i + 1; g < listA.size(); g++) {
				flag = true;
				for (int j = 0; j < listA[i].size(); j++) {
					if (!present(listA[i][j], listA[g])) {
						flag = false;
						break;
					}
				}
				if (flag) {
					listA.erase(listA.begin() + g);
				}
			}
		}
	}
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

//Data validation
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
	if (a > sentence.size()){
		return -1;
	}
	for (int pos = a; pos < sentence.size(); pos++) {
		if (find == sentence[pos]) {
			return pos;
		}
	}
	return -1;
}


	//Display Functions
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
void display(stack<string>& list) {
	reverse(list);
	while (!list.empty()) {
		cout << list.top() << " ";
		list.pop();
	}
	cout << "-> ";
}

void displayEnd(stack<string>& list) {
	reverse(list);
	while (!list.empty()) {
		cout << list.top() << " ";
		list.pop();
	}
	cout << endl;
}

void resetCounter(vector<int>& counter, int size)
{
	counter.clear();
	counter.resize(size);
}


//String Manipulation
void lowerString(string* convert) {
	transform(convert->begin(), convert->end(), convert->begin(), ::tolower);
}

void reverse(stack<vector<string>>& original) {
	stack<vector<string>> copy;
	while(!original.empty()) {
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

bool maxCount(vector<int> lower, vector<int> upper)
{
	for (int i = 0; i < lower.size() && i < upper.size(); i++) {
		if (lower[i] < upper[i] - 1) {
			return false;
		}
	}
	return true;
}

//Check to see if the currently chosen int in a vector is the lowest one that can be incremented against its upper limits
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

vector<vector<string>> transformToSingle(vector<string> list, vector<string> identifiers)
{
	//Take a sentence and use key identifiers to split it up
	//Then use a scheme such as for (int i = 0; i < list.size() - 1; i++) to create new sentences from the list
	//Those sentences then get added to the return vector
	vector<vector<string>> returnMatrix;
	vector<string> tempVec;
	vector<int> places = {-1};
	for (int i = 0; i < list.size(); i++) {
		if (present(list[i], identifiers)) {
			places.push_back(i);
		}
	}
	places.push_back(list.size());
	//display(list);
	//display(places);
	if (places.size() > 2) {
		//display(list);
		/*
		for (int i = 1; i < places.size() - 1; i++) {
			for (int g = places[i - 1] + 1; g < places[i + 1]; g++) {
				//cout << list[g] << " ";
			}
			//cout << endl;
		}*/
	}
	else {
		return returnMatrix;
	}

	return returnMatrix;
}

//Break down the sentence into multiple pieces based on U and T parameters, returning the split versions at the end
vector<vector<string>> partition(vector<string> sentence, vector<string> con, vector<string> split) {
	vector<int> tracker, counter; //Tracker is set to the size of the partitions in the matrix, counter keeps track and is always less than tracker
	vector<string> tempVec;
	vector<vector<string>> tempMat, tempMat_2, returnMat;
	vector<vector<vector<string>>> dMat; //I really didn't wanna have to do this

	for (vector<string>::iterator word = sentence.begin(); word != sentence.end(); word++) {
		//splitWord
		if (present(*word, split)) {
			tempMat.push_back(tempVec);
			tempVec.clear();
		}
		else {
			tempVec.push_back(*word);
		}
	}
	tempMat.push_back(tempVec);
	tempVec.clear();

	for (vector<vector<string>>::iterator sentences = tempMat.begin(); sentences != tempMat.end(); sentences++) {
		for (vector<string>::iterator word = sentences->begin(); word != sentences->end(); word++) {
			if (present(*word, con)) {
				tempMat_2.push_back(tempVec);
				tempVec.clear();
			}
			else {
				tempVec.push_back(*word);
			}
		}
		tempMat_2.push_back(tempVec);
		dMat.push_back(tempMat_2);

		tempVec.clear();
		tempMat_2.clear();
	}

	//Stage 2: Using the 3D Matrix to construct every possibility
		//Set up the int vector
	resetCounter(counter, dMat.size());
	resetCounter(tracker, dMat.size());

	for (int i = 0; i < dMat.size(); i++) {
		tracker[i] = dMat[i].size();
	}
	while (!maxCount(counter, tracker)) {
		int i = 0;
		recursiveConstruct(i, tracker, counter, tempVec, dMat);
		returnMat.push_back(tempVec);
		tempVec.clear();
		increment(counter, tracker);
	} //This loop doesn't account for the last possible counter

	int i = 0;
	recursiveConstruct(i, tracker, counter, tempVec, dMat);
	returnMat.push_back(tempVec);
	tempVec.clear();

	return returnMat;
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

void increment(vector<int>& lower, vector<int>& upper) {
	for (int i = 0; i < lower.size(); i++) {
		if (lower[i] < upper[i] && lowestPossible(lower, upper, i)) {
			lower[i]++;
			for (int g = i + 1; g < lower.size(); g++) {
				lower[g] = 0;
			}
			break;
		}
	}
}

void display(vector<int> list) {
	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << " ";
	}
	cout << endl;
}