//
// Created by young on 18-3-25.
//
#include <thread>
#include "CedisClient.h"
#include "Parser.h"

cedis::CedisClient::CedisClient() {
        m_ios = std::make_shared<io_service>();
        m_connector = std::make_shared<Connector>(m_ios, "127.0.0.1", 6379);
        m_connector->Start();
}

bool cedis::CedisClient::set(const std::string &key, const std::string &value) {
    std::string commmand = "set " + key + " \"" + value + "\"\r\n";
    m_connector->Send(commmand.data(), commmand.size());
    return Parser::parseSetRes(m_connector->ReadAndGet());
}

bool cedis::CedisClient::get(const std::string &key, std::string& res) {
    std::string command = "get " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    res = Parser::parseGetRes(m_connector->ReadAndGet());
    if(res.empty())
        return false;
    return true;
}

cedis::CedisClient::~CedisClient() {
    m_ios->stop();
}

bool cedis::CedisClient::lrangeAll(const std::string &key, std::vector<std::string>& res) {
    std::string command = "lrange " + key + " 0 -1 \r\n";
    m_connector->Send(command.data(), command.size());
    res = Parser::parseLRangeRes(m_connector->ReadAndGet());
    if(res.empty())
        return false;
    return true;
}

bool cedis::CedisClient::lrange(const std::string &key, const int &begin_idx,
                                const int &end_idx, std::vector<std::string>& res) {
    std::string command = "lrange " + key + " " + std::to_string(begin_idx) + " " +
                                                    std::to_string(end_idx) + "\r\n";
    m_connector->Send(command.data(), command.size());
    res = Parser::parseLRangeRes(m_connector->ReadAndGet());
    if(res.empty())
        return false;
    return true;
}

int cedis::CedisClient::del(const std::vector<std::string>& keys) {
    std::string command = "del";
    for(const auto& key : keys)
        command += " " + key;
    command += "\r\n";
    std::cout << "command: " << command << std::endl;
    m_connector->Send(command.data(), command.size());
    return Parser::parseDelRes(m_connector->ReadAndGet());
}

int cedis::CedisClient::exists(const std::string &key) {
    std::string command = "exists " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseDelRes(m_connector->ReadAndGet());
}

int cedis::CedisClient::append(const std::string &key, const std::string &append_str) {
    std::string command = "append " + key + " " + append_str + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseDelRes(m_connector->ReadAndGet());
}

int cedis::CedisClient::bitcount(const std::string &key, const int &begin_idx, const int &end_idx) {
    std::string command = "bitcount " + key + " " + std::to_string(begin_idx) + " " + std::to_string(end_idx) + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseBitcountRes(m_connector->ReadAndGet());
}

bool cedis::CedisClient::getRange(const std::string& key, const int& begin_idx,
                                  const int& end_idx, std::string& res) {
    std::string command = "getrange " + key + " " + std::to_string(begin_idx) + " " + std::to_string(end_idx) + "\r\n";
    m_connector->Send(command.data(), command.size());
    res = Parser::parseGetRangeRes(m_connector->ReadAndGet());
    if(res.empty())
        return false;
    return true;
}

bool cedis::CedisClient::getSet(const std::string& key, const std::string& val, std::string& res) {
    std::string commmand = "getset " + key + " \"" + val + "\"\r\n";
    m_connector->Send(commmand.data(), commmand.size());
    res = Parser::parseGetSetRes(m_connector->ReadAndGet());
}

int64_t cedis::CedisClient::incr(const std::string& key) {
    std::string command = "incr " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseIncrRes(m_connector->ReadAndGet());
}

int64_t cedis::CedisClient::incrby(const std::string &key, const int64_t &increment) {
    std::string command = "incrby " + key + " " + std::to_string(increment) + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseIncrbyRes(m_connector->ReadAndGet());
}

bool cedis::CedisClient::incrByFloat(const std::string &key, const float &increment, float& res) {
    std::string command = "incrbyfloat " + key + " " + std::to_string(increment) + "\r\n";
    m_connector->Send(command.data(), command.size());
    if(Parser::parseIncrByFloatRes(m_connector->ReadAndGet(), res))
        return true;
    else
        return false;

}

void cedis::CedisClient::mget(const std::vector<std::string>& keys, std::vector<std::string>& res) {
    std::string command = "mget";
    for(const auto& key : keys)
        command += " " + key;
    command += "\r\n";
    m_connector->Send(command.data(), command.size());
    res = Parser::parseMGetRes(m_connector->ReadAndGet());
}

void cedis::CedisClient::mset(const std::vector<std::pair<std::string, std::string> >& kv_pair) {
    std::string command = "mset ";
    for(const auto& kv : kv_pair)
        command += " " + kv.first + " \"" + kv.second + "\"";
    command += "\r\n";

    m_connector->Send(command.data(), command.size());
}

bool cedis::CedisClient::msetNX(const std::vector<std::pair<std::string, std::string> > &kv_pair) {
    std::string command = "msetnx ";
    for(const auto& kv : kv_pair)
        command += " " + kv.first + " \"" + kv.second + "\"";
    command += "\r\n";

    m_connector->Send(command.data(), command.size());
}

bool cedis::CedisClient::psetEX(const std::string &key, const int64_t &mseconds, const std::string &value) {
    std::string command = "psetEX " + key + " " + std::to_string(mseconds) + " \"" + value + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parsePSetEXRes(m_connector->ReadAndGet());
}

int cedis::CedisClient::setbit(const std::string &key, const int64_t &offset, const short &val) {
    std::string command = "setbit " + key + " " + std::to_string(offset) + " "
                                    + std::to_string(val) + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseSetbitRes(m_connector->ReadAndGet());
}

