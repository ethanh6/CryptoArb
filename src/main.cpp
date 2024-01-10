#include "parameters.h"

#include <gtest/gtest.h>

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  std::cout << " >>> CryptoArb Cryptocurrencies Arbitrage Bot <<<\n";
  std::cout << " >>> DISCLAIMER: USE THIS SOFTWARE AT YOUR OWN RISK <<<\n";

  // read config file
  json config = json::parse(std::ifstream("config.json"));
  std::cout << config["project_name"] << std::endl;

  std::cout << " >>> CryptoArb has been correctly terminated. <<<" << std::endl;

  return 0;
}
