#include "Bitcoin.h"
#include "utils/time_fun.h"
#include "parameters.h"

#include <iostream>

struct Balance {
  double leg1;
  double leg2;
  double leg1After;
  double leg2After;
};

int main(int argc, char **argv) {
  std::cout << "CryptoArb Cryptocurrencies Arbitrage Bot" << std::endl;

  Parameters params("CryptoArb.conf");

  // Inits cURL connections
  params.curl = curl_easy_init();

  if(params.curl) {
    std::cout << "valid" << std::endl;
    CURLcode res;
    curl_easy_setopt(params.curl, CURLOPT_URL, "https://example.com");
    res = curl_easy_perform(params.curl);
    curl_easy_cleanup(params.curl);
  }

  return 0;
}
