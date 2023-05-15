#pragma once
#include "BasicCoin.h"

class Bitcoin : public BasicCoin {

public:
  Bitcoin(unsigned _id, std::string _exchName, std::string _coinName,
          double _fees, bool _hasShort, bool _isImplemented)
      : BasicCoin(_id, _exchName, _coinName, _fees, _hasShort, _isImplemented) {
  }
};
