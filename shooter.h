#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "dragons.h"
#include "state.h"
#include "item.h"
#include <iostream>

class dragons;
class items;
class bullets;

using namespace sf;
using namespace std;

struct Position
{
	float x;
	float y;
};

class shooter {
private:
	Texture shooter_t;
	Sprite shooter_s;
	int gravity=5;
	bool isJumping=false;
	bool isBottom = true;
	bool direction = true;
	bool check_item = false;
	bool check_item2 = false;
	float shooter_x=0;
	float shooter_y=0;
	int time = 0;
	int check_time = 300;
	int check_time2 = 300;
	float moving_speed = 0;
public:
	void incre_speed();
	void decre_speed();
	void EatItem(item&, bullets&);
	void EatItem(item&);
	void EatItem(item&, HP&);
	void EatItem(item&, MP&);
	void Collision_dragon(dragons, HP&);
	void setTextureImg();
	void setTextureImg_left();
	void setSpriteImg();
	Sprite getSpriteImg();
	void setShooter_x(float);
	void setShooter_y(float);
	float getShooter_x();
	float getShooter_y();
	void setShooter_s();
	void check_Jumping();
	void Jumping();
	void no_bottom(float);
	void no_sky(float);
	void move_left();
	void move_right();
	void L_wall();
	void R_wall(float);
	void setDirection(bool);
	bool getDirection();
};

class bullets {
private:
	int speed_up = 1;
	int time = 0;
	int angle_time1 = 0;
	int angle_time2 = 0;
	int angle = 0;
	int R_count[6] = { -1, -1, -1, -1, -1, -1 };
	int L_count[6] = { -1, -1, -1, -1, -1, -1 };
	Texture bullet_t;
	Texture bullet_t2;
	Sprite bullet_s;
	Sprite bullet_s2;
	vector <Sprite> bullet_list[12];
	vector <Position> bullet_p[12];
	int bullet_speed = 20;
public:
	void set_Item_speed_UP();
	void set_Item_speed_Down();
	void increAngle();
	void decreAngle();
	void setTextureImg1();
	void setSpriteImg1();
	void setTextureImg2();
	void setSpriteImg2();
	vector<Sprite>* getSpriteImg();
	void shoot(shooter, bool);
	void shooting(float, dragons, HP&);
};
