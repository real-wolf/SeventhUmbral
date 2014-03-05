#pragma once

#include <deque>
#include "SocketDef.h"
#include "Types.h"
#include "MemStream.h"
#include "PacketUtils.h"
#include "packets/CompositePacket.h"

class CGameServerPlayer
{
public:
								CGameServerPlayer(SOCKET);
	virtual						~CGameServerPlayer();

	bool						IsConnected() const;
	void						Update();

private:
	typedef std::deque<PacketData> PacketQueue;

	void						QueuePacket(const PacketData&);

	void						PrepareInitialPackets();

	void						ProcessKeepAlive(const PacketData&);
	void						ProcessChat(const PacketData&);
	void						ProcessSetPlayerPosition(const PacketData&);
	void						ProcessSetSelection(const PacketData&);
	void						ProcessScriptCommand(const PacketData&);
	void						ProcessScriptResult(const PacketData&);

	void						ScriptCommand_EquipItem(const PacketData&, uint32);
	void						ScriptCommand_Emote(const PacketData&, uint32);
	void						ScriptCommand_TrashItem(const PacketData&, uint32);
	void						ScriptCommand_SwitchToActiveMode(CCompositePacket&);
	void						ScriptCommand_SwitchToPassiveMode(CCompositePacket&);

	void						SendTeleportSequence(uint32, uint32, float, float, float, float);

	SOCKET						m_clientSocket;
	Framework::CMemStream		m_incomingStream;
	PacketQueue					m_packetQueue;
	bool						m_disconnect;
	bool						m_alreadyMovedOutOfRoom;
	bool						m_zoneMasterCreated;
};
