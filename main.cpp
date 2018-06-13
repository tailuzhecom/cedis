#include <iostream>
#include <boost/asio.hpp>
#include <array>
#include <thread>
#include <functional>
#include <chrono>
#include "CedisClient.h"
#include "Parser.h"

using namespace boost::asio::ip;
using namespace boost::asio;
using namespace std;
using namespace cedis;

typedef vector<string> StrVec;

int main() {

    cedis::CedisClient client;
    StrVec res;
    client.hvals("website", res);
    for(const auto& val : res)
        cout << val << endl;
    return 0;
}