#ifndef __Sound_Manager_H__
#define __Sound_Manager_H__

#include "cocos2d.h"

class SoundManager
{
private:
	static SoundManager* m_Instance;

	cocos2d::ValueVector m_SelfMusicList;

	std::string m_CurGameMusic;

	SoundManager(void);
public:
	static SoundManager* Instance();

	~SoundManager(void);

	void PlayEffect(std::string name);

	void Play(std::string name);
	//--------------
	void PauseMusic();

	void PauseEffect();

	void PauseSound();
	//--------------
	void ResumeMusic();

	void ResumeEffect();

	void ResumeSound();
	//--------------
	void StopMusic();

	void StopEffect();

	void StopSound();
	//--------------
	void Add(std::string name);

	void RePlay();

	bool checkIsOutSide();

	std::string GetCurMusic();
};

#endif //__Sound_Manager_H__