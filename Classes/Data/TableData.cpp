#include "TableData.h"

#include <cocos2d.h>

TableData::TableData()
	:m_seperator(",")
	,m_colLength(0)
{

}

TableData::~TableData()
{

}

bool TableData::openAndResolveFile(const char *fileName)
{
	std::string pathKey = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
	unsigned char* pBuffer = nullptr;
	ssize_t bufferSize = 0;
	pBuffer = cocos2d::FileUtils::getInstance()->getFileData(pathKey.c_str(), "r", &bufferSize);

	std::string tmpStr = (char*)pBuffer;
	std::string fileContent = tmpStr.substr(0, bufferSize);

	std::vector<std::string> line;
	rowSplit(line, fileContent, '\n');
	for (unsigned int i = 0; i < line.size(); ++i) {
		std::vector<std::string> fieldVector;
		fieldSplit(fieldVector, line[i]);
		data.push_back(fieldVector);
		m_colLength = std::max(m_colLength, (int)fieldVector.size());
	}

	return true;
}


void TableData::rowSplit(std::vector<std::string> &rows, const std::string &content, const char &rowSeperator)
{
	std::string::size_type lastIndex = content.find_first_not_of(rowSeperator, 0);
	std::string::size_type    currentIndex = content.find_first_of(rowSeperator,lastIndex);

	while (std::string::npos != currentIndex || std::string::npos != lastIndex) {
		rows.push_back(content.substr(lastIndex, currentIndex - lastIndex));
		lastIndex = content.find_first_not_of(rowSeperator, currentIndex);
		currentIndex = content.find_first_of(rowSeperator, lastIndex);
	}
}

void TableData::fieldSplit(std::vector<std::string> &fields, std::string line)
{
	if (line[line.length() - 1] == '\r') {
		line = line.substr(0, line.length() - 1);
	}

	std::string field;
	unsigned int i = 0, j = 0;
	while (j < line.length()) {
		if (line[i] == '"') {
			//������
			j = getFieldWithQuoted(line, field, i);
		} else {
			j = getFieldNoQuoted(line, field, i);
		}

		fields.push_back(field);
		i = j + 1; //������һ��field�� ��1Ϊ��������ǰ�ķָ���
	}
}

int TableData::getFieldWithQuoted(const std::string &line, std::string &field, int i)
{
	unsigned int j = 0;
	field = std::string();
	if (line[i] != '"') {
		//����������ʼ��������
		CCLOGERROR("start char is not quote when call %s", __FUNCTION__);
		return -1;
	}

	for (j = i + 1; j < line.length() - 1; ++j) {
		if (line[j] != '"') {
			//��ǰchar��Ϊ���ţ�����field����(��������)
			field += line[j];
		} else {
			//����field����ʱ�����ţ����Է���
			return j;
			break;
		}
	}

	if (j == line.length()) {
		//û���ҵ��ɶԵĽ�������
		CCLOGERROR("resoleve the line error: no pair quote, line:%s, field:%s, start index:%d", line.c_str(), field.c_str(), i);
	}

	return j;
}

int TableData::getFieldNoQuoted(const std::string &line, std::string &field, int index)
{
	unsigned int j = 0;
	//�ҵ���һ���ָ���λ��
	j = line.find_first_of(m_seperator, index);
	if (j > line.length()) {
		j = line.length();
	}

	field = std::string(line, index, j - index);

	return j;
}

///////search data
const char *TableData::getData(unsigned int rowIndex, unsigned int colIndex)
{
	if (rowIndex >= getRowLength() || colIndex >= getColLength()) {
		return "";
	}

	if (colIndex >= data[rowIndex].size()) {
		return "";
	}

	return data[rowIndex][colIndex].c_str();
}

const char *TableData::getData(std::string strAttribute, int nID)
{

	int nRow = data.size();
	int nCol = m_colLength;
	for (int i=1; i<nRow; ++i)
	{
		std::stringstream ss;
		ss<<nID; 
		std::string strId = ss.str();

		if(data[i][0] == strId)
		{
			for(int j=0; j<nCol; ++j)
			{
				if(data[0][j] == strAttribute)
				{
					std::string szData = data[i][j];
					return szData.c_str();
				}
			}
		}
	}

	//if (rowIndex >= getRowLength() || colIndex >= getColLength()) {
	//	return "";
	//}

	//if (colIndex >= data[rowIndex].size()) {
	//	return "";
	//}

	return "";
}