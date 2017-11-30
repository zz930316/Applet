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
	//主菜单
	void MainMenu();
	//游戏界面
	void GameInterface();
	//显示地图
	void ShowMap();
	//操作
	void control(char);
protected:
	//初始地图
	void Mapin();
	//随机食物
	void Food();
	//移动身体
	void Move(char*,int);
	//删除蛇链表
	void DeleteSnake();
	//建立蛇链表
	void NewSnake();
	//判断方向正确性
	bool Direction(char,char);
	//下一关判断及加速
	void NEXT();
	//暂停
	void Pause();
	//读取变动的蛇和食物
	void SnakeFood();
	//指定光标位置
	void gotoy(int x, int y);
	//游戏结束
	void GameOver();
private:
	//地图
	char Map[MAP_WIDTH][MAP_HEIGHT];
	//蛇的长度
	int len;
	//蛇
	Snake *snake;
	//分数
	int score;
	//速度的程度
	int CustomsPass;
	//移动速度
	int Speed;
	//判断食物是否存在
	bool Food1;
};