int cedis::CedisClient::getbit(const std::string &key, const int64_t &offset) {
    std::string command = "getbit " + key + " " + std::to_string(offset) + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseGetbitRes(m_connector->ReadAndGet());
}

bool cedis::CedisClient::setEX(const std::string &key, const int64_t &seconds, const std::string &value) {
    std::string command = "setex " + key + " " + std::to_string(seconds) + " \"" +
                                                                           value + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseSetEXRes(m_connector->ReadAndGet());
}

bool cedis::CedisClient::setNX(const std::string &key, const std::string &value) {
    std::string command = "setnx " + key + " \"" + value + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseSetNXRes(m_connector->ReadAndGet());
}

int64_t cedis::CedisClient::setRange(const std::string &key, const int64_t &offset, const std::string &value) {
    std::string command = "setrange " + key + " " + std::to_string(offset) + " \"" +
                                                                             value + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseSetRangeRes(m_connector->ReadAndGet());
}

int64_t cedis::CedisClient::strlen(const std::string &key) {
    std::string command = "strlen " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseStrlenRes(m_connector->ReadAndGet());
}

//解析失败返回０，如果 field 是哈希表中的一个新建域，并且值设置成功，返回 1 。
//如果哈希表中域 field 已经存在且旧值已被新值覆盖，返回 0 。
short cedis::CedisClient::hset(const std::string &key, const std::string &field, const std::string &value) {
    std::string command = "hset " + key + " " + field + " \"" + value + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHSetRes(m_connector->ReadAndGet());
}

bool cedis::CedisClient::hget(const std::string &key, const std::string &field, std::string &res) {
    std::string command = "hget " + key + " " + field + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHGetRes(m_connector->ReadAndGet(), res);
}

int cedis::CedisClient::hdel(const std::string &key, const std::vector<std::string> &fields) {
    std::string command = "hdel " + key;
    for(const auto& field : fields) {
        command += " " + field;
    }
    command += "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHDelRes(m_connector->ReadAndGet());
}

//如果哈希表含有给定域，返回 1 。
//如果哈希表不含有给定域，或 key 不存在，返回 0 。
bool cedis::CedisClient::hexists(const std::string &key, const std::string &filed) {
    std::string command = "hexists " + key + " " + filed + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHExistsRes(m_connector->ReadAndGet());
}

//返回一个map,对应哈希表
void cedis::CedisClient::hgetAll(const std::string &key, std::map<std::string, std::string>& res) {
    std::string command = "hgetall " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    Parser::parseHGetAllRes(m_connector->ReadAndGet(), res);
}

//返回执行 HINCRBY 命令之后，哈希表 key 中域 field 的值。
int64_t cedis::CedisClient::hincrby(const std::string &key, const std::string &field, const int64_t& increment) {
    std::string command = "hincrby " + key + " " + field + " " + std::to_string(increment) + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHIncrByRes(m_connector->ReadAndGet());
}

//res为执行加法操作之后 field 域的值,成功返回true,失败返回false
bool cedis::CedisClient::hincrByFloat(const std::string &key, const std::string& field, const float &increment, float &res) {
    std::string command = "hincrbyfloat " + key + " " + field + " " + std::to_string(increment) + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHIncrByFloatRes(m_connector->ReadAndGet(), res);
}

//返回哈希表所有的field
void cedis::CedisClient::hkeys(const std::string &key, cedis::CedisClient::StrVec &res) {
    std::string command = "hkeys " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    Parser::parseHKeysRes(m_connector->ReadAndGet(), res);
}

//返回哈希表 key 中域的数量。
int64_t cedis::CedisClient::hlen(const std::string &key) {
    std::string command = "hlen " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHLenRes(m_connector->ReadAndGet());
}

//如果命令执行成功，返回 OK 。
//当 key 不是哈希表(hash)类型时，返回一个错误。
bool cedis::CedisClient::hmset(const std::string &key, const cedis::CedisClient::StrPairVec &kv) {
    std::string command = "hmset " + key;
    for(const auto& kv_item : kv)
        command += " " + kv_item.first + " \"" + kv_item.second + "\"";
    command += "\r\n";
    std::cout << command << std::endl;
    m_connector->Send(command.data(), command.size());
    return Parser::parseHMSetRes(m_connector->ReadAndGet());

}

//res为返回值，一个包含多个给定域的关联值的vector，vector中的string的排列顺序和给定域参数的请求顺序一样。
void cedis::CedisClient::hmget(const std::string &key, const cedis::CedisClient::StrVec &fields,
                               cedis::CedisClient::StrVec &res) {
    std::string command = "hmget " + key;
    for(const auto& field : fields)
        command += " " + field;
    command += "\r\n";
    m_connector->Send(command.data(), command.size());
    Parser::parseHMGetRes(m_connector->ReadAndGet(), res);
}

//设置成功，返回 1 。
//如果给定域已经存在且没有操作被执行，返回 0 。
bool cedis::CedisClient::hsetNX(const std::string &key, const std::string &field, const std::string &value) {
    std::string command = "hsetnx " + key + " " + field + " \"" + value + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseHSetNXRes(m_connector->ReadAndGet());
}

//返回哈希表 key 中所有域的值。
void cedis::CedisClient::hvals(const std::string &key, cedis::CedisClient::StrVec &res) {
    std::string command = "hvals " + key + "\r\n";
    m_connector->Send(command.data(), command.size());
    Parser::parseHValsRes(m_connector->ReadAndGet(), res);
}

bool cedis::CedisClient::lset(const std::string &key, const int &idx, const std::string &value) {
    std::string command = "lset " + std::to_string(idx) + " \"" + value
                          + "\"\r\n";
    m_connector->Send(command.data(), command.size());
    return Parser::parseLSet(m_connector->ReadAndGet());
}









