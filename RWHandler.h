//
// Created by young on 18-3-25.
//

#ifndef CEDIS_RWHANDLER_H
#define CEDIS_RWHANDLER_H

#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

const int MAX_IP_PACK_SIZE = 65536;
const int HEAD_LEN = 4;
namespace cedis {
    class RWHandler {
    public:
        RWHandler(io_service& ios)
                : m_sock(ios) {
            m_sock.open(tcp::v4());
        }

        ~RWHandler() {}

        void HandleRead() {
            m_sock.read_some(buffer(m_buff));
            std::cout << m_buff.data() << std::endl;
        }

        std::string ReadAndGetString() {
            int len = m_sock.read_some(buffer(m_buff));
            return std::string(m_buff.data(), m_buff.data() + len);
        }

        void HandleWrite(const char *data, int len) {
            boost::system::error_code ec;
            m_sock.send(buffer(data, len));
            if (ec != nullptr)
                HandleError(ec);
        }

        tcp::socket &GetSocket() {
            return m_sock;
        }

        void CloseSocket() {
            boost::system::error_code ec;
            m_sock.shutdown(tcp::socket::shutdown_send, ec);
            m_sock.close(ec);
        }

        void SetConnId(int connId) {
            m_connId = connId;
        }

        int GetConnId() const {
            return m_connId;
        }

        void setNoDelay(bool on) {
            tcp::no_delay option(on);
            m_sock.set_option(option);
        }

        template<typename F>
        void SetCallBackError(F f) {
            m_callbackError = f;
        }

    private:
        void HandleError(const boost::system::error_code &ec) {
            CloseSocket();
            std::cout << ec.message() << std::endl;
            if (m_callbackError)
                m_callbackError(m_connId);
        }


        tcp::socket m_sock;
        std::array<char, MAX_IP_PACK_SIZE> m_buff;
        int m_connId;
        std::function<void(int)> m_callbackError;
    };
}

#endif //CEDIS_RWHANDLER_H
