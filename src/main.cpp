#include "parameters.h"
#include "utils/db_fun.h"
#include "utils/time_fun.h"

#include "coins/Bitcoin.h"
#include "coins/Ethereum.h"

#include "exchanges/binance.h"
#include "exchanges/kraken.h"

#include <iostream>
#include <vector>

struct Balance {
  double leg1;
  double leg2;
  double leg1After;
  double leg2After;
};

int main(int argc, char **argv) {
  std::cout << " >>> KryptoArb Cryptocurrencies Arbitrage Bot <<<" << std::endl;

  Parameters params("KryptoArb.conf");

  if (params.isDemoMode)
    std::cout << " >>> DemoMode <<<" << std::endl;

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
    exit(EXIT_FAILURE);
  }

  // initialize exchange objects
  std::vector<BasicExchange *> ExchangeVec{};

  if (params.binanceEnable || params.isDemoMode) {
    ExchangeVec.push_back(new Binance());
    createTable("binance", params);
  }
  if (params.krakenEnable || params.isDemoMode) {
    ExchangeVec.push_back(new Kraken());
    createTable("kraken", params);
  }
  // TODO: add more exchagnes

  std::vector<BasicCoin *> CoinVec{
      new Bitcoin(0, true),
      new Ethereum(1, true),
  };
  // TODO: add more coin

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
  std::cout << " >>> Log file generated: " << logFileName << " <<<\n";
  std::cout << " >>> KryptoArb is running... <<<" << std::endl;
  std::ofstream logFile(logFileName, std::ofstream::trunc);
  logFile << std::setprecision(3) << std::fixed;
  params.logFile = &logFile;

  logFile << "--------------------------\n";
  logFile << "|   KryptoArb Log File   |\n";
  logFile << "--------------------------\n";
  logFile << "KryptoArb started time: " << printDateTime() << "\n\n";
  logFile << "Connected to database \'" << params.dbFile << "\'\n\n";

  if (params.isDemoMode)
    logFile << "Demo mode: trades won't be generated\n\n";

  logFile << "Pair traded: " << params.leg1 << "/" << params.leg2 << "\n\n";

  logFile << "[ Targets ]\n"
          << "\tSpread Entry : " << params.spreadEntry * 100.0 << "%\n"
          << "\tSpread Target: " << params.spreadTarget * 100.0 << "%\n\n";

  // spread entry and spread target should both be positive, otherwise it'll
  // lose money on every trade.
  if (params.spreadEntry <= 0.0)
    logFile << "\t\t WARNING: Spread Entry should be positive.\n";

  if (params.spreadTarget <= 0.0)
    logFile << "\t\t WARNING: Spread Target should be positive.\n";

  logFile << std::endl;


  // get balances of target coins in target exchanges

  logFile << "[ Current Balance ]\n";

  for (auto &exch : ExchangeVec) {

    // get balance in the exchange
    // store it in class member: balances
    exch->getAvailBalance(params);
    logFile << "\t" << exch->getExchName() << "\n";

    for (auto &coin : CoinVec) {
      std::string coinName = coin->getCoinName();
      auto bal = exch->getBalance(coinName);

      // TODO: implement demo mode
      if (params.isDemoMode and false) {
        logFile << "\t\t"
                << "N/A - demo mode\tTODO: Implement demo mode\n";
      } else if (exch->getIsImplemented()) {
        logFile << "\t\t" << coinName << ": " << bal << "\n";
      } else {
        logFile << "\t\t" << "not implemented";
      }
    }
  }
  logFile << std::endl;

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

    for (auto exchange : ExchangeVec) {
      std::string exchName = exchange->getExchName();
      auto quote = exchange->getQuote(params);
      double bid = quote.bid(), ask = quote.ask();

      // Saves bid/ask data into SQLite database
      addBidAskToDb(exchName, printDateTimeDb(currTime), bid, ask, params);

      if (params.verbose)
        logFile << "\t" << exchName << " (bid/ask): " << bid << " / " << ask
                << std::endl;

      curl_easy_reset(params.curl);
    }

    running = (++i != 1);
  }

  csvFile.close();
  curl_easy_cleanup(params.curl);

  std::cout << " >>> KryptoArb has been correctly terminated. <<<" << std::endl;

  return 0;
}
