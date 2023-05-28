#pragma once

#include "quote_t.h"
#include <string>

struct Parameters;

class BasicExchange {
  private:
public:
  std::string exchName;
  virtual std::string getExchName() const = 0;
  virtual quote_t getQuote(Parameters &params) = 0;
};
