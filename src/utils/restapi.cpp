#include "restapi.h"
#include <cassert>
#include <thread>

namespace {
// internal helpers
size_t recvCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  auto &buffer = *static_cast<std::string *>(userp);
  auto n = size * nmemb;
  return buffer.append((char *)contents, n), n;
}

} // end of anonymous namespace

RestApi::RestApi(std::string host, const char *cacert, std::ostream &log)
    : C(curl_easy_init()), host(std::move(host)), log(log) {

  assert(C);

  // CA cert setup
  if (cacert)
    curl_easy_setopt(C.get(), CURLOPT_CAINFO, cacert);
  else
    curl_easy_setopt(C.get(), CURLOPT_SSL_VERIFYPEER, false);

  curl_easy_setopt(C.get(), CURLOPT_CONNECTTIMEOUT, 10L);
  curl_easy_setopt(C.get(), CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(C.get(), CURLOPT_USERAGENT, "CryptoArb");
  curl_easy_setopt(C.get(), CURLOPT_ACCEPT_ENCODING, "gzip");

  curl_easy_setopt(C.get(), CURLOPT_WRITEFUNCTION, recvCallback);
}

void RestApi::CURL_deleter::operator()(CURL *c) {
  if (c)
    curl_easy_cleanup(c);
}

void RestApi::CURL_deleter::operator()(curl_slist *slist) {
  if (slist)
    curl_slist_free_all(slist);
}
