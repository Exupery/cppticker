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
	last = "";
	change = "";
	changePercent = "";
}

void Instrument::setSymbol(std::string symbol) {
	this->symbol = symbol;
}

void Instrument::setCID(std::string cid) {
	this->cid = cid;
}

void Instrument::setLast(std::string last) {
	this->last = last;
}

void Instrument::setChange(std::string change) {
	this->change = change;
}

void Instrument::setChangePercent(std::string changePercent) {
	this->changePercent = changePercent;
}

std::string Instrument::getSymbol() {
	return symbol;
}

std::string Instrument::getCID() {
	return cid;
}

std::string Instrument::getLast(){
	return last;
}

std::string Instrument::getChange(){
	return change;
}

std::string Instrument::getChangePercent(){
	return changePercent;
}

Instrument::~Instrument() {

}

