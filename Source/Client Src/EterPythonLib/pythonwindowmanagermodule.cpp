//arat

else if (!stricmp(pszFlag, "ignore_size"))
			pWin->AddFlag(UI::CWindow::FLAG_IGNORE_SIZE);

//altına ekle

		else if (!stricmp(pszFlag, "alpha_sensitive"))
			pWin->AddFlag(UI::CWindow::FLAG_ALPHA_SENSITIVE);
		else if (!stricmp(pszFlag, "remove_limit"))
			pWin->AddFlag(UI::CWindow::FLAG_REMOVE_LIMIT);
		else if (!stricmp(pszFlag, "window_without_alpha"))
			pWin->AddFlag(UI::CWindow::FLAG_IS_BOARD_WITHOUT_ALPHA);

//arat

PyObject * wndButtonIsDown(PyObject * poSelf, PyObject * poArgs)

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
PyObject* wndButtonIsDisable(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	return Py_BuildValue("i", ((UI::CButton*)pWindow)->IsDisable());
}

PyObject* wndImageSetCoolTime(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	
	float fCoolTime;
	if (!PyTuple_GetFloat(poArgs, 1, &fCoolTime))
		return Py_BuildException();

	float fElapsedTime;
	if (!PyTuple_GetFloat(poArgs, 2, &fElapsedTime))
		return Py_BuildException();

	((UI::CImageBox*)pWindow)->SetCoolTime(fCoolTime, fElapsedTime);
	return Py_BuildNone();
}

PyObject* wndImageSetStartCoolTime(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	float fCoolTimeStart;
	if (!PyTuple_GetFloat(poArgs, 1, &fCoolTimeStart))
		return Py_BuildException();

	((UI::CImageBox*)pWindow)->SetCoolTimeStart(fCoolTimeStart);
	return Py_BuildNone();
}

PyObject* wndIsInCoolTime(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	
	return Py_BuildValue("i", ((UI::CImageBox*)pWindow)->IsInCoolTime());
}
#endif

PyObject* wndMgrSetSlotCoverImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	DWORD dwSlotIndex;
	if (!PyTuple_GetUnsignedLong(poArgs, 1, &dwSlotIndex))
		return Py_BuildException();

	char* szFileName;
	if (!PyTuple_GetString(poArgs, 2, &szFileName))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	dynamic_cast<UI::CSlotWindow*>(pWin)->SetSlotCoverImage(dwSlotIndex, szFileName);

	return Py_BuildNone();
}

PyObject* wndMgrEnableSlotCoverImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	DWORD dwSlotIndex;
	if (!PyTuple_GetUnsignedLong(poArgs, 1, &dwSlotIndex))
		return Py_BuildException();

	bool bOnOff;
	if (!PyTuple_GetBoolean(poArgs, 2, &bOnOff))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	dynamic_cast<UI::CSlotWindow*>(pWin)->EnableSlotCoverImage(dwSlotIndex, bOnOff);

	return Py_BuildNone();
}

//arat

{ "IsDown",						wndButtonIsDown,					METH_VARARGS },

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
		{ "IsDisable",					wndButtonIsDisable,					METH_VARARGS },
		{ "SetCoolTimeImageBox",		wndImageSetCoolTime,				METH_VARARGS },
		{ "SetStartCoolTimeImageBox",	wndImageSetStartCoolTime,			METH_VARARGS },
		{ "IsInCoolTime",				wndIsInCoolTime,						METH_VARARGS },
#endif
		{ "SetSlotCoverImage",			wndMgrSetSlotCoverImage,			METH_VARARGS },
		{ "EnableSlotCoverImage",		wndMgrEnableSlotCoverImage,			METH_VARARGS },