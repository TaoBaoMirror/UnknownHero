#include "SoundManager.h"
#include "ResDef.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager* SoundManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new SoundManager();
	}

	return m_Instance;
}

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
}
//------------------------------------------
void SoundManager::PlayEffect(std::string name)
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(name.c_str());
	}
}

void SoundManager::Play(std::string name)
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		m_CurGameMusic = name;
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name.c_str());
	}
}

void SoundManager::PauseMusic()
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

void SoundManager::PauseEffect()
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
}

void SoundManager::PauseSound()
{
	PauseEffect();
	PauseMusic();
}

void SoundManager::ResumeMusic()
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

void SoundManager::ResumeEffect()
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}

void SoundManager::ResumeSound()
{
	ResumeMusic();
	ResumeEffect();
}

void SoundManager::StopMusic()
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{		
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		m_CurGameMusic = "";
	}
}

void SoundManager::StopEffect()
{
	if (ResDef::getInstance()->ConfigSetting.EnableAudio)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	}
}

void SoundManager::StopSound()
{
	StopMusic();
	StopEffect();
}

void SoundManager::Add(std::string name)
{
	m_SelfMusicList.push_back(cocos2d::Value(name));
}

void SoundManager::RePlay()
{
	if (m_CurGameMusic != "")
	{
		Play(m_CurGameMusic);
	}
}

bool SoundManager::checkIsOutSide()
{
	return false;
}

std::string SoundManager::GetCurMusic()
{
	return m_CurGameMusic;
}