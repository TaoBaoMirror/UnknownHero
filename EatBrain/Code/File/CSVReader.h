/********************************************************************
	created:	2015/03/25
	created:	25:3:2015   17:25
	filename: 	E:\cyvasse\EatBrain\Code\File\CSVReader.h
	file path:	E:\cyvasse\EatBrain\Code\File
	file base:	CSVReader
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef CSVReader_h__
#define CSVReader_h__

#include <assert.h>
#include <map>
#include <vector>
#include <string>

class CSVReader
{
	std::map<unsigned int, std::map<unsigned int, std::string> >	m_StringMap;
	std::string									m_CSVName;
public:
	CSVReader(){}
	CSVReader(const char *path)
	{
		assert(LoadCSV(path));
	}
	~CSVReader();
	//
	bool GetIntValue(unsigned int uiRow, unsigned int uiCol, unsigned int &riValue);
	bool GetFloatValue(unsigned int uiRow, unsigned int uiCol, float &rfValue);
	const std::string* GetStringValue(unsigned int uiRow, unsigned int uiCol);
	int GetParamFromString(std::string str, std::vector<std::string> &stringVec, char delim  = ',');
	bool LoadCSV(const char *path);
	bool SaveCSV(const char *path = NULL);
	//
	std::map<unsigned int, std::map<unsigned int, std::string> >& GetCSVMap()
	{
		return m_StringMap;
	}
protected:
	
private:
};

#endif // CSVReader_h__
