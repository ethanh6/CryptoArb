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
  std::cout << " >>> KryptoArb Cryptocurrencies Arbitrage Bot <<<" << std::endl;

  Parameters params("KryptoArb.conf");

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

  // create Binance table in the db
  createTable("binance", params);

  // create CSV files collecting trade results
  std::string currDateTime = printDateTimeFileName();
  std::string csvFileName =
      "output/result/KryptoArb_result_" + currDateTime + ".csv";
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
  std::string logFileName = "output/log/KryptoArb_log_" + currDateTime + ".log";
  std::ofstream logFile(logFileName, std::ofstream::trunc);
  logFile << std::setprecision(3) << std::fixed;
  params.logFile = &logFile;

  logFile << "--------------------------\n";
  logFile << "|   KryptoArb Log File   |\n";
  logFile << "--------------------------\n";
  logFile << "KryptoArb started time: " << printDateTime() << "\n\n";
  logFile << "Connected to database \'" << params.dbFile << "\'\n\n";

  if (params.isDemoMode) {
    logFile << "Demo mode: trades won't be generated\n\n";
  }

  logFile << "Pair traded: " << params.leg1 << "/" << params.leg2 << "\n\n";

  logFile << "[ Targets ]\n"
          << "\tSpread Entry:  " << params.spreadEntry * 100.0 << "%\n"
          << "\tSpread Target: " << params.spreadTarget * 100.0 << "%\n\n";

  logFile << "[ Current Balance ]\n";
  logFile << "[ Exposure ]\n";
  logFile << std::endl;

  // initialize curl connections
  params.curl = curl_easy_init();

  // time info
  time_t rawtime = time(nullptr); // returns the current calendar time encoded
  tm timeinfo = *localtime(&rawtime); // struct tm holding a calendar data

  // main analysis loop
  bool running = true;
  time_t currTime;
  int i = 0;
  while (running) {
    currTime = std::mktime(&timeinfo);

    auto quote = Binance::getQuote(params);
    double bid = quote.bid();
    double ask = quote.ask();

    // Saves bid/ask data into SQLite database
    addBidAskToDb("Binance", printDateTimeDb(currTime), bid, ask, params);

    if (params.verbose) {
      logFile << "\tBinance (bid/ask):\t" << bid << "/" << ask << std::endl;
    }

    curl_easy_reset(params.curl);

    if (++i == 5)
      running = false;
  }

  csvFile.close();
  curl_easy_cleanup(params.curl);

  std::cout << " >>> End of program <<<" << std::endl;

  return 0;
}
