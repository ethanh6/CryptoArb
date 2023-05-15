#pragma once
#include <iostream>
#include <ctime>

time_t getTime_t(int y, int m, int d, int h, int n, int s);

// Returns 'yyyy-mm-dd_hh:nn:ss'
extern std::string (*const printDateTimeCsv)(const time_t &t);

// Returns 'yyyy-mm-dd hh:nn:ss'
extern std::string (*const printDateTimeDb)(const time_t &t);

// Returns 'yyymmdd_hhnnss'
std::string printDateTimeFileName();

// Returns 'mm/dd/yyyy hh:nn:ss'
std::string printDateTime(time_t t);

// Returns current 'mm/dd/yyyy hh:mm:ss'
std::string printDateTime();
