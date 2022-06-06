//arat

			case HEADER_GD_REQUEST_CHANNELSTATUS:
				RequestChannelStatus(peer, dwHandle);
				break;

//altına ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
			case HEADER_GD_FIND_CHANNEL:
				FindChannel(peer, dwHandle, (TPacketChangeChannel*)data);
				break;
#endif

//en alta ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
void CClientManager::FindChannel(CPeer* requestPeer, DWORD dwHandle, TPacketChangeChannel* p)
{
	if (!p->lMapIndex || !p->iChannel)
		return;

	long lAddr = 0;
	WORD port = 0;

	for (const auto peer : m_peerList)
	{
		if (peer->GetChannel() != p->iChannel) //not the channel we are looking for!
			continue;

		TMapLocation kMapLocation;
		thecore_memcpy(kMapLocation.alMaps, peer->GetMaps(), sizeof(kMapLocation.alMaps));

		for (const auto midx : kMapLocation.alMaps)
		{
			if (midx == p->lMapIndex)
			{
				//Get host, and convert to int
				char host[16];
				strlcpy(host, peer->GetPublicIP(), sizeof(kMapLocation.szHost));
				lAddr = inet_addr(host);

				//Target port
				port = peer->GetListenPort();

				break;
			}
		}

		if (lAddr && port) //We already obtained them
			break;
	}

	TPacketReturnChannel r;
	r.lAddr = lAddr;
	r.wPort = port;

	requestPeer->EncodeHeader(HEADER_DG_CHANNEL_RESULT, dwHandle, sizeof(r));
	requestPeer->Encode(&r, sizeof(r));
}
#endif