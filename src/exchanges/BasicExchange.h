#pragma once

#include <string>
#include <vector>

#include "quote_t.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"
#include "utils/hex_str.h"

struct Parameters;

#include "utils/unique_json.h"

class BasicExchange {
private:
public:
  std::string exchName;

  bool isImplemented;

  std::string getExchName() const { return exchName; }

  bool getIsImplemented() const { return isImplemented; }

  virtual double getBalance(std::string &currency) const = 0;

  virtual quote_t getQuote(Parameters &params, std::string symbol) = 0;

  virtual void getAvailBalance(Parameters &params) = 0;

  virtual json_t *authRequest(Parameters &params, std::string, std::string, std::string) = 0;

  virtual std::string getSignature(Parameters &params, std::string) = 0;
};
