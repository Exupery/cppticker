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

void parseData(std::string input);
double parseQuote(std::string rawData, std::string cid);
std::string parseCID(std::string rawData);
std::string parseSymbol(std::string rawData);

int main() {

	ifstream in("msft");

	if (!in) {
		cerr << "Error reading from file" << endl;
	} else {
		while(in) {
			std::string input;
			getline(in, input);
			parseData(input);
		}
	}
	in.close();

	return 0;
}

void parseData(std::string input) {
	std::string sym = parseSymbol(input);
	if (sym.length() > 0) {
		cout << sym << endl;
	}
	std::string cid = parseCID(input);
	if (cid.length() > 0) {
		cout << cid << endl;
	}
	double quote = parseQuote(input, "358464");
	if (quote > 0.0) {
		cout << "$" << quote << endl;
	}
}

std::string parseCID(std::string rawData) {
	std::string cid = "";
	std::string cidLine = "setCompanyId";
	size_t foundCID = rawData.find(cidLine);
	if (foundCID != string::npos) {
		size_t start = rawData.find("(");
		size_t end = rawData.find(")", start);
		if (start != string::npos && end != string::npos) {
			cid = rawData.substr(start+1, (end-start-1));
		}
	}

	return cid;
}

double parseQuote(std::string rawData, std::string cid) {
	double quote = 0.0;
	std::string quoteLine = string("ref_")+cid+string("_l");
	size_t foundQuote = rawData.find(quoteLine);
	if (foundQuote != string::npos) {
		cout << rawData << endl;
		//cout << "start: " << start << "\tend: " << end << endl;
	}
	return quote;
}

std::string parseSymbol(std::string rawData) {
	std::string symbol = "";
	std::string tickerLine = "var _ticker =";
	size_t foundTicker = rawData.find(tickerLine);
	if (foundTicker != string::npos) {
		size_t start = rawData.find(":");
		size_t end = rawData.find("'", start);
		if (start != string::npos && end != string::npos) {
			symbol = rawData.substr(start+1, (end-start-1));
		}
	}

	return symbol;
}
