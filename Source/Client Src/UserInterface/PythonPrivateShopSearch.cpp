#include "Stdafx.h"
#include "PythonPrivateShopSearch.h"

CPythonPrivateShopSearch::CPythonPrivateShopSearch()
{
}

CPythonPrivateShopSearch::~CPythonPrivateShopSearch()
{
}

#ifdef ENABLE_CHEQUE_SYSTEM
void CPythonPrivateShopSearch::AddItemData(DWORD vid, long long price, DWORD price_cheque, const TSearchItemData& rItemData)
#else
void CPythonPrivateShopSearch::AddItemData(DWORD vid, long long price, const TSearchItemData& rItemData)
#endif
{
	m_ItemInstanceVector.push_back(rItemData);
}

void CPythonPrivateShopSearch::ClearItemData()
{
	m_ItemInstanceVector.clear();
}

DWORD CPythonPrivateShopSearch::GetItemDataPtr(DWORD index, TSearchItemData** ppInstance)
{
	*ppInstance = &m_ItemInstanceVector.at(index);
	return 1;
}

PyObject* privateShopSearchGetSearchItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BadArgument();

	int iSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSocketIndex))
		return Py_BadArgument();

	if (iSocketIndex >= ITEM_SOCKET_SLOT_MAX_NUM)
		return Py_BuildException();

	CPythonPrivateShopSearch::TSearchItemData* pItemData;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildException();

	return Py_BuildValue("i", pItemData->alSockets[iSocketIndex]);
}

PyObject* privateShopSearchGetSearchItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();

	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		CPythonPrivateShopSearch::TSearchItemData* pItemData;
		if (CPythonPrivateShopSearch::Instance().GetItemDataPtr(iSlotIndex, &pItemData))
		{
			return Py_BuildValue("ii", pItemData->aAttr[iAttrSlotIndex].bType, pItemData->aAttr[iAttrSlotIndex].sValue);
		}
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* privateShopSearchGetItemCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPrivateShopSearch::Instance().GetItemDataCount());
}

PyObject* privateShopSearchGetSearchItemCount(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->count);
}

PyObject* privateShopSearchGetSearchItemPrice(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->price);
}

#ifdef ENABLE_CHEQUE_SYSTEM
PyObject* privateShopSearchGetSearchItemPriceCheque(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->price_cheque);
}
#endif

PyObject* privateShopSearchGetSearchItemShopVID(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->vid);
}

PyObject* privateShopSearchGetSearchItemPos(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->Cell);
}

PyObject* privateShopSearchGetSearchItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->vnum);
}

#ifdef __BL_TRANSMUTATION__
PyObject* privateShopSearchGetSearchItemTransmutation(PyObject* poSelf, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BadArgument();

	CPythonPrivateShopSearch::TSearchItemData* pInstance;
	if (!CPythonPrivateShopSearch::Instance().GetItemDataPtr(iPos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->dwTransmutationVnum);
}
#endif

PyObject* privateShopSearchClearSearchItems(PyObject* poSelf, PyObject* poArgs)
{
	CPythonPrivateShopSearch::Instance().ClearItemData();
	return Py_BuildNone();
}

void initprivateShopSearch()
{
	static PyMethodDef s_methods[] =
	{
		{ "GetItemCount", privateShopSearchGetItemCount, METH_VARARGS },

		{ "GetSearchItemCount", privateShopSearchGetSearchItemCount, METH_VARARGS },
		{ "GetSearchItemPrice", privateShopSearchGetSearchItemPrice, METH_VARARGS },
#ifdef ENABLE_CHEQUE_SYSTEM
		{ "GetSearchItemPriceCheque", privateShopSearchGetSearchItemPriceCheque, METH_VARARGS },
#endif
		{ "GetSearchItemVnum", privateShopSearchGetSearchItemVnum, METH_VARARGS },

		{ "GetSearchItemShopVID", privateShopSearchGetSearchItemShopVID, METH_VARARGS },

		{ "ClearSearchItems", privateShopSearchClearSearchItems, METH_VARARGS },

		{ "GetSearchItemMetinSocket", privateShopSearchGetSearchItemMetinSocket, METH_VARARGS },
		{ "GetSearchItemAttribute", privateShopSearchGetSearchItemAttribute, METH_VARARGS },

#ifdef __BL_TRANSMUTATION__
		{ "GetSearchItemTransmutation", privateShopSearchGetSearchItemTransmutation, METH_VARARGS },
#endif

		{ "GetSearchItemPos", privateShopSearchGetSearchItemPos, METH_VARARGS },

		{ NULL, NULL, NULL },
	};

	PyObject* poModule = Py_InitModule("privateShopSearch", s_methods);
}
