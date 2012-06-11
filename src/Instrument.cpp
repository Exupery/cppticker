/*
 * Instrument.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: frost
 */

#include "Instrument.h"
#include <string>

Instrument::Instrument() {
	symbol = "";
	cid = "";
	last = 0.0;
}

void Instrument::setSymbol(std::string symbol) {
	this->symbol = symbol;
}

void Instrument::setCID(std::string cid) {
	this->cid = cid;
}

void Instrument::setLast(double last) {
	this->last = last;
}

std::string Instrument::getSymbol() {
	return symbol;
}

std::string Instrument::getCID() {
	return cid;
}

double Instrument::getLast(){
	return last;
}

Instrument::~Instrument() {

}

