//arat

		if (IsFlag(CWindow::FLAG_NOT_PICK))
			return NULL;

//altına ekle

		if (IsFlag(CWindow::FLAG_IS_BOARD_WITHOUT_ALPHA)) // check flag
		{
			return NULL;
		}

		if (IsFlag(CWindow::FLAG_ALPHA_SENSITIVE)) // check flag
		{
			bool isFullTransparent = true;
			IsTransparentOnPixel(&x, &y, &isFullTransparent); // check transparency of the clicking position
			if (isFullTransparent)
				return NULL; // if transparent then return nothing, else give current window
		}

//hemen altındaki şu kodu gör 

		return (this);
	}

//altına ekle

	void CWindow::IsTransparentOnPixel(long* x, long* y, bool* ret)
	{
		if (IsShow() && IsIn(*x, *y)) // check if the window is active and the cursor is in the window
		{
			if (m_windowType == WINDOW_TYPE_EX_IMAGE) // check if its an expanded_image
			{
				D3DXCOLOR pixel = ((CExpandedImageBox*)this)->GetPixelColor(*x - m_rect.left, *y - m_rect.top); // get current pixel color

				if ((BYTE)pixel.a != 0) // if the pixel is not trasparent then the whole window is not trasparent
				{
					*ret = false;
					return;
				}
			}
			else if (m_pChildList.empty()) // if its not ex_image and has no child then its NOT transparent [default for other components]
			{
				*ret = false;
				return;
			}
		}
		if (!m_pChildList.empty()) // check if all the childs are trasparent on the current position
		{
			std::list<CWindow *>::reverse_iterator ritor = m_pChildList.rbegin();
			for (; ritor != m_pChildList.rend(); ritor++)
			{
				(*ritor)->IsTransparentOnPixel(x, y, ret);
				if (!*ret)
					return;
			}
		}
	}

	void CWindow::HaveSomeChildOnOnPixel(long* x, long* y, bool* ret)
	{
		if (IsShow() && IsIn(*x, *y)) // check if the window is active and the cursor is in the window
		{
			if (m_windowType == WINDOW_TYPE_EX_IMAGE) // check if its an expanded_image
			{
				D3DXCOLOR pixel = ((CExpandedImageBox*)this)->GetPixelColor(*x - m_rect.left, *y - m_rect.top); // get current pixel color

				if ((BYTE)pixel.a != 0) // if the pixel is not trasparent then the whole window is not trasparent
				{
					*ret = false;
					return;
				}
			}
			else if (m_pChildList.empty()) // if its not ex_image and has no child then its NOT transparent [default for other components]
			{
				*ret = false;
				return;
			}
		}
		if (!m_pChildList.empty()) // check if all the childs are trasparent on the current position
		{
			std::list<CWindow *>::reverse_iterator ritor = m_pChildList.rbegin();
			for (; ritor != m_pChildList.rend(); ritor++)
			{
				(*ritor)->IsTransparentOnPixel(x, y, ret);
				if (!*ret)
					return;
			}
		}
	}

//arat

	void CImageBox::OnChangePosition()
	{
		if (!m_pImageInstance)
			return;

		m_pImageInstance->SetPosition(m_rect.left, m_rect.top);
	}

//altına ekle

	void CImageBox::SetCoolTime(float fCoolTime, float fElapsedTime)
	{
		m_fCoolTime = fCoolTime;
		m_fCoolElapsedTime = fElapsedTime;
	}

	void CImageBox::SetCoolTimeStart(float fCoolTimeStart)
	{
		m_fCoolTimeStart = fCoolTimeStart;
	}
	
	BOOL CImageBox::IsInCoolTime()
	{
		BOOL inInCoolTime = (m_fCoolTime > 0.0f);
		return inInCoolTime;
	}