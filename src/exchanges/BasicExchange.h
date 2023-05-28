#pragma once

#include "quote_t.h"
#include <string>

struct Parameters;

class BasicExchange {
private:
public:
  std::string exchName;
  bool isImplemented;
  std::string getExchName() const { return exchName; }
  bool getIsImplemented() const { return isImplemented; }
  virtual quote_t getQuote(Parameters &params) = 0;
};
