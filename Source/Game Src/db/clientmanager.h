//arat

void RequestChannelStatus(CPeer* peer, DWORD dwHandle);

//altına ekle

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	void		FindChannel(CPeer* pkPeer, DWORD dwHandle, TPacketChangeChannel* p);
#endif