#include <string>
#include <iostream>
#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

class Instrument {
friend std::ostream& operator<<(std::ostream& out, const Instrument& i);
private:
  std::string symbol;
  std::string last;
  std::string high;
  std::string low;
  std::string change;
  std::string changePercent;
public:
  Instrument();
  virtual ~Instrument();
  void setSymbol(std::string symbol);
  void setLast(std::string last);
  void setHigh(std::string high);
  void setLow(std::string low);
  void setChange(std::string change);
  void setChangePercent(std::string changePercent);
  std::string getSymbol();
  std::string getLast();
  std::string getHigh();
  std::string getLow();
  std::string getChange();
  std::string getChangePercent();
  bool isPositive() const;
  bool operator<(const Instrument& i) const;
};

#endif /* INSTRUMENT_H_ */
