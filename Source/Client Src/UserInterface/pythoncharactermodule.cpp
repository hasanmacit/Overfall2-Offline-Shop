//definelerin hemen altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
PyObject * chrIsOverfallPremium(PyObject * poSelf, PyObject * poArgs)
{
	CInstanceBase * pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
	if (!pInstance)
		return Py_BuildValue("i", 0);

	return Py_BuildValue("i", pInstance->IsOverfallPremium());
}
#endif

//arat

{ "GetBoundBoxOnlyXY",			chrGetBoundBoxOnlyXY,				METH_VARARGS },

//altına ekle

#if defined(ENABLE_PREMIUM_MEMBERS)
		{ "IsOverfallPremium",			chrIsOverfallPremium,				METH_VARARGS },
#endif

//en alta ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "AFFECT_OFFLINE_SHOP", CInstanceBase::AFFECT_OFFLINE_SHOP);
	//PyModule_AddIntConstant(poModule, "EFFECT_OWN_OFFLINE_SHOP", CInstanceBase::EFFECT_OWN_OFFLINE_SHOP);
#endif
#if defined(ENABLE_PREMIUM_MEMBERS)
	PyModule_AddIntConstant(poModule, "AFFECT_OVERFALL_PREMIUM", CInstanceBase::NEW_AFFECT_OVERFALL_PREMIUM);
#endif