#include "Stdafx.h"
#include "packet.h"
#include "PythonNewPrivateShopSearch.h"

CPythonNewPrivateShopSearch::CPythonNewPrivateShopSearch()
{
}

CPythonNewPrivateShopSearch::~CPythonNewPrivateShopSearch()
{
}

void CPythonNewPrivateShopSearch::AddItemData(const TSearchItemData& rItemData)
{
	m_ItemInstanceVector.push_back(rItemData);
}

void CPythonNewPrivateShopSearch::ClearItemData()
{
	m_ItemInstanceVector.clear();
}

DWORD CPythonNewPrivateShopSearch::GetItemDataPtr(DWORD index, TSearchItemData** ppInstance)
{
	*ppInstance = &m_ItemInstanceVector.at(index);
	return 1;
}

PyObject* newprivateShopSearchGetSearchItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BadArgument();

	int iSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSocketIndex))
		return Py_BadArgument();

	if (iSocketIndex >= ITEM_SOCKET_SLOT_MAX_NUM)
		return Py_BuildException();

	CPythonNewPrivateShopSearch::TSearchItemData* pItemData;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildException();

	return Py_BuildValue("i", pItemData->alSockets[iSocketIndex]);
}

PyObject* newprivateShopSearchGetSearchItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();

	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		CPythonNewPrivateShopSearch::TSearchItemData* pItemData;
		if (CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iSlotIndex, &pItemData))
		{
			return Py_BuildValue("ii", pItemData->aAttr[iAttrSlotIndex].bType, pItemData->aAttr[iAttrSlotIndex].sValue);
		}
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* newprivateShopSearchGetItemCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonNewPrivateShopSearch::Instance().GetItemDataCount());
}

PyObject* newprivateShopSearchGetSearchItemCount(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->count);
}

PyObject* newprivateShopSearchGetSearchItemPrice(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	long long llGold = pInstance->price;
	return PyLong_FromLongLong(llGold);
}

PyObject* newprivateShopSearchGetSearchItemShopVID(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->vid);
}

PyObject* newprivateShopSearchGetSearchItemPos(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->Cell);
}

PyObject* newprivateShopSearchGetSearchItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->vnum);
}

PyObject* newprivateShopGetSearchItemShopTime(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->shop_time);
}

PyObject* newprivateShopGetPlayerSearchMapIndex(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->ch_map_index);
}

PyObject* newprivateShopGetOfflineShopMapIndex(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->off_shop_map_index);
}

PyObject* newprivateShopGetItemState(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->item_state);
}

PyObject* newprivateShopSetItemState(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	int iState;
	if (!PyTuple_GetInteger(poArgs, 1, &iState))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		pInstance->item_state = iState;

	return Py_BuildNone();
}

PyObject* newprivateReloadItemPrice(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	long long llPrice;
	if (!PyTuple_GetLongLong(poArgs, 1, &llPrice))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		pInstance->price = llPrice;

	return Py_BuildNone();
}

#ifdef __BL_TRANSMUTATION__
PyObject* newprivateShopSearchGetSearchItemTransmutation(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->dwTransmutationVnum);
}
#endif

PyObject* newprivateShopSearchGetSearchItemId(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->item_id);
}

PyObject* newprivateShopSearchGetSearchItemSellerName(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonNewPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonNewPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("s", pInstance->sellerName.c_str());
}

PyObject* newprivateShopSearchClearSearchItems(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNewPrivateShopSearch::Instance().ClearItemData();
	return Py_BuildNone();
}

void initnewprivateShopSearch()
{
	static PyMethodDef s_methods[] =
	{
		{ "GetItemCount", newprivateShopSearchGetItemCount, METH_VARARGS },

		{ "GetSearchItemCount", newprivateShopSearchGetSearchItemCount, METH_VARARGS },
		{ "GetSearchItemPrice", newprivateShopSearchGetSearchItemPrice, METH_VARARGS },
		{ "GetSearchItemVnum", newprivateShopSearchGetSearchItemVnum, METH_VARARGS },
		{ "GetSearchItemShopTime", newprivateShopGetSearchItemShopTime, METH_VARARGS },
		{ "GetPlayerSearchMapIndex", newprivateShopGetPlayerSearchMapIndex, METH_VARARGS },
		{ "GetOfflineShopMapIndex", newprivateShopGetOfflineShopMapIndex, METH_VARARGS },
		{ "GetSearchItemId", newprivateShopSearchGetSearchItemId, METH_VARARGS },
		{ "GetSearchItemSellerName", newprivateShopSearchGetSearchItemSellerName, METH_VARARGS },
		{ "GetItemState", newprivateShopGetItemState, METH_VARARGS },
		{ "SetItemState", newprivateShopSetItemState, METH_VARARGS },
		{ "ReloadItemPrice", newprivateReloadItemPrice, METH_VARARGS },

		{ "GetSearchItemShopVID", newprivateShopSearchGetSearchItemShopVID, METH_VARARGS },

		{ "ClearSearchItems", newprivateShopSearchClearSearchItems, METH_VARARGS },

		{ "GetSearchItemMetinSocket", newprivateShopSearchGetSearchItemMetinSocket, METH_VARARGS },
		{ "GetSearchItemAttribute", newprivateShopSearchGetSearchItemAttribute, METH_VARARGS },

#ifdef __BL_TRANSMUTATION__
		{ "GetSearchItemTransmutation", newprivateShopSearchGetSearchItemTransmutation, METH_VARARGS },
#endif

		{ "GetSearchItemPos", newprivateShopSearchGetSearchItemPos, METH_VARARGS },

		{ NULL, NULL, NULL },
	};

	PyObject* poModule = Py_InitModule("newPrivateShopSearch", s_methods);

	PyModule_AddIntConstant(poModule, "NPSS_HAVE_PAGE_OPENED",	NPSS_HAVE_PAGE_OPENED);
	PyModule_AddIntConstant(poModule, "NPSS_PLEASE_WAIT",	NPSS_PLEASE_WAIT);
	PyModule_AddIntConstant(poModule, "NPSS_NEED_TO_BE_IN_EMPIRE",	NPSS_NEED_TO_BE_IN_EMPIRE);
	PyModule_AddIntConstant(poModule, "NPSS_NEED_OTHER_ERROR",	NPSS_NEED_OTHER_ERROR);
}
