#include "Instrument.h"
#include <string>
#include <iostream>
#include <iomanip>

Instrument::Instrument() {
  symbol = "";
  last = 0;
  high = 0;
  low = 0;
  change = 0;
  changePercent = 0;
}

void Instrument::setSymbol(std::string symbol) {
  for (unsigned int i=0; i<symbol.length(); i++) {
    if (symbol[i] >= 'a' && symbol[i] <= 'z') {
      symbol[i] += ('A' - 'a');
    }
  }
  size_t hasDot = symbol.find(".");
  if (hasDot != std::string::npos) {
    this->symbol = symbol.substr(hasDot+1);
  } else {
    this->symbol = symbol;
  }
}

void Instrument::setLast(float last) {
  this->last = last;
}

void Instrument::setHigh(float high) {
  this->high = high;
}

void Instrument::setLow(float low) {
  this->low = low;
}

void Instrument::setChange(float change) {
  this->change = change;
}

void Instrument::setChangePercent(float changePercent) {
  this->changePercent = changePercent * 100;
}

std::string Instrument::getSymbol() {
  return symbol;
}

float Instrument::getLast() {
  return last;
}

float Instrument::getHigh() {
  return high;
}

float Instrument::getLow() {
  return low;
}

float Instrument::getChange() {
  return change;
}

float Instrument::getChangePercent() {
  return changePercent;
}

bool Instrument::operator<(const Instrument& i) const {
  return (this->symbol.compare(i.symbol) < 0);
}

bool Instrument::isPositive() const {
  return change > 0;
}

Instrument::~Instrument() {

}

std::ostream& operator<<(std::ostream& out, const Instrument& i) {
  out << std::fixed;
  out << std::setprecision(2);
  out << std::setw(6) << std::left << i.symbol << std::right << std::setw(10) << i.last;
  std::string color = (i.isPositive()) ? "\033[1;32m" : "\033[1;31m";
  out << color << std::setw(10) << i.change << std::setw(8) << i.changePercent << "%";
  out << "\033[0m" <<  std::setw(12) << i.low << " - " <<  std::setw(10) << std::left << i.high;
  return out;
}

