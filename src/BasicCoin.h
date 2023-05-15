#pragma once
#include "quote_t.h"
#include <string>

class BasicCoin {

private:
  unsigned id;
  std::string exchName;
  std::string coinName;
  double fees;
  bool hasShort;
  bool isImplemented;
  double bid;
  double ask;

public:
  BasicCoin(unsigned _id, std::string _exchName, std::string _coinName,
                    double _fees, bool _hasShort, bool _isImplemented) {}

  void updateData(quote_t quote) {
    bid = quote.bid();
    ask = quote.ask();
  }

  unsigned getId() const { return id; }

  std::string getExchName() const { return exchName; }

  std::string getCoinName() const { return coinName; }

  double getFees() const { return fees; }

  bool getHasShort() const { return hasShort; };

  bool getIsImplemented() const { return isImplemented; }

  double getBid() const { return bid; }

  double getAsk() const { return ask; }

  double getMidPrice() const {
    return (bid > 0.0 && ask > 0.0) ? (bid + ask) / 2.0 : 0.0;
  }
};
