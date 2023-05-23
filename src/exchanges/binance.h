#pragma once

#include "quote_t.h"
#include <string>

struct Parameters;

namespace Binance {
quote_t getQuote(Parameters &params);

}
