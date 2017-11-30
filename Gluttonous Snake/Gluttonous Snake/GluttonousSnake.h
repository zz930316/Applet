#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

const int MAP_WIDTH = 22;
const int MAP_HEIGHT = 22;

struct Snake
{
	char *s;
	Snake * w;
};




class GluttonousSnake
{
public:
	GluttonousSnake();
	~GluttonousSnake();
	//���˵�
	void MainMenu();
	//��Ϸ����
	void GameInterface();
	//��ʾ��ͼ
	void ShowMap();
	//����
	void control(char);
protected:
	//��ʼ��ͼ
	void Mapin();
	//���ʳ��
	void Food();
	//�ƶ�����
	void Move(char*,int);
	//ɾ��������
	void DeleteSnake();
	//����������
	void NewSnake();
	//�жϷ�����ȷ��
	bool Direction(char,char);
	//��һ���жϼ�����
	void NEXT();
	//��ͣ
	void Pause();
	//��ȡ�䶯���ߺ�ʳ��
	void SnakeFood();
	//ָ�����λ��
	void gotoy(int x, int y);
	//��Ϸ����
	void GameOver();
private:
	//��ͼ
	char Map[MAP_WIDTH][MAP_HEIGHT];
	//�ߵĳ���
	int len;
	//��
	Snake *snake;
	//����
	int score;
	//�ٶȵĳ̶�
	int CustomsPass;
	//�ƶ��ٶ�
	int Speed;
	//�ж�ʳ���Ƿ����
	bool Food1;
};

