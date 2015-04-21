#include "TableManager.h"

//-------------------------------------------------------
TableManager* TableManager::m_Instance = nullptr;

TableManager* TableManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new TableManager();
	}

	return m_Instance;
}
//-------------------------------------------------------
TableManager::TableManager(void)
{
}


TableManager::~TableManager(void)
{
}
//-------------------------------------------------------
void TableManager::LoadAllTable()
{
	//这里加载所有的表
}

TableData* TableManager::GetTable(TableType type)
{
	TableData* ret = nullptr;
	if (m_Tables.find(type) != m_Tables.end())
	{
		ret = m_Tables[type];
	}

	return ret;
}

std::string TableManager::GetTableData(TableType type, std::string tabTitle, int index)
{
	TableData* pTab = GetTable(type);

	std::string dataResult = "";

	if (pTab != nullptr)
	{
		dataResult = pTab->getData(tabTitle,index);
	}

	return dataResult;
}
//-------------------------------------------------------
