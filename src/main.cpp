#include "Bitcoin.h"
#include "parameters.h"
#include "utils/time_fun.h"

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

  // create the CSV files that collect trade results
  std::string currDateTime = printDateTimeFileName();
  std::string csvFileName = "output/CryptoArb_result_" + currDateTime + ".cvs";
  std::ofstream csvFile(csvFileName, std::ofstream::trunc);

  // csvFile
  //     <<
  //     "TRADE_ID,EXCHANGE_LONG,EXHANGE_SHORT,ENTRY_TIME,EXIT_TIME,DURATION,"
  //     << "TOTAL_EXPOSURE,BALANCE_BEFORE,BALANCE_AFTER,RETURN" << std::endl;

  // Inits cURL connections
  // params.curl = curl_easy_init();
  // CURLcode res;
  // if (params.curl) {
  //   std::string BINANCE_API =
  //       "https://api.binance.com/api/v3/ticker/bookTicker?symbol=BTCUSDT";
  //   curl_easy_setopt(params.curl, CURLOPT_URL, BINANCE_API);
  //   curl_easy_setopt(params.curl, CURLOPT_WRITEDATA, (void *)&chunk);
  //   res = curl_easy_perform(params.curl);
  //
  //   if (res == CURLE_OK) {
  //     printf("Size: %lu\n", (unsigned long)chunk.size);
  //     printf("Data: %s\n", chunk.memory);
  //   }
  //
  // }

  csvFile.close();
  curl_easy_cleanup(params.curl);
  std::cout << " >>> End of program <<<" << std::endl;

  return 0;
}
