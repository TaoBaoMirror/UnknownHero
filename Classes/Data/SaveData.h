#ifndef __SAVE_DATA_H__
#define __SAVE_DATA_H__

#include <string>

//---------------------------------------------------------
class SaveData
{
public:
	SaveData(void);
	~SaveData(void);

	void WriteSaveFile(std::string filepath);
	void LoadSaveFile(std::string filepath);

public:

	int IsNewData; //是否为一个新的空的存档文件

	int HeroType; //英雄类型 分为 1普通英雄 英雄贴图姓名是拼接成的 没有特殊剧情 2特殊英雄 英雄贴图是固定的 有特殊剧情

	//--Hero--
	//normal hero
	int HeroTexID;
	std::string HeroName;	
	//spec hero
	int SpecialHeroID;
	std::string AlreadyFinishPlot;
	//common
	int HeroOccupation;
	int HeroLevel;
	int SkillID_1;
	int SkillID_2;
	int SkillID_3;
	int MaxHP;		//最大血量
	int CurHP;		//当前血量
	int Stamina;	//体力值
	int CurSceneID;	//当前场景ID
	int CurGrid_X;	//当前格子坐标X
	int CurGrid_Y;	//当前格子坐标Y
	int FaceDir;	//面朝方向
	int Coin;		//当前角色身上的金币
	int ItemID_1;	//身上可带的道具1
	int ItemID_2;	//身上可带的道具2

	int PassedSceneCount; //已经走过了多少场景
	//--Enemy--
	//1 记录当前地图的敌人各自站位 面朝方向 与血量
	//2 记录当前地图已经触发的事件?(或者记录为村子已经触发的事件)

	//--Village--
	//1 纪录主角已经访问过的村子,以及访问的次数,因为要设置"随着访问次数提升,恢复体力的花费提升"的功能
	//2 记录主角寄存在村子里的道具金钱

	//--Died Hero--
	//记录已经死亡的英雄个数  已经死亡的特殊英雄
	int DeadHeroCount;
	std::string DeadSpecialHero;
};

#endif //__SAVE_DATA_H__