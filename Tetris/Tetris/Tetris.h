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
	//主菜单
	void MainMenu();
	//游戏界面
	void GameInterface();
	//显示地图
	void ShowMap();
	//按键
	void Key();
protected:
	
	//嵌入方块
	void Insertion_Map();
	//初始化
	void Initialization();
	//随机方块h
	void Stochastic();
	//变形
	void Deformation_Diamonds();
	//变形方块嵌入地图
	void Deformation_Diamonds_Insertion_Map();
	//寻找方块位置
	int Deformation_Seek();
	//显示级别
	void ShowGrade();
	//左移
	void LeftShift();
	//右移
	void RightShift();
	//移动操作
	bool ShiftControl(int);
	//下降
	void DropDown();
	//方块落地变值
	void Contact();
	//下一关判断及加速
	void NEXT();
	//暂停
	void Pause();
	//指定光标位置
	void gotoy(int x, int y);
	//游戏结束
	void GameOver();
	//复制地图
	void Copy_Map(char M1[][Map_Width],char M2[][Map_Width]);
	//清除一排
	void Eliminate();
private:
	char geta;
	char getb;	
	char Map[Map_Height][Map_Width];
	char Map2[Map_Height][Map_Width];//地图
	char Diamonds[4][4];//方块
	int CustomsPass;//关卡
	int score;//分数
	int Diamonds_Type;//方块的种类
	int Diamonds_Type_Deformation;//方块的种类变形
	bool S_Diamonds;	//判断是否产生随机方块
	int Time;//时间
	int Diamonds_Num;//方块复制进地图的次数
	int Gameobject;//刷新点
	bool Deformation_Bool;//判断是否按键变形
};

