//
// Created by young on 18-3-25.
//

#ifndef CEDIS_CEDISCLIENT_H
#define CEDIS_CEDISCLIENT_H

#include <thread>
#include "Connector.h"
#include <string>
#include <utility>

namespace cedis {
    class CedisClient {
    public:
        typedef std::vector<std::string> StrVec;
        typedef std::vector<std::pair<std::string, std::string> > StrPairVec;

        CedisClient();
        ~CedisClient();

        //string
        bool set(const std::string& key, const std::string& value);
        bool get(const std::string& key, std::string& res);
        int append(const std::string& key, const std::string& append_str);
        int bitcount(const std::string& key, const int& begin_idx, const int& end_idx);
        bool getRange(const std::string& key, const int& begin_idx, const int& end_idx, std::string& res);
        bool getSet(const std::string& key, const std::string& val, std::string& res);
        int64_t incr(const std::string& key);
        int64_t incrby(const std::string& key, const int64_t& increment);
        bool incrByFloat(const std::string& key, const float& increment, float& res);
        void mget(const std::vector<std::string>& keys, std::vector<std::string>& res);
        void mset(const std::vector<std::pair<std::string, std::string> >& kv_pair);
        bool msetNX(const std::vector<std::pair<std::string, std::string> >& kv_pair);
        bool psetEX(const std::string& key, const int64_t& mseconds, const std::string& value);
        int setbit(const std::string& key, const int64_t& offset, const short& val);
        int getbit(const std::string& key, const int64_t& offset);
        bool setEX(const std::string& key, const int64_t& seconds, const std::string& value);
        bool setNX(const std::string& key, const std::string& value);
        int64_t setRange(const std::string& key, const int64_t& offset, const std::string& value);
        int64_t strlen(const std::string& key);

        //Hash table
        short hset(const std::string& key, const std::string& field, const std::string& value);
        bool hget(const std::string& key, const std::string& field, std::string& res);
        int hdel(const std::string& key, const std::vector<std::string>& fields);
        bool hexists(const std::string& key, const std::string& filed);
        void hgetAll(const std::string& key, std::map<std::string, std::string>& res);
        int64_t hincrby(const std::string& key, const std::string& field, const int64_t& increment);
        bool hincrByFloat(const std::string& key, const std::string& field, const float& increment, float& res);
        void hkeys(const std::string& key, StrVec& res);
        int64_t hlen(const std::string& key);
        bool hmset(const std::string& key, const StrPairVec& kv);
        void hmget(const std::string& key, const StrVec& fields, StrVec& res);
        bool hsetNX(const std::string& key, const std::string& field, const std::string& value);
        void hvals(const std::string& key, StrVec& res);
        //void scan(const std::string& key);

        //list
        bool lrangeAll(const std::string& key, std::vector<std::string>& res);
        bool lrange(const std::string& key, const int& begin_idx, const int& end_idx, std::vector<std::string>& res);
        bool lset(const std::string& key, const int& idx, const std::string& value);

        //key
        int del(const std::vector<std::string>& key);
        int exists(const std::string& key);



    private:
        std::shared_ptr<Connector> m_connector;
        std::shared_ptr<io_service> m_ios;
        std::shared_ptr<std::thread> m_runThread;
    };
}


#endif //CEDIS_CEDISCLIENT_H
