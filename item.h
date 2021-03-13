#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

class item {
private:
	Texture speed_up_t;
	Sprite speed_up_s;
	Texture Shooter_speed_t;
	Sprite Shooter_speed_s;
	Texture HP_up_t;
	Sprite HP_up_s;
	Texture MP_up_t;
	Sprite MP_up_s;
	int time[4] = { rand() % 900,rand() % 900,rand() % 3600,rand() % 3600 };
	bool disappear[4] = { true, true, true, true };
	bool make[4] = { false,false,false,false };
	float bottom = 0;
	float temp_bottom1[4] = { 0, };
	float temp_bottom2[4] = { 0, };
public:
	void Bottom_f(float);
	bool getDisappear(int);
	void setDisappear(int, bool);
	void setTextureImg();
	void setSpriteImg();
	Sprite* getSpriteImg(int);
	void drop_item(int);
};