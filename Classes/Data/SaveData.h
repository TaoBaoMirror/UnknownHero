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

	int IsNewData; //�Ƿ�Ϊһ���µĿյĴ浵�ļ�

	int HeroType; //Ӣ������ ��Ϊ 1��ͨӢ�� Ӣ����ͼ������ƴ�ӳɵ� û��������� 2����Ӣ�� Ӣ����ͼ�ǹ̶��� ���������

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
	int MaxHP;		//���Ѫ��
	int CurHP;		//��ǰѪ��
	int Stamina;	//����ֵ
	int CurSceneID;	//��ǰ����ID
	int CurGrid_X;	//��ǰ��������X
	int CurGrid_Y;	//��ǰ��������Y
	int FaceDir;	//�泯����
	int Coin;		//��ǰ��ɫ���ϵĽ��
	int ItemID_1;	//���Ͽɴ��ĵ���1
	int ItemID_2;	//���Ͽɴ��ĵ���2

	int PassedSceneCount; //�Ѿ��߹��˶��ٳ���
	//--Enemy--
	//1 ��¼��ǰ��ͼ�ĵ��˸���վλ �泯���� ��Ѫ��
	//2 ��¼��ǰ��ͼ�Ѿ��������¼�?(���߼�¼Ϊ�����Ѿ��������¼�)

	//--Village--
	//1 ��¼�����Ѿ����ʹ��Ĵ���,�Լ����ʵĴ���,��ΪҪ����"���ŷ��ʴ�������,�ָ������Ļ�������"�Ĺ���
	//2 ��¼���ǼĴ��ڴ�����ĵ��߽�Ǯ

	//--Died Hero--
	//��¼�Ѿ�������Ӣ�۸���  �Ѿ�����������Ӣ��
	int DeadHeroCount;
	std::string DeadSpecialHero;
};

#endif //__SAVE_DATA_H__