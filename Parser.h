//
// Created by young on 18-3-27.
//

#ifndef CEDIS_PARSER_H
#define CEDIS_PARSER_H

#include <vector>
#include <string>
#include <map>

namespace cedis {
    class Parser {
    public:
        typedef std::vector<std::string> StrVec;

        //string
        static std::string parseGetRes(const std::string& response);
        static std::string parseGetRangeRes(const std::string& response);
        static bool parseSetRes(const std::string& response);
        static int parseAppendRes(const std::string& response);
        static int parseBitcountRes(const std::string& response);
        static std::string parseGetSetRes(const std::string& response);
        static int64_t parseIncrRes(const std::string& response);
        static int64_t parseIncrbyRes(const std::string& response);
        static bool parseIncrByFloatRes(const std::string& response, float& res);
        static std::vector<std::string> parseMGetRes(const std::string& response);
        static bool parseMGetNXRes(const std::string& response);
        static bool parsePSetEXRes(const std::string& response);
        static int parseSetbitRes(const std::string& response);
        static int parseGetbitRes(const std::string& response);
        static bool parseSetEXRes(const std::string& response);
        static bool parseSetNXRes(const std::string& response);
        static int64_t parseSetRangeRes(const std::string& response);
        static int64_t parseStrlenRes(const std::string& response);

        //hash table
        static short parseHSetRes(const std::string& response);
        static bool parseHGetRes(const std::string& response, std::string& res);
        static int parseHDelRes(const std::string& response);
        static bool parseHExistsRes(const std::string& response);
        static void parseHGetAllRes(const std::string& response, std::map<std::string, std::string>& res);
        static int64_t parseHIncrByRes(const std::string& response);
        static bool parseHIncrByFloatRes(const std::string& response, float& res);
        static void parseHKeysRes(const std::string& response, StrVec& res);
        static int64_t parseHLenRes(const std::string& response);
        static bool parseHMSetRes(const std::string& response);
        static void parseHMGetRes(const std::string& response, StrVec& res);
        static bool parseHSetNXRes(const std::string& response);
        static void parseHValsRes(const std::string& response, StrVec& res);

        //list
        static std::vector<std::string> parseLRangeRes(const std::string& response);


        //key
        static int parseDelRes(const std::string& response);

    private:
        static int64_t parseInteger(const std::string& response);
        static bool parseFloat(const std::string& response, float& res);
        static void parseMultiString(const std::string& response, StrVec& res);

    };
}


#endif //CEDIS_PARSER_H
