//
// Created by young on 18-3-27.
//

#include "Parser.h"
#include <ctype.h>
#include <sstream>
#include <iostream>

std::string cedis::Parser::parseGetRes(const std::string& response) {
    std::string num_str;
    int i = 0;
    std::string res;
    if(response[i] == '$') {
        i++;
        //被请求的值不存在
        if(response[i] == '-')
            return res;

        while(response[i] != '\r') {
            num_str += response[i];
            i++;
        }
        std::stringstream str_stream;
        str_stream << num_str;
        int str_len;
        str_stream >> str_len;
        i += 2;
        return response.substr(i, str_len);
    }
    return res;
}

bool cedis::Parser::parseSetRes(const std::string& response) {
    if(response[0] == '+') {
        return true;
    }
    else if(response[0] == '-') {
        return false;
    }
}

std::vector<std::string> cedis::Parser::parseLRangeRes(const std::string& response) {
    std::vector<std::string> res;
    //value的数量
    std::string value_num_str;
    int i = 0;
    if(response[i] == '*') {
        i++;

        while(response[i] != '\r') {
            value_num_str += response[i];
            i++;
        }

        std::stringstream str_stream;
        str_stream << value_num_str;
        int value_num;
        str_stream >> value_num;

        //消息数为０
        if(value_num == 0)
            return res;
        i += 2;

        //parse value
        while(value_num--) {
            std::string value_len_str = "";
            if(response[i] == '$') {
                i++;

                while(response[i] != '\r') {
                    value_len_str += response[i];
                    i++;
                }
                str_stream.clear();
                str_stream << value_len_str;
                int value_len;
                str_stream >> value_len;
                i += 2;
                if(value_len == -1) {
                    res.push_back("");
                    continue;
                }
                //key exists
                res.push_back(response.substr(i, value_len));
                i += value_len;
                i += 2;
            }
        }
    }
    return res;
}

int cedis::Parser::parseDelRes(const std::string& response) {
    if(response[0] == ':') {
        int i = 1;
        std::stringstream str2int_stream;
        std::string res_str;

        while(response[i] != '\r')
            res_str += response[i++];

        str2int_stream << res_str;
        int res = 0;
        str2int_stream >> res;
        return res;
    }
    return -1;
}

int cedis::Parser::parseAppendRes(const std::string& response) {
    return parseDelRes(response);
}

int cedis::Parser::parseBitcountRes(const std::string& response) {
    return parseDelRes(response);
}

std::string cedis::Parser::parseGetRangeRes(const std::string& response) {
    return parseGetRes(response);
}

std::string cedis::Parser::parseGetSetRes(const std::string& response) {
    return parseGetRes(response);
}

int64_t cedis::Parser::parseIncrRes(const std::string& response) {
    if(response[0] == ':') {
        int i = 1;
        std::stringstream str2int_stream;
        std::string res_str;

        while(response[i] != '\r')
            res_str += response[i++];

        str2int_stream << res_str;
        int res = 0;
        str2int_stream >> res;
        return res;
    }
    else if(response[0] == '-') {
        return -1;
    }
}

int64_t cedis::Parser::parseIncrbyRes(const std::string& response) {
    return parseIncrRes(response);
}

bool cedis::Parser::parseIncrByFloatRes(const std::string &response, float& res) {
    return parseFloat(response, res);
}

std::vector<std::string> cedis::Parser::parseMGetRes(const std::string &response) {
    return parseLRangeRes(response);
}

bool cedis::Parser::parseMGetNXRes(const std::string &response) {
    if(response[0] == ':') {
        if(response[1] == '0')
            return false;
        else
            return true;
    }
}

bool cedis::Parser::parsePSetEXRes(const std::string &response) {
    if(response[0] == '+')
        return true;
    else
        return false;
}

int cedis::Parser::parseSetbitRes(const std::string &response) {
    if(response[0] == ':')
        return response[1] == '0' ? 0 : 1;
    return -1;
}

int cedis::Parser::parseGetbitRes(const std::string &response) {
    return parseSetbitRes(response);
}

bool cedis::Parser::parseSetEXRes(const std::string &response) {
    if(response[0] == '+')
        return true;
    else
        return false;
}

bool cedis::Parser::parseSetNXRes(const std::string &response) {
    if(response[0] == ':') {
        if(response[1] == '1')
            return true;
        else
            return false;
    }
    return false;
}

int64_t cedis::Parser::parseSetRangeRes(const std::string &response) {
    return parseIncrRes(response);
}

int64_t cedis::Parser::parseStrlenRes(const std::string &response) {
    return parseDelRes(response);
}

short cedis::Parser::parseHSetRes(const std::string &response) {
    if(response[0] == ':') {
        if(response[1] == '1')
            return 1;
        else
            return 0;
    }
    return -1;
}

