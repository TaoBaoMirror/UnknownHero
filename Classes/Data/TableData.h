#ifndef __TABLE_DATA_H__
#define __TABLE_DATA_H__

#include <string>

#include <vector>

class TableData
{
public:
	TableData(void);
	~TableData(void);

	bool openAndResolveFile(const char *fileName);

	const char *getData(unsigned int rowIndex, unsigned int colIndex);
	const char *getData(std::string strAttribute, int nID);

	inline int getColLength() { return m_colLength; }
	inline int getRowLength() {    return data.size(); }

private:
	const std::string m_seperator;
	std::vector<std::vector<std::string> > data;

	//cols length
	int m_colLength;

	void rowSplit(std::vector<std::string> &rows, const std::string &content, const char &rowSeperator);
	void fieldSplit(std::vector<std::string> &fields, std::string line);

	//获取带引号的字段
	int getFieldWithQuoted(const std::string &line, std::string& field, int index);

	//获取无引号的字段
	int getFieldNoQuoted(const std::string &line, std::string &field, int index);

};

#endif //__TABLE_DATA_H__
