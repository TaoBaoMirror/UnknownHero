#ifndef __GAME_ACTION_H__
#define __GAME_ACTION_H__

class GameAction
{
public:
	GameAction(int typeID);
	~GameAction(void);

	virtual void ClickAction();

	virtual void UseAction(int level); //老虎机摇出两个一样的 就是2级 3个 就是三级

	int GetWeight(){return m_Weight;}

	int GetTypeID(){return m_TypeID;}

	int GetIconID(){return m_IconID;}


protected:
	int m_Weight;

	int m_TypeID;

	int m_IconID;
};

#endif//__GAME_ACTION_H__

