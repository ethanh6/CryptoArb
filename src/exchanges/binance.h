#pragma once

#include "BasicExchange.h"
#include "quote_t.h"
#include <string>

struct Parameters;

class Binance : public BasicExchange {
public:
  Binance();
  std::string getExchName();
  bool getIsImplemented() const;
  quote_t getQuote(Parameters &params) override;
  double getAvail(Parameters &, std::string) override;
  json_t *authRequest(Parameters &, std::string, std::string,
                      std::string) override;
  std::string getSignature(Parameters &, std::string) override;
};
