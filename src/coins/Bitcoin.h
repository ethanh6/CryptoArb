#pragma once
#include "BasicCoin.h"

class Bitcoin : public BasicCoin {

public:
  Bitcoin(unsigned _id, bool _isImplemented)
      : BasicCoin(_id, "BTC", _isImplemented) {
  }
};
