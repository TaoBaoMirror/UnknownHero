#include "ResDef.h"

//#include "Player/PlayerManager.h"
#include "Scene/GameManager.h"
#include "Data/TableManager.h"

using namespace std;
USING_NS_CC;

ConfigFileStruct::ConfigFileStruct()
{
	NeedPlayHelp = true;
	EnableAudio = true;
	CurrentMoney = 8888;
	RatedMe = false;
	Payment = false;
	FinishedEgyptStory = false;

	CurrentArea = 1;
	CurrentLevel = 1;
	MaxShowLevel = 1;
	CanUsedRoleIDs.clear();
	//CanUsedRoleIDs.push_back((int)GameRoleType::GameRoleType_ARSEHOLE);
	//CanUsedRoleIDs.push_back((int)GameRoleType::GameRoleType_PHARAOH);

	//
	RefreshData();
}

//-------------------------------------------------------------------------------
void ConfigFileStruct::SaveToFile(std::string fileName)
{
	auto root = Dictionary::create();
	//auto str = String::create("GameSaveData");
	//root->setObject(str, "SaveData");
	//auto array = Array::create();
	auto dictInArray = Dictionary::create();	

	auto booNeedPlayHelpObject = Bool::create(NeedPlayHelp);
	dictInArray->setObject(booNeedPlayHelpObject, "NeedPlayHelp");

	auto booEnableAudioObject = Bool::create(EnableAudio);
	dictInArray->setObject(booEnableAudioObject, "EnableAudio");

	//-----------------
	auto intCurrentMoney = Integer::create(CurrentMoney);
	dictInArray->setObject(intCurrentMoney, "CurrentMoney");

	auto intCurrentArea = Integer::create(CurrentArea);
	dictInArray->setObject(intCurrentArea, "CurrentArea");

	auto intCurrentLevel = Integer::create(CurrentLevel);
	dictInArray->setObject(intCurrentLevel, "CurrentLevel");

	auto intMaxShowLevel = Integer::create(MaxShowLevel);
	dictInArray->setObject(intMaxShowLevel, "MaxShowLevel");
	
	//------------------
	auto booRatedMeObject = Bool::create(RatedMe);
	dictInArray->setObject(booRatedMeObject, "RatedMe");

	auto booPaymentObject = Bool::create(Payment);
	dictInArray->setObject(booPaymentObject, "Payment");

	auto booFinEgyptObject = Bool::create(FinishedEgyptStory);
	dictInArray->setObject(booFinEgyptObject, "FinishedEgyptStory");
	//------------------
	std::string unlockRoleList = "";
	for (int i=0; i<CanUsedRoleIDs.size(); ++i)
	{
		std::stringstream ss;
		ss<<CanUsedRoleIDs[i]; 
		std::string indexStr = ss.str();
		if (unlockRoleList != "")
		{
			unlockRoleList = unlockRoleList + "," + indexStr;
		}
		else
		{
			unlockRoleList = indexStr;
		}

	}
	auto strUnlockRoleList = String::create(unlockRoleList);
	dictInArray->setObject(strUnlockRoleList, "UnlockRoleList");
	//------------------

	root->setObject(dictInArray, "SaveData");

	std::string writablePath = FileUtils::getInstance()->getWritablePath();
	//std::string fullPath = writablePath + "savedata.plist";
	std::string fullPath = writablePath + fileName;

	if(root->writeToFile(fullPath.c_str()))
		log("see the plist file at %s", fullPath.c_str());
	else
		log("write plist file failed");
}
//
bool ConfigFileStruct::LoadFromFile(std::string fileName)
{
	std::string writablePath = FileUtils::getInstance()->getWritablePath();
	//std::string fullPath = writablePath + "savedata.plist";
	std::string fullPath = writablePath + fileName;

	if (FileUtils::getInstance()->isFileExist(fullPath) == false)
	{
		return false;
	}

	auto loadDict = __Dictionary::createWithContentsOfFile(fullPath.c_str());
	auto loadDictInDict = (__Dictionary*)loadDict->objectForKey("SaveData");

	auto autoNeedPlayHelp = (__String*)loadDictInDict->objectForKey("NeedPlayHelp");
	NeedPlayHelp = autoNeedPlayHelp->boolValue();

	auto autoEnableAudio = (__String*)loadDictInDict->objectForKey("EnableAudio");
	EnableAudio = autoEnableAudio->boolValue();

	//-----------------------------------------
	__String* autoCurrentMoney = (__String*)loadDictInDict->objectForKey("CurrentMoney");
	CurrentMoney = autoCurrentMoney->intValue();

	__String* autoCurrentArea = (__String*)loadDictInDict->objectForKey("CurrentArea");
	CurrentArea = autoCurrentArea->intValue();

	__String* autoCurrentLevel = (__String*)loadDictInDict->objectForKey("CurrentLevel");
	CurrentLevel = autoCurrentLevel->intValue();

	__String* autoMaxShowLevel = (__String*)loadDictInDict->objectForKey("MaxShowLevel");
	MaxShowLevel = autoMaxShowLevel->intValue();
	//-----------------------------------------

	auto autoRatedMe = (__String*)loadDictInDict->objectForKey("RatedMe");
	RatedMe = autoRatedMe;

	auto autoPayment = (__String*)loadDictInDict->objectForKey("Payment");
	Payment = autoPayment;

	auto autoFinEgyptStory = (__String*)loadDictInDict->objectForKey("FinishedEgyptStory");
	FinishedEgyptStory = autoFinEgyptStory;
	//-----------------------------------------
	auto autoUnlockRoleList = (__String*)loadDictInDict->objectForKey("UnlockRoleList");
	std::string strUnlocklist = autoUnlockRoleList->getCString();

	std::vector<std::string> partStrs = ProgressCount::split(strUnlocklist,",");

	for (int i=0; i<partStrs.size(); ++i)
	{
		int roleIndex = atoi(partStrs[i].c_str());
		CanUsedRoleIDs.push_back(roleIndex);
	}

	return true;
}
//-------------------------------------------------------------------------------
ResDef* ResDef::m_Instance = NULL;

