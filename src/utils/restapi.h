#pragma once

#include "curl/curl.h"
#include "jansson.h"
#include <iostream>
#include <memory>
#include <string>

struct json_t;

class RestApi {
private:
  struct CURL_deleter {
    void operator()(CURL *);
    void operator()(curl_slist *);
  };
  typedef std::unique_ptr<CURL, CURL_deleter> unique_curl;

  unique_curl C;
  const std::string host;
  std::ostream &log;

public:
  RestApi(std::string host, const char *cacert = nullptr,
          std::ostream &log = std::cerr);
  RestApi (const RestApi &) = delete;
  RestApi& operator = (const RestApi &) = delete;
};
