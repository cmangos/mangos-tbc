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

#ifndef _VOICECHATSERVERSSOCKET_H
#define _VOICECHATSERVERSSOCKET_H

#include "Common.h"
#include "Network/AsyncSocket.hpp"

#include <chrono>
#include <functional>
#include <deque>

class VoiceChatServerPacket;

class VoiceChatServerSocket : public MaNGOS::AsyncSocket<VoiceChatServerSocket>
{
    private:
        bool ProcessIncomingData() override;
        std::mutex m_voiceChatServerSocketMutex;

    public:
        VoiceChatServerSocket(boost::asio::io_service& service);
        bool OnOpen() override;
        void SendPacket(const VoiceChatServerPacket& pct);
};

#endif
