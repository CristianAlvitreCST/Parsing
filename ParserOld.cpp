#include "ParserOld.h"

void sentenceCompare(vector<string>& sentence, vector<string>& parser, vector<string>& nodes) { //Comparison throughout the sentence
	vector<string>::iterator sentenceI, parserI;
	for (sentenceI = sentence.begin(); sentenceI != sentence.end(); sentenceI++) {
		for (parserI = parser.begin(); parserI != parser.end(); parserI++) {
			match(sentence, parser, sentenceI, parserI, nodes);
		}
	}
}

void match(vector<string>& sentence, vector<string>& parser, vector<string>::iterator& sentenceI, vector<string>::iterator& parserI, vector<string>& nodes) {
	string empt = "";
	nodes.push_back(empt);
	vector<string>::iterator nodesI = nodes.begin();
	//cout << "evaluating if " << *sentenceI << " is comparable to " << *parserI << endl;
	if (sentenceI != sentence.end() && parserI != parser.end()) {
		if (*sentenceI == *parserI) {		//a == b
			cout << *sentenceI << " ";
			sentenceI++;
			parserI++;
		}
		else if (sentenceI->empty()) {	//a == empty
			vector<string>::iterator ignore = parserI, end = parser.end();
			end--;
			if (ignore != end) {
				ignore++;
				while (sentenceI != sentence.end() && *sentenceI != *ignore) {
					nodes.push_back(empt);
					while (sentenceI != sentence.end() && !present(*sentenceI, ',') && *sentenceI != *ignore) {
						nodesI->append(*sentenceI);
						nodesI->append(" ");
						cout << *sentenceI << " ";
						sentenceI++;
					}
					nodesI++;
					cout << "Node looks like: " << *nodesI << endl;
					if (sentenceI != sentence.end()) {
						cout << endl;
						sentenceI++;
					}
				}
			}
		}
		else if (*parserI == "...") {	//a == "..."
			vector<string>::iterator ignore = parserI, end = parser.end();
			end--;
			if (ignore != end) {
				ignore++;
				while (sentenceI != sentence.end() && *sentenceI != *ignore) {
					sentenceI++;
				}
			}
		}
		else {			//a != any of the above.
			if (sentenceI != sentence.end())
				sentenceI++;
		}
	}
}

bool redundancyCheck(vector<node> list) {
	string word;
	for (int i = 0; i < list.size(); i++) {
		word = list[i].subject;
		for (int g = i + 1; g < list.size(); g++) {
			if (word == list[g].subject) {
				return true;
			}
		}
	}
	return false;
}

bool redundancyCheck(node list) {
	string word;
	for (int i = 0; i < list.edges.size(); i++) {
		word = list.edges[i];
		for (int g = i + 1; g < list.edges.size(); g++) {
			if (word == list.edges[g]) {
				return true;
			}
		}
	}
	return false;
}

bool redundancyCheck(vector<vector<string>> list) {
	for (int i = 1; i < list.size(); i++) {
		if (compareSentences(list[i], list[i - 1])) {
			return true;
		}
	}
	return false;
}

void redundancyCorrection(vector<vector<string>>& list) {
	while (redundancyCheck(list)) {
		for (int i = 0; i < list.size(); i++) {
			for (int g = i + 1; g < list.size(); g++) {
				if (compareSentences(list[i], list[g])) {
					list.erase(list.begin() + g);
					parserAssociation.erase(parserAssociation.begin() + g);
				}
			}
		}
	}
}

void redundancyCorrection(vector<node>& list) {
	while (redundancyCheck(list)) {
		for (int i = 0; i < list.size(); i++) {
			for (int g = i + 1; g < list.size(); g++) {
				if (list[i].subject == list[g].subject) {
					//Add all of list[g]'s edges to list[i]
					for (int a = 0; a < list[g].edges.size(); a++) {
						list[i].edges.push_back(list[g].edges[a]);
					}
					//Then, delete list[g]
					list.erase(list.begin() + g);
				}
			}
		}
	}
}



bool ignoreWord(string word) {
	vector<char> ignore = { '[', ']' };
	for (int i = 0; i < ignore.size(); i++) {
		if (word[0] == ignore[i]) {
			return true;
		}
	}
	return false;
}

