#include "dragons.h"

vector <Sprite>* dragons::getSpriteImg()									// 발사된 불덩이 넘겨주는 함수
{
	return fireball_list;
}

void dragons::setTextureImg()												// 텍스쳐 설정
{
	dragon_t.loadFromFile("dragon.png");
	fireball_t.loadFromFile("fireball.png");
	fireball_t2.loadFromFile("fireball2.png");
}

void dragons::setTextureImg_Right()											// 드래곤 오른쪽 텍스쳐 설정
{
	dragon_t.loadFromFile("dragon2.png");
}

void dragons::setSpriteImg()												// 스프라이트 설정
{
	dragon_s.setTexture(dragon_t);
	fireball_s.setTexture(fireball_t);
	fireball_s2.setTexture(fireball_t2);
}

void dragons::setDragon_s()													// 드래곤 위치 설정
{
	dragon_s.setPosition(dragon_p.x, dragon_p.y);
}

void dragons::setDragon_x(float x)											// 드래곤 X 값 변경 함수
{
	this->dragon_p.x = x;
}

void dragons::setDragon_y(float y)											// 드래곤 Y 값 변경 함수
{
	this->dragon_p.y = y;
}

void dragons::setFireball_s(float x, float y)								// 불덩이 X, Y 값 변경 함수
{
	fireball_s.setPosition(x, y);
}

void dragons::dragon_skill_1(MP &MP_state)									// 슈터 S 스킬 함수
{
	if (Keyboard::isKeyPressed(Keyboard::S) && skill_time == 0 && MP_state.get_MP() > 0)
	{
		skill_1 = 5;														// 불덩이 속도 변수
		skill_time = 600;													// 10초
		MP_state.decreMP();													// 마나 감소
	}
	else if (skill_time > 0)
	{
		skill_time--;
	}
	else if (skill_time <= 0)
	{
		skill_1 = 0;
		skill_time = 0;
	}
}

void dragons::dragon_skill_2(MP& MP_state)									// 슈터 D 스킬 함수
{
	if (Keyboard::isKeyPressed(Keyboard::D) && skill_time2 == 0 && MP_state.get_MP() > 0)
	{
		MP_state.decreMP();													// 마나 감소
		skill_2 = 5;														// 드래곤 속도 변수
		skill_time2 = 600;													// 10초
	}
	else if (skill_time2 > 0)
	{
		skill_time2--;
	}
	else if (skill_time2 <= 0)
	{
		skill_2 = 0;
		skill_time2 = 0;
	}
}

void dragons::dragon_attack()												// 불덩이 설정
{
	if (time_attack == 0)													// 랜덤 시간 120초 안에 설정			
	{
		int count_temp;
		Position_ temp;
		if (direction)														// 왼쪽 오른쪽 구분
		{
			R_count++;
			fireball_list[direction].push_back(fireball_s2);
			temp.x = dragon_p.x + 550;
			temp.y = dragon_p.y + 250;
			count_temp = R_count;
		}
		else
		{
			L_count++;
			fireball_list[direction].push_back(fireball_s);
			temp.x = dragon_p.x - 130;
			temp.y = dragon_p.y + 250;
			count_temp = L_count;
		}
		fireball_p[direction].push_back(temp);
		fireball_list[direction][count_temp].setPosition(fireball_p[direction][count_temp].x, fireball_p[direction][count_temp].y);
		time_attack = rand() % 120;

	}
	else if (time_attack > 0)
	{
		time_attack--;
	}
	else if (time_attack < 0)
	{
		time_attack = 0;
	}
}

