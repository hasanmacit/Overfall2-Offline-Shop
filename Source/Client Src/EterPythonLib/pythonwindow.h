//arat

FLAG_IGNORE_SIZE		= (1 << 10),

//altına ekle

				FLAG_ALPHA_SENSITIVE	= (1 << 12),	// flag for activating alpha sensitive
				FLAG_REMOVE_LIMIT	= (1 << 13),	// flag for activating remove limit
				FLAG_IS_BOARD_WITHOUT_ALPHA	= (1 << 14),

//arat

bool				m_bIsScrollable;

//altına ekle

				BYTE				m_windowType; // to recognize window type

//arat

			int GetHeight();

//altına ekle

			void SetCoolTime(float fCoolTime, float fElapsedTime);
			void SetCoolTimeStart(float fCoolTimeStart);
			BOOL IsInCoolTime();

//arat

int				GetChildCount()	{ return m_pChildList.size(); }

//altına ekle

			void			IsTransparentOnPixel(long* x, long* y, bool* ret);
			void			HaveSomeChildOnOnPixel(long* x, long* y, bool* ret);

//arat

		protected:
			CGraphicImageInstance * m_pImageInstance;

//altına ekle

			float m_fCoolTime;
			float m_fCoolElapsedTime;
			float m_fCoolTimeStart;