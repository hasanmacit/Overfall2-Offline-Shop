//arat

		void			SetChannelStatusRequested(bool bChannelStatusRequested) { m_bChannelStatusRequested = bChannelStatusRequested; }

//altına ekle

#if defined(__ENABLE_PREMIUM_MEMBERS__)
		DWORD GetAccountId() { return m_accountTable.id; }
#endif