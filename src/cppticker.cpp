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
#include <sstream>
#include <set>
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Instrument.h"

std::string curlRead(std::string *symbol);
void parseData(std::string input, Instrument &i);
double parseQuote(std::string rawData, std::string cid);
std::string parseCID(std::string rawData);
std::string parseSymbol(std::string rawData);

int main() {

	std::string rawData;

	std::set<std::string> symbols;
	symbols.insert("msft");

	Instrument i;
	std::string sym = "msft";
	rawData = curlRead(&sym);
	parseData(rawData, i);
	std::cout << "Symbol:\t" << i.getSymbol() << std::endl;
	std::cout << "CID:\t" << i.getCID() << std::endl;
	std::cout << "Last:\t" << "$" << i.getLast() << std::endl;

	return 0;
}

int curlWrite(char *data, size_t size, size_t len, std::string *buffer) {
	int result = 0;
	if (buffer != NULL) {
		buffer->append(data, size * len);
		result = size * len;
	}
	return result;
}

std::string curlRead(std::string *symbol) {
	CURL *curl;
	std::string buffer;
	std::string url = "http://127.0.0.1/" + *symbol;
	//std::string url = "http://www.google.com/finance?cid=358464" + *symbol;
	std::string userAgent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5";
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, &url);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_REFERER, &url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, &userAgent);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);

	}

	return buffer;
}

void parseData(std::string input, Instrument &i) {
	if (i.getSymbol().length() == 0) {
		std::string sym = parseSymbol(input);
		if (sym.length() > 0) {
			i.setSymbol(sym);
		}
	}

	if (i.getCID().length() == 0) {
		std::string cid = parseCID(input);
		if (cid.length() > 0) {
			i.setCID(cid);
		}
	}

	if (i.getLast() == 0.0) {
		double quote = parseQuote(input, i.getCID());
		if (quote > 0.0) {
			i.setLast(quote);
		}
	}
}

std::string parseCID(std::string rawData) {
	std::string cid = "";
	std::string cidMarker = "setCompanyId";
	size_t foundCID = rawData.find(cidMarker);
	if (foundCID != std::string::npos) {
		std::string cidLine = "";
		size_t lineStart = rawData.find(cidMarker);
		size_t lineEnd = rawData.find(";", lineStart);
		if (lineStart != std::string::npos && lineEnd != std::string::npos) {
			cidLine = rawData.substr(lineStart+1, (lineEnd-lineStart-1));

			size_t start = cidLine.find("(");
			size_t end = cidLine.find(")", start);
			if (start != std::string::npos && end != std::string::npos) {
				cid = cidLine.substr(start+1, (end-start-1));
			}
		}
	}

	return cid;
}

double parseQuote(std::string rawData, std::string cid) {
	double quote = 0.0;
	std::string quoteLine = std::string("ref_")+cid+std::string("_l\">");
	size_t foundQuote = rawData.find(quoteLine);
	if (foundQuote != std::string::npos) {
		size_t start = rawData.find(quoteLine);
		std::string endString = "</span>";
		size_t end = rawData.find(endString, start);
		if (start != std::string::npos && end != std::string::npos) {
			std::string quoteString = rawData.substr(start+quoteLine.length(), (end-start-quoteLine.length()));
			std::istringstream dbl(quoteString);
			dbl >> quote;
		}
	}
	return quote;
}

std::string parseSymbol(std::string rawData) {
	std::string symbol = "";
	std::string tickerMarker = "var _ticker =";
	size_t foundTicker = rawData.find(tickerMarker);
	if (foundTicker != std::string::npos) {
		std::string tickerLine = "";
		size_t lineStart = rawData.find(tickerMarker);
		size_t lineEnd = rawData.find(";", lineStart);
		if (lineStart != std::string::npos && lineEnd != std::string::npos) {
			tickerLine = rawData.substr(lineStart+1, (lineEnd-lineStart-1));

			size_t start = tickerLine.find(":");
			size_t end = tickerLine.find("'", start);
			if (start != std::string::npos && end != std::string::npos) {
				symbol = tickerLine.substr(start+1, (end-start-1));
			}
		}


	}

	return symbol;
}
