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

#include "VoiceChatServerSocket.h"
#include "Network/AsyncConnector.hpp"
#include "VoiceChatMgr.h"

#include <boost/asio.hpp>
#include <utility>

#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif
struct VoiceChatServerPktHeader
{
    uint16 cmd;
    uint16 size;

    const char* data() const {
        return reinterpret_cast<const char*>(this);
    }

    std::size_t headerSize() const {
        return sizeof(VoiceChatServerPktHeader);
    }
};
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

VoiceChatServerSocket::VoiceChatServerSocket(boost::asio::io_service& service) : AsyncSocket(service)
{}

bool VoiceChatServerSocket::OnOpen()
{
    sVoiceChatMgr.RequestNewSocket(this->shared_from_this().get());
    return true;
}

bool VoiceChatServerSocket::ProcessIncomingData()
{
    std::shared_ptr<VoiceChatServerPktHeader> header = std::make_shared<VoiceChatServerPktHeader>();

    auto self(shared_from_this());

    Read((char*)header.get(), sizeof(VoiceChatServerPktHeader), [self, header](const boost::system::error_code& error, std::size_t read) -> void
    {
        if (error) return;

        if ((header->size < 2) || (header->size > 0x2800) || (header->cmd >= VOICECHAT_NUM_OPCODES))
        {
            sLog.outError("VoiceChatServerSocket::ProcessIncomingData: client sent malformed packet size = %u , cmd = %u", header->size, header->cmd);
            return;
        }

        const VoiceChatServerOpcodes opcode = static_cast<VoiceChatServerOpcodes>(header->cmd);

        size_t packetSize = header->size;
        std::shared_ptr<std::vector<uint8>> packetBuffer = std::make_shared<std::vector<uint8>>(packetSize);

        self->Read(reinterpret_cast<char*>(packetBuffer->data()), packetBuffer->size(), [self, packetBuffer, opcode = opcode](const boost::system::error_code& error, std::size_t read) -> void
        {
            if (error) return;
            std::unique_ptr<VoiceChatServerPacket> pct = std::make_unique<VoiceChatServerPacket>(opcode, packetBuffer->size());
            pct->append(*packetBuffer.get());

            try
            {
                sVoiceChatMgr.QueuePacket(std::move(pct));
            }
            catch (ByteBufferException&)
            {
                sLog.outError("VoiceChatServerSocket::ProcessIncomingData ByteBufferException occured while parsing an instant handled packet (opcode: %u).",
                    opcode);

                if (sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))
                {
                    DEBUG_LOG("Dumping error-causing voice server packet:");
                    pct->hexlike();
                }

                DETAIL_LOG("Disconnecting voice server [address %s] for badly formatted packet.",
                    self->GetRemoteAddress().c_str());

                return;
            }
            self->ProcessIncomingData();
        });
    });

    return true;
}

void VoiceChatServerSocket::SendPacket(const VoiceChatServerPacket& pct)
{
    if (IsClosed())
        return;

    std::lock_guard<std::mutex> guard(m_voiceChatServerSocketMutex);

    VoiceChatServerPktHeader header;

    header.cmd = pct.GetOpcode();
    header.size = static_cast<uint8>(pct.size());

    if (pct.size() > 0)
    {
        // allocate array for full message
        std::shared_ptr<std::vector<char>> fullMessage = std::make_shared<std::vector<char>>(header.headerSize() + pct.size());
        std::memcpy(fullMessage->data(), header.data(), header.headerSize()); // copy header
        std::memcpy((fullMessage->data() + header.headerSize()), reinterpret_cast<const char*>(pct.contents()), pct.size()); // copy packet
        auto self(shared_from_this());
        Write(fullMessage->data(), fullMessage->size(), [self, fullMessage](const boost::system::error_code& error, std::size_t read) {});
    }
    else
    {
        std::shared_ptr<VoiceChatServerPktHeader> sharedHeader = std::make_shared<VoiceChatServerPktHeader>(header);
        auto self(shared_from_this());
        Write(sharedHeader->data(), sharedHeader->headerSize(), [self, sharedHeader](const boost::system::error_code& error, std::size_t read) {});
    }
}
