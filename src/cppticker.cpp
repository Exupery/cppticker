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

#include "json.hpp"

#include "Instrument.h"

const std::string URL_BASE = "http://www.google.com/finance/info?infotype=infoquoteall&q=";

std::string buildURL(const std::set<std::string> &symbols);
std::string curlRead(const std::set<std::string> &symbols);
int curlWrite(char * data, size_t size, size_t len, std::string * buffer);
bool isNumber(const std::string &str);
std::set<Instrument> parseData(std::string input);
std::string parseJSON(std::string input, std::string field);
int parseIterationInterval(const char * str);

int main(int argc, char * argv[]) {

  std::string rawData;
  std::set<std::string> symbols;
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

  while (true) {
    rawData = curlRead(symbols);
    for (Instrument i : parseData(rawData)) {
      std::cout << i << std::endl;
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

  std::string::size_type jsonStart = buffer.find("[");
  if (jsonStart != 0) {
    buffer.erase(0, jsonStart);
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

std::set<Instrument> parseData(std::string input) {
  std::set<Instrument> instruments;
  for (nlohmann::json json : nlohmann::json::parse(input)) {
    Instrument i;

    i.setSymbol(json["t"]);
    i.setLast(json["l_cur"]);
    i.setChange(json["c"]);
    i.setChangePercent(json["cp"]);
    i.setHigh(json["hi"]);
    i.setLow(json["lo"]);

    instruments.insert(i);
  }

  return instruments;
}
