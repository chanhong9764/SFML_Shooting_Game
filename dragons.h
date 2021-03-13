#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include "shooter.h"
#include "state.h"

class shooter;

using namespace sf;
using namespace std;

struct Position_
{
	float x;
	float y;
};

class dragons {
private:
	Texture dragon_t;
	Texture fireball_t;
	Texture fireball_t2;
	Sprite dragon_s;
	Sprite fireball_s;
	Sprite fireball_s2;
	vector <Position_> fireball_p[2];
	vector <Sprite> fireball_list[2];
	Position_ dragon_p;
	bool fly = true;
	bool direction = true;
	int time = 0;
	int time_attack = 0;
	int L_count = -1;
	int R_count = -1;
	int skill_1 = 0;
	int skill_2 = 0;
	int skill_time = 0;
	int skill_time2 = 0;
public:
	void dragon_skill_1(MP&);
	void dragon_skill_2(MP&);
	void setTextureImg();
	void setSpriteImg();
	void setDragon_s();
	void setFireball_s(float, float);
	void setDragon_x(float);
	void setDragon_y(float);
	Sprite getDragon_s();
	Sprite getFireball_s();
	void dragon_fly(float, float);
	void dragon_attack();
	void fire_shooting(float, shooter, HP&, float);
	vector <Sprite>* getSpriteImg();
	void setTextureImg_Right();
};