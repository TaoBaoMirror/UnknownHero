#include "stdafx.h"
#include "Analyzer.h"

Analyzer::Analyzer()
{
	mGSMap = 0;
	mRound = -1;
	mScores.reserve(16);
}

Analyzer::~Analyzer()
{

}

void Analyzer::Init( GridSceneMap* GSMap,int Camp )
{
	mCamp = Camp;
	mGSMap = GSMap;
}

void Analyzer::Free()
{

}

void Analyzer::Analysis(int Round)
{
	
	std::list<AnalyzerUnit*>::iterator it = mAnalyzerUnitList.begin();
	std::list<AnalyzerUnit*>::iterator it_end = mAnalyzerUnitList.end();

	mScores.clear();

	for (;it != it_end;it++)
	{
		mScores.push_back(std::make_pair((*it)->Analysis(),it));
	}


}

void Analyzer::AddUnit( AnalyzerUnit* unit )
{
	mAnalyzerUnitList.push_back(unit);
}

void Analyzer::RemoveUnit( AnalyzerUnit* unit )
{
	mAnalyzerUnitList.remove(unit);
}

void Analyzer::Decision(int Round)
{
	//先分析，每回合只分析一次
	if (mRound != Round)
	{
		Analysis(Round);
	}
	//再决策
	int indexUnit = -1;;

	for (int i = 0;i< mScores.size();++i )
	{
		indexUnit = max(indexUnit,mScores[i].first);
	}

	//
	(*mScores[indexUnit].second)->Decision();
	//

}

