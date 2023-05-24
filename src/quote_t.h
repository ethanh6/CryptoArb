#pragma once
#include <utility>

class quote_t {
private:
  typedef double bid_t;
  typedef double ask_t;
  std::pair<bid_t, ask_t> quote_pair;

public:
  quote_t(bid_t bid, ask_t ask) : quote_pair(std::make_pair(bid, ask)) {}
  quote_t(std::pair<bid_t, ask_t> &&quote) : quote_pair(std::move(quote)) {}
  bid_t bid() const { return quote_pair.first; }
  ask_t ask() const { return quote_pair.second; }
};
