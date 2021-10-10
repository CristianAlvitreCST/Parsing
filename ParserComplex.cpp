/* Project: Parsing
*  Author: Cristian Alvitre
*  Description:
*		ParserComplex is where all "complex" functions in the project go.
*		A complex function is defined as a function that makes use of other functions
*	other than another version of itself within the parser library.
*		For example, basic parser function "foo" being used in function "bar" would make bar "complex"
*/
#pragma once
#include "ParserComplex.h"

/* Build word lists
*	Builds a word list based on the filename string passed to it
*	TODO: turn these into functions based simply on their return value
*	but I need to differentiate the first two somehow. Rename one maybe?
*/
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

/* Parsing
*	Functions that perform data parsing to eventually be put into a DAG
*	TODO: Restructure these so that any boilerplate code is removed
*	TODO: Give a better name to worldSalad
*	TODO: stackCreation should be the last part of the process
*/
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
				matches.push_back(*listIt);
			}
		}
	}
}
void stackCreation(vector<vector<string>>& sentences, vector<vector<string>>& parser) {
	vector<vector<string>> matrix, tempMat;
	stack<string> theStack;
	vector<string> ignore, stop, con, tempVec; //Ignore for words to move past, stop for words to trigger a stop
	string tempStr;
	vector<int> andPos, affectPos;
	int a, split;

	buildWordList("Documents/Parsing/ignore", ignore);
	buildWordList("Documents/Parsing/stop", stop);
	buildWordList("Documents/Parsing/conjunctional", con);

	//TODO: make partition take the whole matrix and return the complete list instead
	//In other words, put the for loop and insertion on the inside of the function.
	/* REWORK
	matrix = partition(sentences, con, stop);
	*/
	for (int i = 0; i < sentences.size(); i++) {
		tempMat = partition(sentences[i], con, stop);
		matrix.insert(matrix.end(), tempMat.begin(), tempMat.end());
	}
	for (int i = 0; i < matrix.size(); i++) {
		transformToSingle(matrix[i], stop);
	}

	tempMat = matrix;
	matrix.clear();
	sentences = tempMat;

	//Everything below this line should be kept in stackCreation. Everything above should be put elsewhere
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

/* Other
*	Temporary name, but a place where oddball functions go such as those that are just barely complex functions
*/
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