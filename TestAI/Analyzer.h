#ifndef Analyzer_h__
#define Analyzer_h__

#include "GridSceneMap.h"
#include <list>
class AnalyzerUnit;
class Analyzer
{
public:

	static Analyzer*	Instance();
	virtual ~Analyzer();
	//
	virtual void Init(GridSceneMap* GSMap,int Camp);
	virtual void Free();
	//
	//
	void	AddUnit(AnalyzerUnit* unit);
	void	RemoveUnit(AnalyzerUnit* unit);
	//
	virtual void	Decision(int Round);
protected:
	//
	virtual void	Analysis(int Round);

	//
	int				mCamp;
	int				mRound;	//»ØºÏÊý

	GridSceneMap*	mGSMap;
	std::list<AnalyzerUnit*>	mAnalyzerUnitList;
	std::vector< std::pair<float,std::list<AnalyzerUnit*>::iterator> >	mScores;



protected:
	Analyzer();
	
private:
};

class AnalyzerUnit
{
public:
	AnalyzerUnit(int Camp):mCamp(Camp){}
	virtual ~AnalyzerUnit();
	//
	virtual float Analysis() = 0;
	virtual void Decision() = 0;
	inline	int GetCamp(){return mCamp;}
	//
protected:
	int		mCamp;
private:
};

#endif // Analyzer_h__
