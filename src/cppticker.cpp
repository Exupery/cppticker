#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <thread>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <curl/curl.h>
#include <curl/easy.h>

#include "Instrument.h"

const std::string URL_BASE = "http://www.google.com/finance/info?infotype=infoquoteall&q=";

std::string buildURL(const std::set<std::string> &symbols);
std::string curlRead(const std::set<std::string> &symbols);
int curlWrite(char * data, size_t size, size_t len, std::string * buffer);
bool isNumber(const std::string &str);
std::string parseData(std::string input, Instrument &i);
std::string parseJSON(std::string input, std::string field);
int parseIterationInterval(const char * str);

int main(int argc, char * argv[]) {

  std::string rawData;
  std::set<std::string> symbols;
  std::set<Instrument> instruments;
  int iterationInterval = 300;
  int symbolInterval = 2;
  symbols.insert(".DJI");
  symbols.insert(".INX");
  symbols.insert("QQQ");

  if (argc > 1) {
    for (int i=1; i<argc; i++) {
      if (isNumber(argv[i])) {
        iterationInterval = parseIterationInterval(argv[i]);
      } else {
        symbols.insert(argv[i]);
      }
    }
  }

  std::set<std::string>::const_iterator iter;
  iter = symbols.begin();
  while (iter != symbols.end()) {
    Instrument i;
    std::string sym = *iter;
    i.setSymbol(sym);
    instruments.insert(i);
    iter++;
  }

  while (true) {
    rawData = curlRead(symbols);
    std::set<Instrument>::const_iterator instIter;
    instIter = instruments.begin();
    while (instIter != instruments.end()) {
      Instrument i = *instIter;
      std::string json = parseData(rawData, i);
      std::string last = parseJSON(json, "l_cur");
      std::string change = parseJSON(json, "c");
      std::string changePercent = parseJSON(json, "cp");
      std::string high = parseJSON(json, "hi");
      std::string low = parseJSON(json, "lo");
      i.setLast(last);
      i.setChange(change);
      i.setChangePercent(changePercent);
      i.setHigh(high);
      i.setLow(low);
      std::cout << i << std::endl;
      instIter++;
      std::this_thread::sleep_for(std::chrono::seconds(symbolInterval));
    }
    std::this_thread::sleep_for(std::chrono::seconds(iterationInterval));
  }

  return 0;
}

bool isNumber(const std::string& str) {
  std::string::const_iterator iter = str.begin();
  while (iter != str.end() && (std::isdigit(*iter) || *iter=='-' || *iter=='.')) {
    ++iter;
  }
  return !str.empty() && iter == str.end();
}

int parseIterationInterval(const char * str) {
  double rawEntry = atof(str);
  if (rawEntry < 1) {
    while (rawEntry < 1) {
      std::cout << "Interval cannot be less than one minute!" << std::endl;
      std:: cout << "Please enter a larger number: ";
      std::cin >> rawEntry;
    }
  }

  return rawEntry * 60;
}

int curlWrite(char * data, size_t size, size_t len, std::string * buffer) {
  int result = 0;
  if (buffer != NULL) {
    buffer->append(data, size * len);
    result = size * len;
  }
  return result;
}

std::string curlRead(const std::set<std::string> &symbols) {
  CURL * curl;
  std::string buffer;
  std::string base = buildURL(symbols);
  const char * url = base.c_str();
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

  return URL_BASE + tail;
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
