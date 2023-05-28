#pragma once

#include "BasicExchange.h"
#include "quote_t.h"
#include <string>

struct Parameters;

class Binance : public BasicExchange {
public:
  Binance();
  std::string getExchName() ;
  bool getIsImplemented() const ;
  quote_t getQuote(Parameters &params) override;
};
