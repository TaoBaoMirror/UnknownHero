#ifndef __RESOURCE_DEF_H__
#define __RESOURCE_DEF_H__

#include "cocos2d.h"
#include <string>
#include "Common\CommonMethod.h"

class ConfigFileStruct
{
public:
	bool NeedPlayHelp;
	bool EnableAudio;
	int	 CurrentMoney;
	bool RatedMe;
	bool Payment;
	bool FinishedEgyptStory;

	int CurrentArea;
	int CurrentLevel;
	int MaxShowLevel;
	

	std::vector<int> CanUsedRoleIDs;
	//
	ConfigFileStruct();
	//
	void RefreshData()
	{
		Payment = true;
	}
	//
	void SaveToFile(std::string fileName);
	//
	bool LoadFromFile(std::string fileName);
};

class ResDef
{
public:
	static const std::string g_GameResPListFile;
	static const std::string g_GameResTextureFile;
	//
	static const std::string g_GameResGUIPListFile;
	static const std::string g_GameResGUITextureFile;

	static const std::string g_StandByHeroPListFile;
	static const std::string g_StandByHeroTextureFile;

	static const std::string g_HeroResPlistFile;
	static const std::string g_HeroResTextureFile;

	static const std::string g_BossPlistFile;
	static const std::string g_BossTextureFile;

	static const std::string g_GameEffectPListFile;
	static const std::string g_GameEffectTextureFile;

	static const std::string g_GameParticlePListFile;
	static const std::string g_GameParticleTextureFile;

	static const std::string g_GameMiscPListFile;
	static const std::string g_GameMiscTextureFile;
	//
	static const std::string g_BlankTextureFile;

	//Map
	static const std::string g_WorldMapNameBase;

	//Help
	static const std::string g_HelpUIImage;

	//Node
	cocos2d::Node* g_GUIBatchNode;
	cocos2d::Node* g_GameBatchNode;

	//music
	static const std::string g_JumpSound;
	static const std::string g_EleSound;
	static const std::string g_FallSound;
	static const std::string g_SpeedUpSound;
	static const std::string g_PutTrap;
	static const std::string g_Hurray;
	static const std::string g_CounterSound;
	static const std::string g_SelectSound;
	static const std::string g_BrokenSound;
	static const std::string g_InvalidSound;
	static const std::string g_PowerUpSound;
	static const std::string g_PowerDownSound;
	static const std::string g_ChangeRoleSound;
	static const std::string g_ChangeModeSound;

	static const std::string g_OpeningMusic;
	static const std::string g_BackgroundMusic;
	static const std::string g_SelectRoleMusic;
	static const std::string g_SceneMapMusic;
	static const std::string g_BossFightMusic;
	//
	static bool FinishedLoadRes;
	//
	static const std::string g_ConfigFileName;
	ConfigFileStruct g_ConfigStruct;

	static const std::string g_SaveDataFileName_1;
	static const std::string g_SaveDataFileName_2;
	static const std::string g_SaveDataFileName_3;
	//
	static const std::string g_ParticleEffect;
	static const std::string g_ParticleEffectExplode;
	static const std::string g_ParticleEffectLavaFlow;

	//-----------------------------------------------------------
	int ScreenWidth;
	int ScreenHeight;

	int BaseGameWidth;
	int BaseGameHeight;

	float ScreenWidthRatio;
	float ScreenHeightRatio;
	//-----------------------------------------------------------
	ConfigFileStruct ConfigSetting;
private:
	static ResDef* m_Instance;
public:
	static ResDef* getInstance();

	ResDef(void);
	~ResDef(void);

	void SaveConfig();
	void ReadConfig();

	void ReadSaveData();

	void ReadTables();

	void loadRes();

	void initRes(ProgressCount* progresscount);

	void LoadBaseUITextures();

	void UnlockRoleID(int id);
	bool IsRoleLocked(int id);

private:
	void loadTextures();

	void loadingTexturesCallBack(cocos2d::Texture2D *texture);
};

#endif //__RESOURCE_DEF_H__
