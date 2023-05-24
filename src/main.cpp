#include "Bitcoin.h"
#include "parameters.h"
#include "utils/time_fun.h"
#include "utils/db_fun.h"

#include <iostream>

struct Balance {
  double leg1;
  double leg2;
  double leg1After;
  double leg2After;
};

typedef quote_t (*getQuoteType)(Parameters &params);

int main(int argc, char **argv) {
  std::cout << " >>> CryptoArb Cryptocurrencies Arbitrage Bot <<<" << std::endl;

  Parameters params("CryptoArb.conf");

  if (params.isDemoMode) {
    std::cout << " >>> DemoMode <<<" << std::endl;
  }

  // sanity check of the parameters
  if (params.leg1 == "BTC" and params.leg2 == "USD") {
    std::cout << " >>> trading pair: [ BTC, USD ] <<<" << std::endl;
  } else {
    std::cout << "ERROR: only support BTC / USD pair" << std::endl;
    exit(EXIT_FAILURE);
  }

  // dababase connections
  int db_status = createDbConnection(params);
  if (db_status != 0) {
    std::cerr << "ERROR: db connection error" << std::endl;
  }

  // create CSV files collecting trade results
  std::string currDateTime = printDateTimeFileName();
  std::string csvFileName = "output/result/CryptoArb_result_" + currDateTime + ".csv";
  std::ofstream csvFile(csvFileName, std::ofstream::trunc);
  csvFile << "TRADE_ID,"
          << "EXCHANGE_LONG,"
          << "EXHANGE_SHORT,"
          << "ENTRY_TIME,"
          << "EXIT_TIME,"
          << "DURATION,"
          << "TOTAL_EXPOSURE,"
          << "BALANCE_BEFORE,"
          << "BALANCE_AFTER,"
          << "RETURN" << std::endl;
  
  // create log files
  std::string logFileName = "output/log/CryptoArb_log_" + currDateTime + ".log";
  std::ofstream logFile(logFileName, std::ofstream::trunc);
  logFile << std::setprecision(4) << std::fixed;
  params.logFile = &logFile;

  logFile << "--------------------------" << std::endl;
  logFile << "|   CryptoArb Log File   |" << std::endl;
  logFile << "--------------------------" << '\n' << std::endl;
  logFile << "CryptoArb started time: " << printDateTime() << '\n' << std::endl;

  logFile << "Connected to database \'" << params.dbFile << "\'\n" << std::endl;

  if (params.isDemoMode) {
    logFile << "Demo mode: trades won't be generated\n" << std::endl;
  }

  logFile << "Pair traded: " << params.leg1 << "/" << params.leg2 << "\n" << std::endl;


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