void nodeCreation(vector<vector<string>>& sentences, vector<vector<string>>& parser, vector<string> stopWords)
{
	stackCreation(sentences, parser);
	vector<node> graph;
	node temp;
	for (int i = 0; i < sentences.size(); i++) {
		for (int g = 0; g < parser.size(); g++) {
			//If there are less than two empty instances, skip
			//The flaw here is that with something like "'x' affects 'y'", we're searching for an empty space, which always doens't exist
		//int beg = position(sentences[i], parser[g][0]);
		//if (beg == -1) { break; }
		//sentences[i].erase(sentences[i].begin(), sentences[i].begin() + beg);
		//int amnt = quantity(parser[g], "");

			//Reworked code for new parsing style
			int beg = position(sentences[i], parser[g][1]);
			if (beg == -1) { break; }
			int amnt = quantityOld(parser[g], "");

			if (amnt > 1) {
				//Find first empty position in the parser sentence, then increment for the position of the next word
				int pos = position(parser[g], "");
				if (pos == -1) { break; }
				pos++;

				//Find the parser word in the main list sentence, decrement to get the relevant subject word
				int wordPos = position(sentences[i], parser[g][pos]);
				if (wordPos == -1 || wordPos >= sentences[i].size()) { break; }
				wordPos--;

				//Temp's subject gets set equal to that relevant word
				temp.subject = sentences[i][wordPos];

				//pos = first empty position in parser
				//wordPos = matching word from the position of the beginning word
				pos = position(parser[g], "", pos);
				//if (pos < parser[g].size()) {
				if (pos + 2 < parser[g].size()) {
					wordPos++;
					pos += 2;
					while (wordPos < sentences[i].size() && pos < parser[g].size() && sentences[i][wordPos] != parser[g][pos]) {
						temp.subject.append(" ");
						temp.subject.append(sentences[i][wordPos]);
						wordPos++;
					}
				}

				amnt--;
				//Repeat the following until there should be no edges (empty parser slots) left
				for (int j = amnt; j > 0; j--) {
					int nextPos = position(parser[g], "", pos);
					nextPos--;
					int nextWordPos = position(sentences[i], parser[g][nextPos]);
					nextWordPos++;

					temp.edges.push_back(sentences[i][nextWordPos]);
					wordPos = nextPos;
					//If the word is not a stopWord, push it back
				}
				/*
				for (int j = amnt; j > 0; j--) {
					int nextPos = position(parser[g], "", pos);
					int nextWordPos = position(sentences[i], parser[g][nextPos + 1]) + 1;

					while (position(stopWords, sentences[i][nextWordPos]) != -1 && nextWordPos < sentences[i].size()) {
						nextWordPos++;
					}

					temp.edges.push_back(sentences[i][nextWordPos]);
					wordPos = nextPos;
				}*/
				break;
			}
		}
		graph.push_back(temp);
		temp.subject.clear();
		temp.edges.clear();
	}
	vector<node> betterGraph;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].subject.empty() || graph[i].edges.empty()) {
			graph.erase(graph.begin() + i);
		}
		else {
			betterGraph.push_back(graph[i]);
		}
	}
	//redundancyCorrection(betterGraph);
	//display(betterGraph);
}

bool compareSentences(vector<string> left, vector<string> right) {
	if (left.size() != right.size()) {
		return false;
	}
	for (int i = 0; i < left.size(); i++) {
		if (left[i] != right[i]) {
			return false;
		}
	}
	return true;
}

void findConnection(vector<vector<string>>& list, vector<vector<string>>& parser, vector<string>& nodes)
{
	vector<string> sentence;
	string current, next;

	vector<vector<string>>::iterator listI = list.begin(), parserI = parser.begin();
	for (listI; listI != list.end(); listI++) {
		for (parserI; parserI != parser.end(); parserI++) {
			//sentenceCompare(*listI, *parserI, nodes);
		}
	}
}

void display(vector<node> list) {
	for (int i = 0; i < list.size(); i++) {
		for (int g = 0; g < list[i].edges.size(); g++) {
			cout << list[i].subject << " -> " << list[i].edges[g] << endl;
		}
	}
}

void splitChars(stack<vector<string>>& theStack)
{
	vector<vector<string>> temp;
	vector<string> stopChars, tempC, splitWords;
	buildWordList("stopChars", stopChars);
	buildWordList("splitWords", splitWords);
	int splitHere;
	while (!theStack.empty()) {
		temp.push_back(theStack.top());
		theStack.pop();
	}
	for (int i = 0; i < temp.size(); i++) {
		for (int g = 0; g < temp[i].size(); g++) {
			if (present(temp[i][g][temp[i][g].size() - 1], stopChars)) { //Quick access to the end of a vector's strings
				splitHere = g + 1;
				//Add the after elements to the array
				for (int j = splitHere; j < temp[i].size(); j++) {
					if (present(temp[i][j], splitWords)) {
						tempC.push_back("->");
					}
					tempC.push_back(temp[i][j]);
				}
				temp[i].erase(temp[i].begin() + splitHere, temp[i].end());
				temp.insert(temp.begin() + i + 1, tempC);
				tempC.clear();
				break;
			}
		}
	}
	for (int i = 0; i < temp.size(); i++) {
		theStack.push(temp[i]);
	}
}

int quantityOld(vector<string> sentence, string find) {
	int amnt = 0;
	for (int i = 0; i < sentence.size(); i++) {
		if (find == sentence[i]) {
			amnt++;
		}
	}
	return amnt;
}

string combineString(vector<string> value)
{
	for (int i = 1; i < value.size(); i++) {
		if (i != value.size() - 1) {
			value[0].append(" ");
		}
		value[0].append(value[i]);
	}
	for (int g = value.size() - 1; g > 0; g--) {
		value.erase(value.begin() + g);
	}
	return value[0];
}

void cleanStack(stack<vector<string>>& sCopy, vector<string> removeMe) {
	stack<vector<string>> target;
	vector<string> temp;
	while (!sCopy.empty()) {
		temp = sCopy.top();
		sCopy.pop();

		while (overlap(temp, removeMe)) {
			for (int i = 0; i < temp.size(); i++) {
				if (present(temp[i], removeMe)) {
					temp.erase(temp.begin() + i);
				}
			}
		}

		target.push(temp);
	}
	reverse(target);
	sCopy = target;
}