bool cedis::Parser::parseHGetRes(const std::string &response, std::string& res) {
    std::string num_str;
    int i = 0;

    if(response[i] == '$') {
        i++;
        //被请求的值不存在
        if(response[i] == '-')
            return false;

        while(response[i] != '\r') {
            num_str += response[i];
            i++;
        }
        std::stringstream str_stream;
        str_stream << num_str;
        int str_len;
        str_stream >> str_len;
        i += 2;
        res = response.substr(i, str_len);\
        return true;
    }
    else
        return false;
}

int cedis::Parser::parseHDelRes(const std::string &response) {
    return parseDelRes(response);
}

bool cedis::Parser::parseHExistsRes(const std::string &response) {
    if(response[0] == ':') {
        if(response[1] == '1')
            return true;
        else
            return false;
    }
    return false;
}

void cedis::Parser::parseHGetAllRes(const std::string &response, std::map<std::string, std::string> &res) {
    //value的数量
    std::string value_num_str;
    int i = 0;
    if(response[i] == '*') {
        i++;

        while(response[i] != '\r') {
            value_num_str += response[i];
            i++;
        }

        std::stringstream str_stream;
        str_stream << value_num_str;
        int value_num;
        str_stream >> value_num;

        //消息数为０
        if(value_num == 0)
            return;
        i += 2;
        value_num = value_num / 2;
        //parse value
        while(value_num--) {
            std::string value_len_str = "", key = "", val = "";
            if(response[i] == '$') {
                i++;

                while(response[i] != '\r') {
                    value_len_str += response[i];
                    i++;
                }
                str_stream.clear();
                str_stream << value_len_str;
                int value_len;
                str_stream >> value_len;
                i += 2;
                //key exists
                key = (response.substr(i, value_len));
                i += value_len;
                i += 2;
            }
            value_len_str = "";
            if(response[i] == '$') {
                i++;

                while(response[i] != '\r') {
                    value_len_str += response[i];
                    i++;
                }
                str_stream.clear();
                str_stream << value_len_str;
                int value_len;
                str_stream >> value_len;
                i += 2;
                //key exists
                val = (response.substr(i, value_len));
                i += value_len;
                i += 2;
            }
            res[key] = val;
        }
    }
}

int64_t cedis::Parser::parseHIncrByRes(const std::string& response) {
    return parseInteger(response);
}

int64_t cedis::Parser::parseInteger(const std::string &response) {
    if(response[0] == ':') {
        int i = 1;
        std::stringstream str2int_stream;
        std::string res_str;

        while(response[i] != '\r')
            res_str += response[i++];

        str2int_stream << res_str;
        int res = 0;
        str2int_stream >> res;
        return res;
    }
    else {
        return -1;
    }
}

bool cedis::Parser::parseFloat(const std::string &response, float &res) {
    std::string num_str;
    int i = 0;
    std::string res_str;
    if(response[i] == '$') {
        i++;
        //被请求的值不存在
        if(response[i] == '-')
            return false;

        while(response[i] != '\r') {
            num_str += response[i];
            i++;
        }
        std::stringstream str_stream;
        str_stream << num_str;
        int str_len;
        str_stream >> str_len;
        i += 2;
        res_str = response.substr(i, str_len);
        str_stream.clear();
        str_stream  << res_str;
        str_stream >> res;
        return true;
    }
    return false;
}

bool cedis::Parser::parseHIncrByFloatRes(const std::string &response, float &res) {
    return parseFloat(response, res);
}

void cedis::Parser::parseHKeysRes(const std::string &response, cedis::Parser::StrVec &res) {
    parseMultiString(response, res);
}

void cedis::Parser::parseMultiString(const std::string &response, cedis::Parser::StrVec &res) {
    //value的数量
    std::string value_num_str;
    int i = 0;
    if(response[i] == '*') {
        i++;

        while(response[i] != '\r') {
            value_num_str += response[i];
            i++;
        }

        std::stringstream str_stream;
        str_stream << value_num_str;
        int value_num;
        str_stream >> value_num;

        //消息数为０
        if(value_num == 0)
            return;
        i += 2;

        //parse value
        while(value_num--) {
            std::string value_len_str = "";
            if(response[i] == '$') {
                i++;

                while(response[i] != '\r') {
                    value_len_str += response[i];
                    i++;
                }
                str_stream.clear();
                str_stream << value_len_str;
                int value_len;
                str_stream >> value_len;
                i += 2;
                if(value_len == -1) {
                    res.push_back("");
                    continue;
                }
                //key exists
                res.push_back(response.substr(i, value_len));
                i += value_len;
                i += 2;
            }
        }
    }
}

int64_t cedis::Parser::parseHLenRes(const std::string &response) {
    return parseInteger(response);
}

bool cedis::Parser::parseHMSetRes(const std::string &response) {
    if(response[0] == '+')
        return true;
    else
        return false;
}

void cedis::Parser::parseHMGetRes(const std::string &response, StrVec& res) {
    return parseMultiString(response, res);
}

bool cedis::Parser::parseHSetNXRes(const std::string &response) {
    return static_cast<bool>(parseInteger(response));
}

void cedis::Parser::parseHValsRes(const std::string &response, cedis::Parser::StrVec &res) {
    parseMultiString(response, res);
}




