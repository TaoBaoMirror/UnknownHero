#include "TableManager.h"
#include "cocos2d.h"

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
	m_TablePaths[TableType::Table_Hero] = "table/HeroTable.csv";

	//m_TablePaths[TableType::Table_Hero] = "table/HeroTable.csv";

	//m_TablePaths[TableType::Table_Hero] = "table/HeroTable.csv";

	//m_TablePaths[TableType::Table_Hero] = "table/HeroTable.csv";

	//m_TablePaths[TableType::Table_Hero] = "table/HeroTable.csv";
}


TableManager::~TableManager(void)
{
}
//-------------------------------------------------------
void TableManager::LoadAllTable()
{
	//这里加载所有的表
	LoadTable(TableType::Table_Hero);
}

void TableManager::LoadTable(TableType type)
{
	if (m_Tables.find(type) != m_Tables.end())
	{
		return;
	}

	CSVReader* newCSV = nullptr;

	std::string path = GetTablePath(type);

	if (path == "")
	{
		return;
	}

	std::string fullpath = cocos2d::FileUtils::getInstance()->fullPathForFilename(path);

	newCSV = new CSVReader(fullpath.c_str());

	m_Tables[type] = newCSV;
}

std::string TableManager::GetTablePath(TableType type)
{
	if (m_TablePaths.find(type) != m_TablePaths.end())
	{
		return m_TablePaths[type];
	}

	return "";
}

CSVReader* TableManager::GetTable(TableType type)
{
	CSVReader* ret = nullptr;
	if (m_Tables.find(type) != m_Tables.end())
	{
		ret = m_Tables[type];
	}

	return ret;
}

std::string TableManager::GetTableData(TableType type, std::string tabTitle, int index)
{
	CSVReader* pTab = GetTable(type);

	const std::string* dataResult;

	if (pTab != nullptr)
	{
		dataResult = pTab->GetStringValueWithTitle(tabTitle,index);

		//dataResult = pTab->GetStringValue(0,0);
	}

	if (dataResult == nullptr)
	{
		return "";
	}

	return *dataResult;
}

int TableManager::GetTableIntData(TableType type, std::string tabTitle, int index)
{
	CSVReader* pTab = GetTable(type);

	const std::string* dataResult;

	if (pTab != nullptr)
	{
		unsigned int ret = 0;
		if (pTab->GetIntValue(tabTitle,index,ret) == true)
		{
			return (int)ret;
		}
	}

	return 0;
}

//TableData* TableManager::GetTable(TableType type)
//{
//	TableData* ret = nullptr;
//	if (m_Tables.find(type) != m_Tables.end())
//	{
//		ret = m_Tables[type];
//	}
//
//	return ret;
//}
//
//std::string TableManager::GetTableData(TableType type, std::string tabTitle, int index)
//{
//	TableData* pTab = GetTable(type);
//
//	std::string dataResult = "";
//
//	if (pTab != nullptr)
//	{
//		dataResult = pTab->getData(tabTitle,index);
//	}
//
//	return dataResult;
//}
//-------------------------------------------------------