void dragons::fire_shooting(float WIDTH, shooter shoot, HP &HP_state, float shooter_bottom)								// 불덩이 움직이는 함수
{
	for (int i = 0; i < 2; i++)																	
	{
		if (fireball_list[i].size() != 0)
		{
			for (auto& e : fireball_list[i])
			{
				if (i == 0)
					e.setPosition(e.getPosition().x - 5, e.getPosition().y + (10 - skill_1));							// 왼쪽
				else
					e.setPosition(e.getPosition().x + 5, e.getPosition().y + (10 - skill_1));							// 오른쪽

				if (e.getGlobalBounds().intersects(shoot.getSpriteImg().getGlobalBounds()))								// 불덩이가 슈터에 충돌
				{
					HP_state.decrease_ShooterHP();																		// HP 감소
					for (auto temp = fireball_list[i].begin(); temp < fireball_list[i].end(); temp++)
					{
						if (fireball_list[i][temp - fireball_list[i].begin()].getPosition().x == e.getPosition().x && fireball_list[i][temp - fireball_list[i].begin()].getPosition().y == e.getPosition().y)
						{
							int temp_i = 0;
							temp_i = temp - fireball_list[i].begin();
							fireball_list[i].erase(temp);
							vector <Position_>::iterator temp2;
							temp2 = fireball_p[i].begin() + temp_i;
							fireball_p[i].erase(temp2);
							if (i == 0)
								L_count--;
							else
								R_count--;
							break;
						}
					}
				}
				else
				{
					if (e.getPosition().y >= shooter_bottom)																	// 바닥에 꽂힌 불덩이
					{
						for (auto temp = fireball_list[i].begin(); temp < fireball_list[i].end(); temp++)						// 닿은 불덩이 찾아서 삭제
						{
							if (fireball_list[i][temp - fireball_list[i].begin()].getPosition().x == e.getPosition().x && fireball_list[i][temp - fireball_list[i].begin()].getPosition().y == e.getPosition().y)
							{
								int temp_i = 0;
								temp_i = temp - fireball_list[i].begin();
								fireball_list[i].erase(temp);
								vector <Position_>::iterator temp2;
								temp2 = fireball_p[i].begin() + temp_i;
								fireball_p[i].erase(temp2);
								if (i == 0)
									L_count--;
								else
									R_count--;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void dragons::dragon_fly(float WIDTH, float dragon_bottom)								// 드래곤 날기
{
	if (time == 0)																		// 랜덤 시간으로 오른쪽 왼쪽 방향 설정
	{
		fly = rand() % 2;																// 1 왼쪽 0 오른쪽
		time = ((rand() % 180) + 1);
	}
	else if (time > 0)
	{
		time--;
	}
	else if (time < 0)
	{
		time = 0;
	}
	if (fly)																			// 드래곤 방향 설정 및 날기
	{
		direction = true;																// 불덩이 뿜을 때 사용 , 오른쪽
		dragon_t.loadFromFile("dragon2.png");
		dragon_s.setTexture(dragon_t);
		this->dragon_p.x += (rand() % 15 + 5 - skill_2);								// 날기
		this->dragon_p.y += rand() % 5;
	}
	else
	{
		direction = false;																// 왼쪽
		dragon_t.loadFromFile("dragon.png");
		dragon_s.setTexture(dragon_t);
		this->dragon_p.x -= (rand() % 15 + 5 - skill_2);
		this->dragon_p.y -= rand() % 8;
	}
	if (this->dragon_p.x <= 0)															// 왼쪽 벽에 닿을 시 방향 전환 및 왼쪽으로 못 나가게
	{
		time = 0;
		dragon_p.x = 0;
	}
	else if (this->dragon_p.x >= WIDTH - 670)											// 오른쪽 벽에 닿을 시 방향 전환 및 오른쪽으로 못 나가게
	{
		time = 0;
		dragon_p.x = WIDTH - 670;
	}
	if (this->dragon_p.y >= dragon_bottom)												// 바닥에 닿을 시 방향 전환 및 밑으로 못 가게
	{
		time = 0;
		dragon_p.y = dragon_bottom;
	}
	else if (this->dragon_p.y <= 0)														// 천장에 닿을 시 방향 전환 및 위로 못 가게
	{
		dragon_p.y = 0;
	}
}

Sprite dragons::getDragon_s()															// 드래곤 스프라이트 반환
{
	return dragon_s;
}

Sprite dragons::getFireball_s()															// 불덩이 스프라이트 반환
{
	return fireball_s;
}