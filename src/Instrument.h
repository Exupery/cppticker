/*
 * Instrument.h
 *
 *  Created on: Jun 10, 2012
 *      Author: frost
 */
#include <string>
#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

class Instrument {
private:
	std::string symbol;
	std::string cid;
	double last;
public:
	Instrument();
	virtual ~Instrument();
	void setSymbol(std::string symbol);
	void setCID(std::string cid);
	void setLast(double last);
	std::string getSymbol();
	std::string getCID();
	double getLast();
};

#endif /* INSTRUMENT_H_ */
