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
	std::string last;
public:
	Instrument();
	virtual ~Instrument();
	void setSymbol(std::string symbol);
	void setCID(std::string cid);
	void setLast(std::string last);
	std::string getSymbol();
	std::string getCID();
	std::string getLast();
};

#endif /* INSTRUMENT_H_ */
