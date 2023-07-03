#pragma once

#include "BasicExchange.h"

struct Parameters;

class Binance : public BasicExchange {
private:

public:
  struct acct_balance {
    std::string asset;
    double free;
    double locked;
    acct_balance(std::string a, double f, double l)
        : asset(a), free(f), locked(l) {}
  };

  // this is not inheriented since the return type
  // from each exchange is different
  std::vector<acct_balance> balances;

  // constructor
  Binance();

  // getter method
  // return balance of the currency
  // return -1 if the currency is invalid
  double getBalance(std::string &currency) const override;

  quote_t getQuote(Parameters &params, std::string symbol) override;

  // get all available coin & its balance from the api
  void getAvailBalance(Parameters &params) override;

  json_t *authRequest(Parameters &params, std::string method,
                      std::string request, std::string options) override;

  std::string getSignature(Parameters &params, std::string payload) override;
};
