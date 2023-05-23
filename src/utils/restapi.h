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
  using unique_slist = std::unique_ptr<curl_slist, CURL_deleter>;
  RestApi(std::string host, const char *cacert = nullptr,
          std::ostream &log = std::cerr);
  RestApi(const RestApi &) = delete;
  RestApi &operator=(const RestApi &) = delete;
  json_t *getRequest(const std::string &uri, unique_slist headers = nullptr);
};
