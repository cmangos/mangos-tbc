/*
* This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MANGOSSERVER_ASYNC_CONNECTOR
#define MANGOSSERVER_ASYNC_CONNECTOR

#include "Platform/Define.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "AsyncSocket.hpp"

namespace MaNGOS
{
    template <typename SocketType>
    class AsyncConnector
    {
        public:
            AsyncConnector(boost::asio::io_service& io_service, std::string const& connectIp, unsigned short connectPort, bool silent = false) : m_service(io_service), m_endpoint(boost::asio::ip::address::from_string(connectIp), connectPort), m_silent(silent)
            {
                Connect();
            }
            void HandleConnect(std::shared_ptr<SocketType> connection, const boost::system::error_code& err)
            {
                if (!err)
                    connection->Start();
            }
        private:
            boost::asio::io_service& m_service;
            boost::asio::ip::tcp::endpoint m_endpoint;
            bool m_silent;
            void Connect()
            {
                // socket
                std::shared_ptr<SocketType> connection = std::make_shared<SocketType>(m_service);
                boost::asio::ip::tcp::socket& bSock = connection->GetAsioSocket();

                try
                {
                    bSock.async_connect(m_endpoint, boost::bind(&AsyncConnector::HandleConnect, this, connection, boost::asio::placeholders::error));
                }
                catch (boost::system::system_error& error)
                {
                    if (!m_silent)
                    {
                        sLog.outError("AsyncConnector:: failed to connect to remote address.  Error: %s", error.what());
                    }
                }
            }
    };
}

#endif
