#ifndef __GAME_ACTION_H__
#define __GAME_ACTION_H__

class GameAction
{
public:
	GameAction(int typeID);
	~GameAction(void);

	virtual void ClickAction();

	virtual void UseAction(int level); //�ϻ���ҡ������һ���� ����2�� 3�� ��������

	bool IsActionDirectly(); //�Ƿ���ֱ����Ч��Action
	void SetActionDirectly(bool bValue){m_bIsDirectly = bValue;}

	void SetWeight(int wei){ m_Weight = wei; }
	int GetWeight(){return m_Weight;}

	int GetTypeID(){return m_ActionTypeID;}

	int GetIconID(){return m_IconID;}
protected:
	int m_Weight;

	int m_ActionTypeID;

	int m_IconID;

	bool m_bIsDirectly;
};

#endif//__GAME_ACTION_H__

