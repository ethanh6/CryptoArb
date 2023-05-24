#include "Bitcoin.h"
#include "parameters.h"
#include "utils/db_fun.h"
#include "utils/time_fun.h"

#include "exchanges/binance.h"

#include <iostream>
#include <vector>

struct Balance {
  double leg1;
  double leg2;
  double leg1After;
  double leg2After;
};

// typedef quote_t (*getQuoteType)(Parameters &params);

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
  std::string csvFileName =
      "output/result/CryptoArb_result_" + currDateTime + ".csv";
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

  logFile << "Pair traded: " << params.leg1 << "/" << params.leg2 << "\n"
          << std::endl;

  logFile << "[ Targets ]\n"
          << "\tSpread Entry:  " << params.spreadEntry * 100.0 << "%\n"
          << "\tSpread Target: " << params.spreadTarget * 100.0 << "%\n"
          << std::endl;

  logFile << "[ Current Balance ]\n";
  logFile << "[ Exposure ]\n";
  logFile << std::endl;

  // initialize curl connections
  params.curl = curl_easy_init();

  bool running = true;
  while (running) {
    std::cout << "while looping" << std::endl;
    auto quote = Binance::getQuote(params);
    double bid = quote.bid(); 
    double ask = quote.ask(); 
    std::cout << bid << " " << ask << std::endl;
    running = false;
  }

  csvFile.close();
  curl_easy_cleanup(params.curl);

  std::cout << " >>> End of program <<<" << std::endl;

  return 0;
}
