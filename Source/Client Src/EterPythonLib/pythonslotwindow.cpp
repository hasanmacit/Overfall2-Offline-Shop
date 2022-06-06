//arat

if (pSlot->pSignImage)

//altına ekle

	if (pSlot->pCoverImage)
	{
		pSlot->pCoverImage->Hide();
	}

//arat

if (rSlot.pInstance)

//altına ekle

		if (rSlot.pCoverImage)
		{
			rSlot.pCoverImage->SetPosition(m_rect.left + rSlot.ixPosition, m_rect.top + rSlot.iyPosition);
			rSlot.pCoverImage->Render();
		}

//arat

void CSlotWindow::SetSlotCoolTime

//altına ekle

void CSlotWindow::SetSlotCoverImage(const DWORD dwIndex, const char* FileName)
{
	TSlot* pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	auto& CoverImage = pSlot->pCoverImage;
	if (CoverImage == nullptr)
		CoverImage = std::make_shared<CImageBox>(nullptr);

	CoverImage->LoadImage(FileName);
	CoverImage->Show();
}

void CSlotWindow::EnableSlotCoverImage(const DWORD dwIndex, const bool bEnable)
{
	TSlot* pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	const auto& CoverImage = pSlot->pCoverImage;
	if (CoverImage == nullptr)
		return;
	
	if (bEnable)
		CoverImage->Show();
	else
		CoverImage->Hide();
}