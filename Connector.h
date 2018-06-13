//
// Created by young on 18-3-25.
//

#ifndef CEDIS_CONNECTOR_H
#define CEDIS_CONNECTOR_H

#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#include "RWHandler.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace cedis {
    class Connector {
    public:
        Connector(std::shared_ptr<io_service> ios, const std::string& strIP, short port)
                : m_ios(ios),
                  m_serverAddr(tcp::endpoint(address::from_string(strIP), port)),
                  m_isConnected(false),
                  m_chkThread(nullptr) {
            CreateEventHandler(*ios);
        }

        ~Connector() {}

        bool Start() {
            m_eventHandler->GetSocket().connect(m_serverAddr);
            m_isConnected = true;
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            return m_isConnected;
        }

        bool IsConnected() const {
            return m_isConnected;
        }

        void Send(const char *data, int len) {
            if (!m_isConnected)
                return;
            m_eventHandler->HandleWrite(data, len);
        }

        void Read() {
            if(!m_isConnected)
                return;
            m_eventHandler->HandleRead();
        }

        std::string ReadAndGet() {
            if(!m_isConnected)
                return NULL;
            return m_eventHandler->ReadAndGetString();
        }

        void AsyncSend(char *data, int len) {
            if (!m_isConnected)
                return;
            //m_eventHandler->HandleAsyncWrite(data, len);
        }

    private:
        void CreateEventHandler(io_service& ios) {
            m_eventHandler = std::make_shared<RWHandler>(ios);
            m_eventHandler->SetCallBackError([this](int connid) {
                HandleRWError(connid);
            });
            m_eventHandler->setNoDelay(false);
        }

        void CheckConnect() {
            if (m_chkThread != nullptr)
                return;
            m_chkThread = std::make_shared<std::thread>([this] {
                while (true) {
                    if (IsConnected())
                        Start();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            });
        }

        void HandleConnectError(const boost::system::error_code &ec) {
            m_isConnected = false;
            std::cout << ec.message() << std::endl;
            m_eventHandler->CloseSocket();
            CheckConnect();
        }

        void HandleRWError(int connid) {
            m_isConnected = false;
            CheckConnect();
        }

        std::shared_ptr<io_service> m_ios;
        tcp::endpoint m_serverAddr;
        std::shared_ptr <RWHandler> m_eventHandler;
        bool m_isConnected;
        std::shared_ptr<std::thread> m_chkThread;
    };
}

#endif //CEDIS_CONNECTOR_H
