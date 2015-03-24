#ifndef __COMMON_METHOD_H__
#define __COMMON_METHOD_H__

#include <vector>

class ProgressCount
{
	int m_count;

	int m_MaxProgress;

public:
	void setMaxCount(int count)
	{
		m_count = count;
	}

	void setCount(int count)
	{
		m_count = count;
	}

	int getCount()
	{
		return m_count;
	}

	float getCurPercentage();

	static std::vector<std::string> split(std::string str,std::string pattern);
};

#endif //__COMMON_METHOD_H__