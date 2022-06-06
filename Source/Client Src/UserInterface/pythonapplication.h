//definelere ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
#include "PythonPrivateShopSearch.h"
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
#include "PythonNewPrivateShopSearch.h"
#endif

//arat

CPythonMessenger			m_pyManager;

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
		CPythonPrivateShopSearch m_pyPrivateShopSearch;
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
		CPythonNewPrivateShopSearch m_pyNewPrivateShopSearch;
#endif