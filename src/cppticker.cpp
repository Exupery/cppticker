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
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Instrument.h"

std::string curlRead(const std::set<std::string> &symbols);
std::string buildURL(const std::set<std::string> &symbols);
std::string parseData(std::string input, Instrument &i);
std::string parseJSON(std::string input, std::string field);
std::string parseQuote(std::string rawData, std::string cid);
std::string parseChange(std::string rawData, std::string cid);
std::string parseChangePercent(std::string rawData, std::string cid);
std::string parseCID(std::string rawData);
std::string parseSymbol(std::string rawData);

int main() {

	std::string rawData;

	std::set<std::string> symbols;
	symbols.insert(".DJI");
	symbols.insert(".INX");
	symbols.insert("QQQ");

	/*std::set<std::string>::const_iterator iter;
	iter = symbols.begin();
	while (iter != symbols.end()) {
		Instrument i;
		std::string sym = *iter;
		rawData = curlRead(&sym);
		parseData(rawData, i);
		std::cout << i << std::endl;
		iter++;
	}*/

	rawData = curlRead(symbols);
	std::set<std::string>::const_iterator iter;
	iter = symbols.begin();
	while (iter != symbols.end()) {
		Instrument i;
		std::string sym = *iter;
		i.setSymbol(sym);
		std::string json = parseData(rawData, i);
		std::string last = parseJSON(json, "l_cur");
		std::string change = parseJSON(json, "c");
		std::string changePercent = parseJSON(json, "cp");
		i.setLast(last);
		i.setChange(change);
		i.setChangePercent(changePercent);
		std::cout << i << std::endl;
		iter++;
	}
	std::cout << rawData << std::endl;
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

std::string curlRead(const std::set<std::string> &symbols) {
	CURL *curl;
	std::string buffer;
	std::string base = buildURL(symbols);
	const char *url = base.c_str();
	char userAgent[] = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5";
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_REFERER, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, &userAgent);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);

	}

	return buffer;
}

std::string buildURL(const std::set<std::string> &symbols) {
	std::string url;
	std::string tail;
	std::set<std::string>::const_iterator iter;
	iter = symbols.begin();
	while (iter != symbols.end()) {
		std::string sym = *iter;
		tail += sym;
		iter++;
		if (iter != symbols.end()) {
			tail += ",";
		}
	}
	url = "http://127.0.0.1/gfinance";
	//url = "http://www.google.com/finance/info?infotype=infoquoteall&q=" + tail;

	return url;
}

std::string parseData(std::string input, Instrument &i) {
	std::string json = "";
	size_t start = input.find(i.getSymbol());
	size_t end = input.find("}", start);
	if (start != std::string::npos && end != std::string::npos) {
		json = input.substr(start, end - start);
	}

	return json;
}

std::string parseJSON(std::string input, std::string field) {
	std::string fieldValue = "";
	std::string fullField = "\""+field+"\" : \"";
	size_t start = input.find(fullField);
	size_t end = input.find("\"", start+fullField.length());
	if (start != std::string::npos && end != std::string::npos) {
		fieldValue = input.substr(start+fullField.length(), (end-start-fullField.length()));
	}

	return fieldValue;
}

/*void OLDparseData(std::string input, Instrument &i) {
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

	if (i.getLast().length() == 0) {
		std::string quote = parseQuote(input, i.getCID());
		if (quote.length() > 0) {
			i.setLast(quote);
		}
	}

	if (i.getChange().length() == 0) {
		std::string change = parseChange(input, i.getCID());
		if (change.length() > 0) {
			i.setChange(change);
		}
	}

	if (i.getChangePercent().length() == 0) {
		std::string cp = parseChangePercent(input, i.getCID());
		if (cp.length() > 0) {
			i.setChangePercent(cp);
		}
	}
}*/

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

std::string parseQuote(std::string rawData, std::string cid) {
	std::string quote = "";
	std::string quoteLine = std::string("\"ref_")+cid+std::string("_l\">");
	size_t foundQuote = rawData.find(quoteLine);
	if (foundQuote != std::string::npos) {
		size_t start = rawData.find(quoteLine);
		std::string endString = "</span>";
		size_t end = rawData.find(endString, start);
		if (start != std::string::npos && end != std::string::npos) {
			quote = rawData.substr(start+quoteLine.length(), (end-start-quoteLine.length()));
		}
	}

	return quote;
}

std::string parseChange(std::string rawData, std::string cid) {
	std::string change = "";
	std::string changeLine = std::string("\"ref_")+cid+std::string("_c\">");
	size_t foundChange = rawData.find(changeLine);
	if (foundChange != std::string::npos) {
		size_t start = rawData.find(changeLine);
		std::string endString = "</span>";
		size_t end = rawData.find(endString, start);
		if (start != std::string::npos && end != std::string::npos) {
			change = rawData.substr(start+changeLine.length(), (end-start-changeLine.length()));
		}
	}

	return change;
}

std::string parseChangePercent(std::string rawData, std::string cid) {
	std::string cp = "";
	std::string cpLine = std::string("\"ref_")+cid+std::string("_cp\">(");
	size_t foundCP = rawData.find(cpLine);
	if (foundCP != std::string::npos) {
		size_t start = rawData.find(cpLine);
		std::string endString = ")</span>";
		size_t end = rawData.find(endString, start);
		if (start != std::string::npos && end != std::string::npos) {
			cp = rawData.substr(start+cpLine.length(), (end-start-cpLine.length()));
		}
	}

	return cp;
}

std::string parseSymbol(std::string rawData) {
	std::string symbol = "";
	std::string tickerMarker = "<div class=appbar-snippet-secondary><span>(";
	size_t foundTicker = rawData.find(tickerMarker);
	if (foundTicker != std::string::npos) {
		std::string tickerLine = "";
		size_t lineStart = rawData.find(tickerMarker);
		size_t lineEnd = rawData.find(")</span>", lineStart);
		if (lineStart != std::string::npos && lineEnd != std::string::npos) {
			symbol = rawData.substr(lineStart+tickerMarker.length(), (lineEnd-lineStart-tickerMarker.length()));
		}


	}

	return symbol;
}
