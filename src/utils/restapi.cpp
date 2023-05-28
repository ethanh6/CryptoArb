#include "restapi.h"
#include <cassert>
#include <thread>

// anonymous namespace for internal helpers
namespace {
size_t recvCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  auto &buffer = *static_cast<std::string *>(userp);
  auto n = size * nmemb;
  return buffer.append((char *)contents, n), n;
}

json_t *doRequest(CURL *C, const std::string &url, const curl_slist *headers,
                  std::ostream &log) {
  std::string recvBuffer;

  curl_easy_setopt(C, CURLOPT_WRITEDATA, recvBuffer.c_str());
  curl_easy_setopt(C, CURLOPT_URL, url.c_str());
  curl_easy_setopt(C, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(C, CURLOPT_DNS_CACHE_TIMEOUT, 3600);

  int attempt = 0;
  while (true) {

    // retry if more than one attempt
    if (attempt != 0) {
      log << "  API ERROR: Retry in 2 sec..." << std::endl;
      std::cout << "  API ERROR: Retry in 2 sec, see log files" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));
      recvBuffer.clear();
      curl_easy_setopt(C, CURLOPT_DNS_CACHE_TIMEOUT, 0);
    }

    // perform curl call
    CURLcode resCurl = curl_easy_perform(C);
    if (resCurl != CURLE_OK) {
      log << "Error with cURL: ";
      log << curl_easy_strerror(resCurl) << '\n';
      log << "  URL: " << url << '\n';
      attempt++;
      continue;
    }

    // Decodes the JSON string input and returns the array or object it
    // contains, or NULL on error, in which case error is filled with
    // information about the error. flags is described above.
    json_error_t error;

    json_t *root = json_loads(recvBuffer.c_str(), 0, &error);
    if (!root) {
      long resp_code;
      curl_easy_getinfo(C, CURLINFO_RESPONSE_CODE, &resp_code);
      log << "Server Response: " << resp_code << " - " << url << '\n'
          << "Error with JSON: " << error.text << '\n'
          << "Buffer:\n"
          << recvBuffer << '\n';
      attempt++;
      continue;
    }

    return root;
  }
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
  curl_easy_setopt(C.get(), CURLOPT_USERAGENT, "KryptoArb");
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
json_t *RestApi::getRequest(const std::string &uri, unique_slist headers) {
  curl_easy_setopt(C.get(), CURLOPT_HTTPGET, true);
  return doRequest(C.get(), host + uri, headers.get(), log);
}

json_t *RestApi::postRequest(const std::string &uri,
                             unique_slist headers,
                             const std::string &post_data) {
  curl_easy_setopt(C.get(), CURLOPT_POSTFIELDS, post_data.data());
  curl_easy_setopt(C.get(), CURLOPT_POSTFIELDSIZE, post_data.size());
  return doRequest(C.get(), host + uri, headers.get(), log);
}

json_t *RestApi::postRequest(const std::string &uri,
                             const std::string &post_data) {

  return postRequest(uri, nullptr, post_data);
}
