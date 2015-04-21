#ifndef __PLAY_MANAGER_H__
#define __PLAY_MANAGER_H__

#include "Actor/Hero.h"

class PlayerManager
{
public:
	static PlayerManager* GetInstance();
	
	~PlayerManager(void);

	void Init();

	void Update(float dt);

private:
	PlayerManager(void);

	static PlayerManager* m_Instance;

	//--------------------------

	Hero* m_pMainRole;
	
};

#endif //