#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

#define Map_Height 20
#define Map_Width 13


class Tetris
{
public:
	Tetris();
	~Tetris();
	//���˵�
	void MainMenu();
	//��Ϸ����
	void GameInterface();
	//��ʾ��ͼ
	void ShowMap();
	//����
	void Key();
protected:
	
	//Ƕ�뷽��
	void Insertion_Map();
	//��ʼ��
	void Initialization();
	//�������h
	void Stochastic();
	//����
	void Deformation_Diamonds();
	//���η���Ƕ���ͼ
	void Deformation_Diamonds_Insertion_Map();
	//Ѱ�ҷ���λ��
	int Deformation_Seek();
	//��ʾ����
	void ShowGrade();
	//����
	void LeftShift();
	//����
	void RightShift();
	//�ƶ�����
	bool ShiftControl(int);
	//�½�
	void DropDown();
	//������ر�ֵ
	void Contact();
	//��һ���жϼ�����
	void NEXT();
	//��ͣ
	void Pause();
	//ָ�����λ��
	void gotoy(int x, int y);
	//��Ϸ����
	void GameOver();
	//���Ƶ�ͼ
	void Copy_Map(char M1[][Map_Width],char M2[][Map_Width]);
	//���һ��
	void Eliminate();
private:
	char geta;
	char getb;	
	char Map[Map_Height][Map_Width];
	char Map2[Map_Height][Map_Width];//��ͼ
	char Diamonds[4][4];//����
	int CustomsPass;//�ؿ�
	int score;//����
	int Diamonds_Type;//���������
	int Diamonds_Type_Deformation;//������������
	bool S_Diamonds;	//�ж��Ƿ�����������
	int Time;//ʱ��
	int Diamonds_Num;//���鸴�ƽ���ͼ�Ĵ���
	int Gameobject;//ˢ�µ�
	bool Deformation_Bool;//�ж��Ƿ񰴼�����
};

