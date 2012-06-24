/*
 * Instrument.h
 *
 *  Created on: Jun 10, 2012
 *      Author: frost
 */
#include <string>
#include <iostream>
#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

class Instrument {
friend std::ostream& operator<<(std::ostream& out, const Instrument& i);
private:
	std::string symbol;
	std::string last;
	std::string change;
	std::string changePercent;
public:
	Instrument();
	virtual ~Instrument();
	void setSymbol(std::string symbol);
	void setLast(std::string last);
	void setChange(std::string change);
	void setChangePercent(std::string changePercent);
	std::string getSymbol();
	std::string getLast();
	std::string getChange();
	std::string getChangePercent();
};

#endif /* INSTRUMENT_H_ */