//constans
const string ResDef::g_GameResPListFile = "plist//GameRes.plist";
const string ResDef::g_GameResTextureFile = "plist//GameRes.png";
//
const string ResDef::g_GameResGUIPListFile = "plist//GUI.plist";
const string ResDef::g_GameResGUITextureFile = "plist//GUI.png";

const string ResDef::g_StandByHeroPListFile = "plist//StandByHero.plist";
const string ResDef::g_StandByHeroTextureFile = "plist//StandByHero.png";

const string ResDef::g_HeroResPlistFile = "plist//HeroRes.plist";
const string ResDef::g_HeroResTextureFile = "plist//HeroRes.png";

const std::string ResDef::g_GameEffectPListFile = "plist//Effect.plist";
const std::string ResDef::g_GameEffectTextureFile = "plist//Effect.png";

const std::string ResDef::g_GameParticlePListFile = "plist//Particle.plist";
const std::string ResDef::g_GameParticleTextureFile = "plist//images//Particle.png";

const std::string ResDef::g_GameMiscPListFile = "plist//GameMisc.plist";
const std::string ResDef::g_GameMiscTextureFile = "plist//GameMisc.png";
//
const std::string ResDef::g_BlankTextureFile = "images//blank.png";

const std::string ResDef::g_WorldMapNameBase = "images//map_";

const std::string ResDef::g_HelpUIImage = "images//help_";
//music
const string ResDef::g_JumpSound = "music/JumpSound";
const string ResDef::g_EleSound = "music/EleSound";
const string ResDef::g_FallSound = "music/FallSound";
const string ResDef::g_SpeedUpSound = "music/SpeedUpSound";
const string ResDef::g_PutTrap = "music/PutTrap";
const string ResDef::g_Hurray = "music/Hurray";
const string ResDef::g_CounterSound = "music/Counter";
const string ResDef::g_SelectSound = "music/SelectSound";
const string ResDef::g_BrokenSound = "music/BrokenSound";
const string ResDef::g_InvalidSound = "music/InvalidSound";
const string ResDef::g_PowerUpSound = "music/PowerUp";
const string ResDef::g_PowerDownSound = "music/PowerDown";
const string ResDef::g_ChangeRoleSound = "music/ChangeRole";
const string ResDef::g_ChangeModeSound = "music/ChangeMode";

const string ResDef::g_OpeningMusic = "music/OpeningMusic";
const string ResDef::g_BackgroundMusic = "music/BackMusic";
const string ResDef::g_SelectRoleMusic = "music/SelectRoleMusic";
const string ResDef::g_SceneMapMusic = "music/SceneMap";
const string ResDef::g_BossFightMusic = "music/BossFight";
//
bool ResDef::FinishedLoadRes = false;
//
const string ResDef::g_ConfigFileName = "configdata.plist";
const string ResDef::g_SaveDataFileName_1 = "savedata1.plist";
const string ResDef::g_SaveDataFileName_2 = "savedata2.plist";
const string ResDef::g_SaveDataFileName_3 = "savedata3.plist";
//const ConfigFileStruct g_ConfigStruct = new ConfigFileStruct();
//
const string ResDef::g_ParticleEffect = "Images/SpookyPeasPlist";
const string ResDef::g_ParticleEffectExplode = "Images/ExplodingRing";
const string ResDef::g_ParticleEffectLavaFlow = "Images/LavaFlow";


ResDef::ResDef(void)
{
	ScreenWidth = 800;
	ScreenHeight = 480;

	BaseGameWidth = 800;
	BaseGameHeight = 480;

	ScreenWidthRatio = (float)ScreenWidth/(float)BaseGameWidth;
	ScreenHeightRatio = (float)ScreenHeight/(float)BaseGameHeight;
}


