#pragma once

#include <string>

struct Parameters;

int createDbConnection(Parameters& params);

int createTable(std::string exchangeName, Parameters& params);

int addBidAskToDb(std::string exchangeName, std::string datetime, double bid, double ask, Parameters& params);
