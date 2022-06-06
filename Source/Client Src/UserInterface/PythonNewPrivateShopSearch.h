#include "StdAfx.h"

class CPythonNewPrivateShopSearch : public CSingleton<CPythonNewPrivateShopSearch>
{
	public:
		struct TSearchItemData : TItemData
		{
			DWORD vid;
			long long price;
			BYTE Cell;
			int shop_time;
			long ch_map_index;
			long off_shop_map_index;
			int item_state;
			DWORD item_id;
			std::string sellerName;
		};

		using TItemInstanceVector = std::vector<TSearchItemData>;

	public:
		CPythonNewPrivateShopSearch();
		virtual ~CPythonNewPrivateShopSearch();

		void AddItemData(const TSearchItemData& rItemData);
		void ClearItemData();

		DWORD GetItemDataCount()
		{
			return m_ItemInstanceVector.size();
		}
		
		DWORD GetItemDataPtr(DWORD index, TSearchItemData** ppInstance);

	protected:
		TItemInstanceVector m_ItemInstanceVector;
};
