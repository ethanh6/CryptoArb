#include "binance.h"
#include "parameters.h"
#include "utils/restapi.h"
#include "utils/unique_json.h"

Binance::Binance() {
  exchName = "Binance";
}

std::string Binance::getExchName() const { return exchName; }

quote_t Binance::getQuote(Parameters &params) {
  RestApi api{"https://api.binance.us", params.cacert.c_str(), *params.logFile};
  std::string x{"/api/v3/ticker/bookTicker?symbol=BTCUSDT"};

  unique_json root{api.getRequest(x)};

  double quote =
      atof(json_string_value(json_object_get(root.get(), "bidPrice")));

  auto bidValue = quote ? quote : 0.0;

  quote = atof(json_string_value(json_object_get(root.get(), "askPrice")));

  auto askValue = quote ? quote : 0.0;

  return std::make_pair(bidValue, askValue);
}
