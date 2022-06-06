//arat

CGraphicImageInstance::~CGraphicImageInstance()
{
	Destroy();
}

//altına ekle

D3DXCOLOR CGraphicImageInstance::GetPixelColor(int x, int y)
{
	// we first need the d3d texture, but its the "shortest" way to get it
	D3DXCOLOR dxClr = D3DXCOLOR(0, 0, 0, 0);
	CGraphicImage * pImage = m_roImage.GetPointer();
	if (!pImage)
		return dxClr;
	CGraphicTexture * pTexture = pImage->GetTexturePointer();
	if (!pTexture)
		return dxClr;

	LPDIRECT3DTEXTURE8 d3dTexture = pTexture->GetD3DTexture();
	if (!d3dTexture)
		return dxClr;

	IDirect3DSurface8* surface;
	D3DSURFACE_DESC desc;
	D3DLOCKED_RECT rect;
	RECT rc;

	// we want just want to lock only one pixel
	rc.left = x;
	rc.right = x + 1;
	rc.top = y;
	rc.bottom = y + 1;

	if (FAILED(d3dTexture->GetSurfaceLevel(0, &surface))) // get the top surface of the image (it contains the whole image)
		return dxClr;
	if (FAILED(surface->GetDesc(&desc)))
		return dxClr;
	if (FAILED(surface->LockRect(&rect, &rc, D3DLOCK_READONLY | D3DLOCK_NO_DIRTY_UPDATE | D3DLOCK_NOSYSLOCK))) // lock the pixel
		return dxClr;

	PBYTE dwTexel = (PBYTE)rect.pBits;

	switch (desc.Format)
	{
	// there are several possible image formats, but its the most common one and as I saw its more than enough
	case D3DFMT_A8R8G8B8:
		dxClr.a = dwTexel[3];
		dxClr.r = dwTexel[2];
		dxClr.g = dwTexel[1];
		dxClr.b = dwTexel[0];
		break;
	}
	surface->UnlockRect(); // unlock the pixel for further using (like render)

	return dxClr;
}