#include <string>
#include <iostream>
#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

class Instrument {
friend std::ostream& operator<<(std::ostream& out, const Instrument& i);
private:
  std::string symbol;
  float last;
  float high;
  float low;
  float change;
  float changePercent;
public:
  Instrument();
  virtual ~Instrument();
  void setSymbol(std::string symbol);
  void setLast(float last);
  void setHigh(float high);
  void setLow(float low);
  void setChange(float change);
  void setChangePercent(float changePercent);
  std::string getSymbol();
  float getLast();
  float getHigh();
  float getLow();
  float getChange();
  float getChangePercent();
  bool isPositive() const;
  bool operator<(const Instrument& i) const;
};

#endif /* INSTRUMENT_H_ */
