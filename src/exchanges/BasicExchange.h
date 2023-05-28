#pragma once

#include "quote_t.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"
#include "utils/hex_str.h"
#include <string>

struct Parameters;

#include "utils/unique_json.h"

class BasicExchange {
private:
public:
  std::string exchName;
  bool isImplemented;
  std::string getExchName() const { return exchName; }
  bool getIsImplemented() const { return isImplemented; }
  virtual quote_t getQuote(Parameters &) = 0;
  virtual double getAvail(Parameters &, std::string) = 0;
  virtual json_t *authRequest(Parameters &, std::string, std::string, std::string) = 0;
  virtual std::string getSignature(Parameters &, std::string) = 0;
};
