//arat

else if (!strcmpi(szCmd, "ObserverTeamInfo"))

//altına ekle

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
	else if (!strcmpi(szCmd, "OfflineShopCount"))
	{
		if (TokenVector.size() < 2)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		BYTE count = atoi(TokenVector[1].c_str());
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Count", Py_BuildValue("i", count));
	}
	else if (!strcmpi(szCmd, "OfflineShopSales"))
	{
		if (TokenVector.size() < 6)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		const std::string & buyerName = TokenVector[1].c_str();
		UINT itemVnum = atoi(TokenVector[2].c_str());
		UINT itemCount = atoi(TokenVector[3].c_str());
		long long itemPrice = atoi(TokenVector[4].c_str());
		UINT itemCheque = atoi(TokenVector[5].c_str());
		UINT itemDate = atoi(TokenVector[6].c_str());
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Sales", Py_BuildValue("(siiLii)", buyerName.c_str(), itemVnum, itemCount, itemPrice, itemCheque, itemDate));
	}
#endif

//arat

	else if (!strcmpi(szCmd, "BettingMoney"))
	{
		if (2 != TokenVector.size())
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		//UINT uMoney= atoi(TokenVector[1].c_str());

	}

//altına ekle

#ifdef ENABLE_PRIVATE_SHOP_SEARCH_SYSTEM
	else if (!strcmpi(szCmd, "ShopSearchError"))
	{
		if (TokenVector.size() < 2)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		BYTE error = atoi(TokenVector[1].c_str());
		switch (error)
		{
		case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY"));
			break;

		case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY_EX:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY_EX"));
			break;

		case SHOP_SUBHEADER_GC_SOLDOUT:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "SOLDOUT"));
			break;

		case SHOP_SUBHEADER_GC_INVENTORY_FULL:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "INVENTORY_FULL"));
			break;

		case SHOP_SUBHEADER_GC_INVALID_POS:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "INVALID_POS"));
			break;

#ifdef ENABLE_CHEQUE_SYSTEM
		case SHOP_SUBHEADER_GC_NOT_ENOUGH_CHEQUE:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_CHEQUE"));
			break;
#endif
		}
	}
	// else if (!strcmpi(szCmd, "OpenShopSearch"))
	// {
		// if (TokenVector.size() < 2)
		// {
			// TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			// return;
		// }

		// BYTE type = atoi(TokenVector[1].c_str());
		// PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OpenPrivateShopSearch", Py_BuildValue("(i)", type));
	// }
	else if (!strcmpi(szCmd, "ShopSearchBuy"))
	{
		if (TokenVector.size() < 1)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BuyShopSearch", Py_BuildValue("()"));
	}
#endif
#if defined(ENABLE_NEW_PRIVATE_SHOP_SEARCH_SYSTEM)
	else if (!strcmpi(szCmd, "NewShopSearch_Error"))
	{
		if (TokenVector.size() < 1)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}
		
		DWORD error_id = (DWORD)atoi(TokenVector[1].c_str());
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_NewPrivateShopSearch_Error", Py_BuildValue("(i)", error_id));
	}
	else if (!strcmpi(szCmd, "NewShopSearchFinish"))
		__RefreshNewShopSearchWindow();
	else if (!strcmpi(szCmd, "NewShopSearchBuy"))
	{
		if (TokenVector.size() < 1)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}
		
		DWORD shop_pos = (DWORD)atoi(TokenVector[1].c_str());
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_NewShopSearchBuy", Py_BuildValue("(i)", shop_pos));

	}
	else if (!strcmpi(szCmd, "NewShopSearchRemoved"))
	{
		if (TokenVector.size() < 1)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}
		
		DWORD shop_pos = (DWORD)atoi(TokenVector[1].c_str());
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_NewShopSearchRemoved", Py_BuildValue("(i)", shop_pos));

	}
	else if (!strcmpi(szCmd, "NewShopSearchPriceChanged"))
	{
		if (TokenVector.size() < 2)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		PyObject *args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, Py_BuildValue("i", (DWORD)atoi(TokenVector[1].c_str())));
		PyTuple_SetItem(args, 1, PyLong_FromLongLong((long long)atoi(TokenVector[2].c_str())));
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_NewShopSearchPriceChanged", args);
	}
	else if (!strcmpi(szCmd, "NewShopBuyError"))
	{
		if (TokenVector.size() < 2)
		{
			TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
			return;
		}

		BYTE error = atoi(TokenVector[1].c_str());
		switch (error)
		{
			case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY"));
				break;

			case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY_EX:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY_EX"));
				break;

			case SHOP_SUBHEADER_GC_SOLDOUT:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "SOLDOUT"));
				break;
			
			case SHOP_SUBHEADER_GC_SOLD_OUT:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "SOLDOUT"));
				break;

			case SHOP_SUBHEADER_GC_REMOVED_FROM_SHOP:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "REMOVED_FROM_SHOP"));
				break;

			case SHOP_SUBHEADER_GC_INVENTORY_FULL:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "INVENTORY_FULL"));
				break;

			case SHOP_SUBHEADER_GC_INVALID_POS:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "INVALID_POS"));
				break;
			
			case SHOP_SUBHEADER_GC_BUY_FROM_OWNSHOP:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "OWN_SHOP_BUY"));
				break;
			
			case SHOP_SUBHEADER_GC_PRICE_CHANGED:
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnNewShopError", Py_BuildValue("(s)", "PRICE_WAS_CHANGED"));
				break;
		}
	}
#endif