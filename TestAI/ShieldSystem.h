/********************************************************************
	created:	2015/03/14
	created:	14:3:2015   15:33
	filename: 	E:\cyvasse\TestAI\ShieldSystem.h
	file path:	E:\cyvasse\TestAI
	file base:	ShieldSystem
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ShieldSystem_h__
#define ShieldSystem_h__

#include <iostream>
#include "ShieldData.h"

class Soldier;

class ShieldSystem
{
public:
	ShieldSystem(Soldier* pOwner);
	~ShieldSystem();
	//
	void SetOriginalShieldDataBase(int data_id);
	const ShieldDataBase* GetOriginalShieldDataBase() const ;
	ShieldDataBase*	GetCurShieldDataBase();
	//
	void	Update();
	//
	bool	Load(std::ifstream& is);
	bool	Save(std::ofstream& os);

protected:
	Soldier*			m_pOwner;
	ShieldDataBase		m_CurShieldDataBase;

	int					m_nOriginalShieldDataBaseID;
	ShieldDataBase		m_OriginalShieldDataBase;		//÷ª∂¡ Ù–‘

private:
};

#endif // ShieldSystem_h__
