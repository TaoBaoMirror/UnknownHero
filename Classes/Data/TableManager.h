#ifndef __TABLE_MANAGER_H__
#define __TABLE_MANAGER_H__

#include <string>
#include <map>

#include "Data/TableData.h"

enum TableType
{
	Table_Hero = 0,
};


class TableManager
{
public:
	static TableManager* GetInstance();
	
	~TableManager(void);

	void LoadAllTable();

	TableData* GetTable(TableType type);

	std::string GetTableData(TableType type, std::string tabTitle, int index);

private:
	TableManager(void);

	static TableManager* m_Instance;

	//-----------------------

	std::map<TableType,TableData*> m_Tables;


};

#endif //__TABLE_MANAGER_H__
