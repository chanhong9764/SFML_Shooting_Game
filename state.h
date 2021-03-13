#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HP {
private:
	float shooter_gauge = 500;
	float dragon_gauge = 800;
	RectangleShape shooter_HP;
	RectangleShape dragon_HP;
	Texture shooterHP_t;
	Texture dragonHP_t;
	Sprite shooterHP_s;
	Sprite dragonHP_s;
	int temp = 0;
public:
	void setTextureImg();
	void setSpirteImg();
	RectangleShape getDragon_HP();
	RectangleShape getShooter_HP();
	void setUnits_HP();
	Sprite getShooterImg();
	Sprite getDragonImg();
	void setImgPosition();
	void decrease_DragonHP();
	void decrease_ShooterHP();
	void incre_HP();
};

class MP {
private:
	float gauge = 500;
	RectangleShape shooter_MP;
	Texture shooterMP_t;
	Sprite shooterMP_s;
public:
	void incre_MP();
	void setTextureImg();
	void setSpriteImg();
	void setShooter_MP();
	void setSpriteImg_MP();
	void decreMP();
	float get_MP();
	Sprite getSpriteImg();
	RectangleShape getShooter_MP();
};