ResDef::~ResDef(void)
{
}

ResDef* ResDef::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new ResDef();
	}

	return m_Instance;
}

void ResDef::LoadBaseUITextures()
{
	//Director::getInstance()->getTextureCache()->addImageAsync("images/BunkerBG.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("images/BunkerUI.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("images\\LoadingBarFrame.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("images\\LesStep.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
}

void ResDef::loadRes()
{	
	loadTextures();
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_GameResGUIPListFile);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_GameResPListFile);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_StandByHeroPListFile);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_HeroResPlistFile);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_GameMiscPListFile);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ResDef::g_GameEffectPListFile);

}

void  ResDef::initRes(ProgressCount* progresscount)
{
    if (FinishedLoadRes == false)
    {		
		progresscount->setCount(20);

        progresscount->setCount(30);
#ifdef WP8
		xtime xt;
		xt.sec = 100;
		_Thrd_sleep(&xt);
		//Sleep(100);
#else
		Sleep(100);
#endif // WP8

        
        progresscount->setCount(40);
#ifdef WP8
		xt.sec = 100;
		_Thrd_sleep(&xt);
		//Sleep(100);
#else
		Sleep(100);
#endif // WP8
        progresscount->setCount(50);
        {
            ReadConfig();
			ReadSaveData();

			//table
			ReadTables();
        }

        progresscount->setCount(60);
#ifdef WP8
		xt.sec = 100;
		_Thrd_sleep(&xt);
		//Sleep(100);
#else
		Sleep(100);
#endif // WP8
        progresscount->setCount(70);
#ifdef WP8
		xt.sec = 100;
		_Thrd_sleep(&xt);
		//Sleep(100);
#else
		Sleep(100);
#endif // WP8

		g_GameBatchNode = cocos2d::SpriteBatchNode::create(g_GameResTextureFile);

        progresscount->setCount(80);
        //MusicManager.Instance().Add(g_OpeningMusic);
        //MusicManager.Instance().Add(g_BackgroundMusic);
        //MusicManager.Instance().Add(g_SelectRoleMusic);
        //MusicManager.Instance().Add(g_SceneMapMusic);
        //MusicManager.Instance().Add(g_BossFightMusic);
        //Sleep(100);
        //
        g_GUIBatchNode = cocos2d::SpriteBatchNode::create(g_GameResGUITextureFile);
        progresscount->setCount(90);
        //Sleep(100);
    }
    //
    progresscount->setCount(100);
    FinishedLoadRes = true;

}

void ResDef::loadingTexturesCallBack(cocos2d::Texture2D *texture)
{
	//++_numberOfLoadedSprites;
    //char tmp[10];
    //sprintf(tmp,"%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
}

void ResDef::loadTextures()
{
	//Director::getInstance()->getTextureCache()->addImageAsync(g_BlankTextureFile, CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("plist//images//GameRes.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("plist//images//GUI.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));

	//Director::getInstance()->getTextureCache()->addImage("plist//images//GameRes.png");
	//Director::getInstance()->getTextureCache()->addImage("plist//images//GUI.png");
	//Director::getInstance()->getTextureCache()->addImageAsync("Images/HelloWorld.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("Images/HelloWorld.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("Images/HelloWorld.png", CC_CALLBACK_1(ResDef::loadingTexturesCallBack, this));
}

void ResDef::SaveConfig()
{
    ConfigSetting.SaveToFile(g_ConfigFileName);
}
//
void ResDef::ReadConfig()
{
	if (!ConfigSetting.LoadFromFile(g_ConfigFileName))
	{
		SaveConfig();
	}
}

void ResDef::ReadSaveData()
{
	GameManager::GetInstance()->LoadGameData();
}

void ResDef::ReadTables()
{
	TableManager::GetInstance()->LoadAllTable();
}

void ResDef::UnlockRoleID(int id)
{
	bool shouldAdd = true;
	for (int i=0; i<ResDef::getInstance()->g_ConfigStruct.CanUsedRoleIDs.size(); ++i)
	{
		int oldID = ResDef::getInstance()->g_ConfigStruct.CanUsedRoleIDs[i];
		if (oldID == id)
		{
			shouldAdd = false;
			break;
		}
	}
	//
	if (shouldAdd)
	{
		ResDef::getInstance()->g_ConfigStruct.CanUsedRoleIDs.push_back(id);
	}
}

bool ResDef::IsRoleLocked(int id)
{
	for (int i=0; i<ResDef::getInstance()->g_ConfigStruct.CanUsedRoleIDs.size(); ++i)
	{
		int origID = ResDef::getInstance()->g_ConfigStruct.CanUsedRoleIDs[i];
		if (origID == id)
		{
			return false;
		}
	}
	//
	return true;
}