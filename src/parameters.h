#pragma once

// #include "utils/unique_sqlite.h"

#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>

// Stores all the parameters defined
// in the configuration file.
struct Parameters {
  
  std::vector<std::string> exchName;
  std::vector<double> fees;
  std::vector<bool> canShort;
  std::vector<bool> isImplemented;
  std::vector<std::string> tickerUrl;

  CURL* curl;
  double spreadEntry;
  double spreadTarget;
  unsigned maxLength;
  double priceDeltaLim;
  double trailingLim;
  unsigned trailingCount;
  double orderBookFactor;
  bool isDemoMode;
  std::string leg1;
  std::string leg2;
  bool verbose;
  std::ofstream* logFile;
  unsigned interval;
  unsigned debugMaxIteration;
  bool useFullExposure;
  double testedExposure;
  double maxExposure;
  bool useVolatility;
  unsigned volatilityPeriod;
  std::string cacert;

  std::string okcoinApi;
  std::string okcoinSecret;
  double okcoinFees;
  bool okcoinEnable;

  std::string bitstampClientId;
  std::string bitstampApi;
  std::string bitstampSecret;
  double bitstampFees;
  bool bitstampEnable;

  std::string geminiApi;
  std::string geminiSecret;
  double geminiFees;
  bool geminiEnable;

  std::string krakenApi;
  std::string krakenSecret;
  double krakenFees;
  bool krakenEnable;

  std::string binanceApi;
  std::string binanceSecret;
  double binanceFees;
  bool binanceEnable;

  bool sendEmail;
  std::string senderAddress;
  std::string senderUsername;
  std::string senderPassword;
  std::string smtpServerAddress;
  std::string receiverAddress;

  std::string dbFile;
  // unique_sqlite dbConn;

  Parameters(std::string fileName);

  void addExchange(std::string n, double f, bool h, bool m);

  int nbExch() const;
};

// Copies the parameters from the configuration file
// to the Parameter structure.
std::string getParameter(std::string parameter, std::ifstream& configFile);

bool getBool(std::string value);

double getDouble(std::string value);

unsigned getUnsigned(std::string value);

