#include "binance.h"
#include "parameters.h"
#include "utils/restapi.h"

namespace Binance {

quote_t getQuote(Parameters &params) {
  RestApi exchange{"https://api.binance.com", params.cacert.c_str(),
                   *params.logFile};
  std::string x{"/api/v3/ticker/bookTicker?symbol=BTCUSDT"};
  return quote_t{0.0, 0.0};
}

} // namespace Binance
