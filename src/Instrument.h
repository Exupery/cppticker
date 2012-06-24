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
	std::string change;
	std::string changePercent;
public:
	Instrument();
	virtual ~Instrument();
	void setSymbol(std::string symbol);
	void setCID(std::string cid);
	void setLast(std::string last);
	void setChange(std::string change);
	void setChangePercent(std::string changePercent);
	std::string getSymbol();
	std::string getCID();
	std::string getLast();
	std::string getChange();
	std::string getChangePercent();
};

#endif /* INSTRUMENT_H_ */
