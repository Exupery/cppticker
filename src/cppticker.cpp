//============================================================================
// Name        : cppticker.cpp
// Author      : Matthew Frost
// Version     : 0.1
// Copyright   : "BEER-WARE LICENSE"
// Description : Stock ticker
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

std::string parseQuote(std::string rawData);

int main() {


	ifstream in("msft");

	if (!in) {
		cerr << "Error reading from file" << endl;
	} else {
		while(in) {
			std::string input;
			getline(in, input);
			std::string quote = parseQuote(input);
			if (quote.length() > 0) {
				cout << quote << endl;
			}
		}
	}


	return 0;
}

std::string parseQuote(std::string rawData) {
	//var _ticker =
	std::string tickerLine = "var _ticker =";
	size_t foundTicker = rawData.find(tickerLine);
	if (foundTicker != string::npos) {
		size_t start = rawData.find(":");
		size_t end = rawData.find("'", start);
		std::string ticker = rawData.substr(start+1, (end-start-1));
		cout << foundTicker << start << end << endl;
		return ticker;
	} else {
		return "";
	}
}
