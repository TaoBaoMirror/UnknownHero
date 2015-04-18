#include "Goal_AttackTarget.h"
#include "AttackSystem.h"
#include "TargetingSystem.h"
#include "Goal_Attack.h"

void Goal_AttackTarget::Activate()
{
	m_iStatus = active;

	//��������ͼ�����¼���ģ�����������������ͼ��������������Щ
	RemoveAllSubgoals();

	//���ȷ����ɫ����һ��Ŀ��~~ 
	if (!m_pOwner->GetTargetingSystem()->isTargetPresent())
	{
		m_iStatus = completed;

		return;
	}

	//�ж��Ƿ���Դ�ĵ�~
	if (m_pOwner->GetTargetingSystem()->isTargetShootable())
	{		
		AddSubgoal(new Goal_Attack(m_pOwner, m_pOwner->GetTargetingSystem()->GetTarget()));		
	}
	//���Ŀ�겻�ڹ�����Χ��,��ȥ׷��
	else
	{
		//AddSubgoal(new Goal_HuntTarget(m_pOwner));
	}
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_AttackTarget::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	ReactivateIfFailed();

	return m_iStatus;
}