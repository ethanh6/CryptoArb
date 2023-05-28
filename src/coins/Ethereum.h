#pragma once
#include "BasicCoin.h"

class Ethereum : public BasicCoin {

public:
  Ethereum(unsigned _id, bool _isImplemented)
      : BasicCoin(_id, "ETH", _isImplemented) {
  }
};
