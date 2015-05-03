#include "CSVReader.h"

CSVReader::~CSVReader()
{

}

bool CSVReader::GetIntValue( unsigned int uiRow, unsigned int uiCol, unsigned int &riValue )
{
	const std::string* pStr = GetStringValue(uiRow, uiCol);  
	if (pStr)  
	{  
		riValue = atoi(pStr->c_str());  
		return true;  
	}   
	else  
	{  
		return false;  
	}  
}

bool CSVReader::GetFloatValue( unsigned int uiRow, unsigned int uiCol, float &rfValue )
{
	const std::string* pStr = GetStringValue(uiRow, uiCol);  
	if (pStr)  
	{  
		rfValue = atof(pStr->c_str());  
		return true;  
	}   
	else  
	{  
		return false;  
	}  
}

bool CSVReader::GetIntValue(std::string strAttribute, unsigned int uiRow, unsigned int &riValue)
{
	const std::string* pStr = GetStringValueWithTitle(strAttribute,uiRow);  
	if (pStr)  
	{  
		riValue = atoi(pStr->c_str());  
		return true;  
	}   
	else  
	{  
		return false;  
	}  
}

bool CSVReader::GetFloatValue(std::string strAttribute, unsigned int uiRow, float &rfValue)
{
	const std::string* pStr = GetStringValueWithTitle(strAttribute, uiRow);  
	if (pStr)  
	{  
		rfValue = atof(pStr->c_str());  
		return true;  
	}   
	else  
	{  
		return false;  
	} 
}

const std::string* CSVReader::GetStringValue( unsigned int uiRow, unsigned int uiCol )
{
	std::map<unsigned int, std::map<unsigned int, std::string> >::iterator iter = m_StringMap.find(uiRow);  
	if (iter != m_StringMap.end())  
	{  
		std::map<unsigned int, std::string> &rStrMap = iter->second;  
		std::map<unsigned int, std::string>::iterator it = rStrMap.find(uiCol);  
		if (it != rStrMap.end())  
		{  
			return &(it->second);  
		}   
		else  
		{  
			return NULL;  
		}  
	}   
	else  
	{  
		return NULL;  
	}  
}

const std::string* CSVReader::GetStringValueWithTitle( std::string strAttribute, unsigned int uiRow)
{
	int col = 0;
	std::map<std::string, unsigned int>::iterator titleIter = m_TitleMap.find(strAttribute);
	if (titleIter != m_TitleMap.end())
	{
		col =  titleIter->second;
	}

	std::map<unsigned int, std::map<unsigned int, std::string> >::iterator iter = m_StringMap.find(uiRow);  
	if (iter != m_StringMap.end())  
	{  
		std::map<unsigned int, std::string> &rStrMap = iter->second;  
		std::map<unsigned int, std::string>::iterator it = rStrMap.find(col);  
		if (it != rStrMap.end())  
		{  
			return &(it->second);  
		}   
		else  
		{  
			return NULL;  
		}  
	}   
	else  
	{  
		return NULL;  
	}  
}

int CSVReader::GetParamFromString( std::string str, std::vector<std::string> &stringVec, char delim /*= ','*/ )
{
	char *token = strtok(const_cast<char *>(str.c_str()), &delim);  
	while (token)  
	{  
		std::string strTemp = token;  
		stringVec.push_back(strTemp);  
		token = strtok(NULL, &delim);  
	}  

	return stringVec.size();  
}

bool CSVReader::LoadCSV( const char *path )
{
	FILE *pFile = fopen(path, "r");  

	if (pFile)  
	{  
		fseek(pFile, 0, SEEK_END);  
		unsigned int uSize = ftell(pFile);  
		rewind(pFile);  

		char *fileBuffer = new char[uSize];  
		fread(fileBuffer, 1, uSize, pFile);  

		//test
		std::map<unsigned int, std::string> stringTitleMap;
		char *pTitleBegin = fileBuffer;  
		char *pTitleEnd = strchr(pTitleBegin, '\n'); 
		std::string strTitles;  
		strTitles.insert(0, pTitleBegin, pTitleEnd-pTitleBegin);  
		{
			std::vector<std::string> stringVec;  
			std::map<unsigned int, std::string> stringMapTemp;  

			assert(GetParamFromString(strTitles, stringVec) > 0);  

			std::vector<std::string>::size_type idx = 0; 

			for (; idx != stringVec.size(); ++idx)  
			{  
				m_TitleMap[stringVec[idx]] = idx;  
			}
		}
		//end

		std::map<unsigned int, std::string> stringMap;  
		unsigned int uiIndex = 1; 
		//这里是排除掉第一行
		char *pBegin = fileBuffer;  
		char *pEnd = strchr(pBegin, '\n');  
		//

		pBegin = pEnd + 1;  
		pEnd = strchr(pBegin, '\n');  

		while (pEnd)  
		{  
			std::string strTemp;  
			strTemp.insert(0, pBegin, pEnd-pBegin);  
			assert(!strTemp.empty());  
			stringMap[uiIndex++] = strTemp;  
			pBegin = pEnd + 1;  
			pEnd = strchr(pBegin, '\n');  
		}  
		delete []fileBuffer;  
		fileBuffer = NULL;  
		pBegin = NULL;  
		pEnd = NULL;  

		std::map<unsigned int, std::string>::iterator iter = stringMap.begin();

		for (; iter != stringMap.end(); ++iter)  
		{  
			std::vector<std::string> stringVec;  
			std::map<unsigned int, std::string> stringMapTemp;  

			assert(GetParamFromString(iter->second, stringVec) > 0);  

			std::vector<std::string>::size_type idx = 0; 

			for (; idx != stringVec.size(); ++idx)  
			{  
				//stringMapTemp[idx + 1] = stringVec[idx];  
				stringMapTemp[idx] = stringVec[idx];  
			}  

			//用第一个做索引
			std::string keyIndexStr = stringVec[0];
			int keyIndex = atoi(keyIndexStr.c_str()); 
			//m_StringMap[iter->first] = stringMapTemp; 
			m_StringMap[keyIndex] = stringMapTemp; 
		}  

		fclose(pFile);  
		m_CSVName = path;  
		return true;  
	}   
	else  
	{  
		return false;  
	}  
}

bool CSVReader::SaveCSV( const char *path /*= NULL*/ )
{
	if (path != NULL)  
	{  
		m_CSVName = path;  
	}  

	FILE *pFile = fopen(m_CSVName.c_str(), "w");  
	if (pFile)  
	{  
		std::map<unsigned int, std::map<unsigned int, std::string>>::iterator iter = m_StringMap.begin();  
		for (; iter != m_StringMap.end(); ++iter)  
		{  
			std::map<unsigned int, std::string> &rStringMap = iter->second;  
			std::map<unsigned int, std::string>::iterator it = rStringMap.begin();  
			for (; it != rStringMap.end(); ++it)  
			{  
				std::string strTemp = it->second;  
				strTemp += ',';  
				fwrite(strTemp.c_str(), strTemp.length(), 1, pFile);  
			}  

			char delim = '\n';  
			fwrite(&delim, 1, 1, pFile);  
		}  

		fclose(pFile);  
		return true;  
	}   
	else  
	{  
		return false;  
	}  
}
