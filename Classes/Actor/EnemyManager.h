#ifndef __ENEMY_MANAGER_H__
#define __ENEMY_MANAGER_H__

class EnemyManager
{
public:	
	static EnemyManager* GetInstance();

	~EnemyManager(void);

	void Init();

	void Update(float dt);

	bool IsAnyBodyHere();//�鿴�Ƿ��е����ڵ�ǰ������

private:
	EnemyManager(void);

	static EnemyManager* m_Instance;
};

#endif //__ENEMY_MANAGER_H__