#ifndef __TABLE_MANAGER_H__
#define __TABLE_MANAGER_H__

#include <string>
#include <map>

#include "Data/TableData.h"
#include "File/CSVReader.h"

enum TableType
{
	Table_Hero = 0,
	Table_Monster,
};


class TableManager
{
public:
	static TableManager* GetInstance();
	
	~TableManager(void);

	void LoadAllTable();

	//TableData* GetTable(TableType type);

	//std::string GetTableData(TableType type, std::string tabTitle, int index);

	CSVReader* GetTable(TableType type);

	std::string GetTableData(TableType type, std::string tabTitle, int index);

	int GetTableIntData(TableType type, std::string tabTitle, int index);

private:
	TableManager(void);

	static TableManager* m_Instance;
	//-----------------------
	void LoadTable(TableType type);

	std::string GetTablePath(TableType type);
	//-----------------------
	std::map<TableType,std::string> m_TablePaths;
	//std::map<TableType,TableData*> m_Tables;
	std::map<TableType,CSVReader*> m_Tables;

};

#endif //__TABLE_MANAGER_H__
