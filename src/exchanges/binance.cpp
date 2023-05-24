#include "binance.h"
#include "parameters.h"
#include "utils/restapi.h"
#include "utils/unique_json.h"

namespace Binance {

quote_t getQuote(Parameters &params) {
  RestApi api{"https://api.binance.com", params.cacert.c_str(), *params.logFile};
  std::string x{"/api/v3/ticker/bookTicker?symbol=BTCUSDT"};

  unique_json root{api.getRequest(x)};

  std::cout << "asdf" << std::endl;

  double quote = atof(json_string_value(json_object_get(root.get(), "bidPrice")));

  auto bidValue = quote ? quote : 0.0;

  quote = atof(json_string_value(json_object_get(root.get(), "askPrice")));

  auto askValue = quote ? quote : 0.0;


  return std::make_pair(bidValue, askValue);
}

} // namespace Binance
