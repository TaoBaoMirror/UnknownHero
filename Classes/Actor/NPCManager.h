#ifndef __NPC_MANAGER_H__
#define __NPC_MANAGER_H__

class NPCManager
{
public:
	static NPCManager* GetInstance();
	
	~NPCManager(void);

	void Init();

	void Update(float dt);

	bool IsAnyBodyHere();//�鿴�Ƿ���NPC�ڵ�ǰ������

private:
	NPCManager(void);

	static NPCManager* m_Instance;
};

#endif //__NPC_MANAGER_H__