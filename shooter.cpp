#include "shooter.h"

void shooter::Collision_dragon(dragons dragon, HP& HP_state)										// 드래곤이랑 1초 간격으로 부딪힘
{
	if (shooter_s.getGlobalBounds().intersects(dragon.getDragon_s().getGlobalBounds()))
	{
		if (time == 0)
		{
			HP_state.decrease_ShooterHP();															// 슈터 HP 감소
			time = 60;
		}
		else if (time > 0)
		{
			time--;
		}
		else if (time < 0)
		{
			time = 0;
		}
	}
}

void shooter::setDirection(bool direct)																// 슈터 방향 설정
{
	direction = direct;
}

bool shooter::getDirection()																		// 슈터 방향 반환
{
	return direction;
}

void shooter::setShooter_x(float x)																	// 슈터 X값 설정
{
	this->shooter_x = x;
}

void shooter::setShooter_y(float y)																	// 슈터 Y값 설정
{
	this->shooter_y = y;
}

void shooter::setTextureImg()																		// 슈터 오른쪽 텍스쳐 설정
{
	shooter_t.loadFromFile("shooter_1.png");
}

void shooter::setTextureImg_left()																	// 슈터 왼쪽 텍스쳐 설정
{
	shooter_t.loadFromFile("shooter_2.png");
}

void shooter::setSpriteImg()																		// 슈터 스프라이트 설정
{
	shooter_s.setTexture(shooter_t);
}

Sprite shooter::getSpriteImg()																		// 슈터 스프라이트 반환
{
	return shooter_s;
}

float shooter::getShooter_x()																		// 슈터 X값 반환
{
	return shooter_x;
}

float shooter::getShooter_y()																		// 슈터 Y값 반환
{
	return shooter_y;
}

void shooter::setShooter_s()																		// 슈터 위치 설정
{
	shooter_s.setPosition(shooter_x, shooter_y);
}
void shooter::check_Jumping()																		// 점프 중인지 아닌지 체크
{
	if (isBottom && !isJumping)
	{
		isJumping = true;
		isBottom = false;
	}
}
void shooter::Jumping()																				// 점프
{
	if (isJumping)
	{
		shooter_y -= gravity;
	}
	else
	{
		shooter_y += gravity;
	}
}
void shooter::no_bottom(float temp)																	// 슈터가 바닥 밑으로 가지 않게
{
	if (shooter_y >= temp)
	{
		shooter_y = temp;
		isBottom = true;
	}
}
void shooter::no_sky(float temp)																	// 슈터가 천장으로 가지 않게
{
	if (shooter_y <= temp - 70)
	{
		isJumping = false;
	}
}
void shooter::move_left()																			// 왼쪽으로 무빙
{
	shooter_x -= (float)(10.0 + moving_speed);														// 무빙 스피드 아이템 변수
}
void shooter::move_right()																			// 오른쪽으로 무빙
{
	shooter_x += (float)(10.0 + moving_speed);
}
void shooter::L_wall()																				// 왼쪽 벽 넘지 않게
{
	if (shooter_x <= 0)
		shooter_x = 0;
}
void shooter::R_wall(float WIDTH)																	// 오른쪽 벽 넘지 않게
{
	if (shooter_x >= WIDTH - 150)
		shooter_x = WIDTH - 150;
}

void shooter::incre_speed()																			// 슈터 속도 증가
{
	moving_speed = 5;
}
void shooter::decre_speed()																			// 슈터 속도 감소
{
	moving_speed = 0;
}

void shooter::EatItem(item& items, bullets& bullet)													// 슈터 1번 아이템
{
	if (shooter_s.getGlobalBounds().intersects(items.getSpriteImg(0)->getGlobalBounds()))			// 슈터 1번 아이템 먹었을 경우
	{
		items.setDisappear(0, true);
		check_item = true;
		items.getSpriteImg(0)->setPosition(items.getSpriteImg(0)->getPosition().x, items.getSpriteImg(0)->getPosition().y + 150);
	}
	if (check_time > 0 && check_item == true)														// 5초 동안 아이템 사용 
	{
		check_time--;
	}
	else if (check_time <= 0)
	{
		check_time = 300;
		check_item = false;
	}

	if (check_item)																					// 총알 스피드 속도 설정
	{
		bullet.set_Item_speed_UP();
	}
	else
	{
		bullet.set_Item_speed_Down();
	}
}

void shooter::EatItem(item& items)																	// 슈터 2번 아이템
{
	if (shooter_s.getGlobalBounds().intersects(items.getSpriteImg(1)->getGlobalBounds()))
	{
		items.setDisappear(1, true);
		check_item2 = true;
		items.getSpriteImg(1)->setPosition(items.getSpriteImg(1)->getPosition().x, items.getSpriteImg(1)->getPosition().y + 50);
	}
	if (check_time2 > 0 && check_item2 == true)
	{
		check_time2--;
	}
	else if (check_time2 <= 0)
	{
		check_time2 = 300;
		check_item2 = false;
	}
	if (check_item2)																				// 슈터 움직임 속도 설정
	{
		incre_speed();
	}
	else
	{
		decre_speed();
	}
}

void shooter::EatItem(item& items, HP& HP_state)													// 슈터 3번 아이템
{
	if (shooter_s.getGlobalBounds().intersects(items.getSpriteImg(2)->getGlobalBounds()))
	{
		HP_state.incre_HP();
		items.setDisappear(2, true);
		items.getSpriteImg(2)->setPosition(items.getSpriteImg(2)->getPosition().x, items.getSpriteImg(2)->getPosition().y + 150);
	}
}

void shooter::EatItem(item& items, MP& MP_state)													// 슈터 4번 아이템
{
	if (shooter_s.getGlobalBounds().intersects(items.getSpriteImg(3)->getGlobalBounds()))
	{
		MP_state.incre_MP();
		items.setDisappear(3, true);
		items.getSpriteImg(3)->setPosition(items.getSpriteImg(3)->getPosition().x, items.getSpriteImg(3)->getPosition().y + 150);
	}
}


// 총알

void bullets::set_Item_speed_UP()																	// 아이템 - 총알 속도 증가
{
	speed_up = 3;
}

void bullets::set_Item_speed_Down()
{
	speed_up = 1;
}

vector <Sprite>* bullets::getSpriteImg()														// 각도에 따라 발사된 총알 리스트 반환
{
	return bullet_list;
}



void bullets::increAngle()																				// 각도 증가 0.5초
{
	if (angle_time1 == 0)
	{
		if (angle >= 5)
		{
			angle = 5;
		}
		else
		{
			angle++;
		}
		angle_time1 = 30;
	}
	else if (angle_time1 > 0)
	{
		angle_time1--;
	}
	else if (angle_time1 <= 0)
	{
		angle_time1 = 0;
	}
}

void bullets::decreAngle()																				// 각도 감소 0.5초
{
	if (angle_time2 == 0)
	{
		if (angle <= 0)
		{
			angle = 0;
		}
		else
		{
			angle--;
		}
		angle_time2 = 30;
	}
	else if (angle_time2 > 0)
	{
		angle_time2--;
	}
	else if (angle_time2 < 0)
	{
		angle_time2 = 0;
	}
}


void bullets::setTextureImg1()																			// 오른쪽 총알 텍스쳐 설정
{
	bullet_t.loadFromFile("bullet.png");
}

void bullets::setSpriteImg1()																			// 오른쪽 총알 스프라이트 설정
{
	bullet_s.setTexture(bullet_t);
}

void bullets::setTextureImg2()																			// 왼쪽 총알 텍스쳐 설정
{
	bullet_t2.loadFromFile("bullet2.png");
}

void bullets::setSpriteImg2()																			// 왼쪽 총알 스프라이트 설정
{
	bullet_s2.setTexture(bullet_t2);
}

void bullets::shoot(shooter shoot, bool direction)														// 총알 스프라이트 각도 설정 및 위치 설정 
{
	if (time == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			Sprite temp_s;
			Position temp;
			if (direction)																				// 총알 방향 설정
			{
				R_count[angle]++;																		// 각도마다 인덱스 생성
				temp_s = bullet_s;
				if (angle == 0)																			// 스프라이트 각도 변경
					temp_s.rotate(0);
				else if (angle == 1)
					temp_s.rotate(-15);
				else if (angle == 2)
					temp_s.rotate(-30);
				else if (angle == 3)
					temp_s.rotate(-45);
				else if (angle == 4)
					temp_s.rotate(-60);
				else if (angle == 5)
					temp_s.rotate(-75);

				bullet_list[angle].push_back(temp_s);
				temp.x = shoot.getShooter_x() + 120;
				temp.y = shoot.getShooter_y() + 100;
				bullet_p[angle].push_back(temp);
				bullet_list[angle][R_count[angle]].setPosition(bullet_p[angle][R_count[angle]].x, bullet_p[angle][R_count[angle]].y);
				bullet_list[angle][R_count[angle]].setScale(1.f, 1.f);
			}
			else
			{
				L_count[angle]++;
				temp_s = bullet_s2;
				if (angle == 0)
					temp_s.rotate(0);
				else if (angle == 1)
					temp_s.rotate(15);
				else if (angle == 2)
					temp_s.rotate(30);
				else if (angle == 3)
					temp_s.rotate(45);
				else if (angle == 4)
					temp_s.rotate(60);
				else if (angle == 5)
					temp_s.rotate(75);

				bullet_list[6 + angle].push_back(temp_s);
				temp.x = shoot.getShooter_x() - 40;
				temp.y = shoot.getShooter_y() + 100;
				bullet_p[6 + angle].push_back(temp);
				bullet_list[6 + angle][L_count[angle]].setPosition(bullet_p[6 + angle][L_count[angle]].x, bullet_p[6 + angle][L_count[angle]].y);
				bullet_list[6 + angle][L_count[angle]].setScale(1.f, 1.f);
			}
			time = 30 / speed_up;
		}
	}
	else if (time > 0)
	{
		time--;
	}
	else if (time <= 0)																							// 에러 방지
	{
		time = 0;
	}
}

void bullets::shooting(float WIDTH, dragons dragon, HP& HP_state)
{
	for (int i = 0; i < 12; i++)
	{
		if (bullet_list[i].size() != 0)
		{
			for (auto& e : bullet_list[i])
			{
				switch (i)																								// 각도 마다 다른 좌표 증감
				{
				case 0:
					e.setPosition(e.getPosition().x + bullet_speed, e.getPosition().y); break;
				case 1:
					e.setPosition(e.getPosition().x + bullet_speed, e.getPosition().y - 2); break;
				case 2:
					e.setPosition(e.getPosition().x + bullet_speed - 3, e.getPosition().y - 5); break;
				case 3:
					e.setPosition(e.getPosition().x + bullet_speed - 5, e.getPosition().y - 7); break;
				case 4:
					e.setPosition(e.getPosition().x + bullet_speed - 7, e.getPosition().y - 10); break;
				case 5:
					e.setPosition(e.getPosition().x + bullet_speed - 10, e.getPosition().y - 14); break;
				case 6:
					e.setPosition(e.getPosition().x - bullet_speed, e.getPosition().y); break;
				case 7:
					e.setPosition(e.getPosition().x - bullet_speed, e.getPosition().y - 2); break;
				case 8:
					e.setPosition(e.getPosition().x - bullet_speed + 3, e.getPosition().y - 5); break;
				case 9:
					e.setPosition(e.getPosition().x - bullet_speed + 5, e.getPosition().y - 7); break;
				case 10:
					e.setPosition(e.getPosition().x - bullet_speed + 7, e.getPosition().y - 10); break;
				default:
					e.setPosition(e.getPosition().x - bullet_speed + 10, e.getPosition().y - 14); break;
				}
				if (e.getGlobalBounds().intersects(dragon.getDragon_s().getGlobalBounds()))
				{
					HP_state.decrease_DragonHP();
					for (auto temp = bullet_list[i].begin(); temp < bullet_list[i].end(); temp++)						// 드래곤에 닿은 총알 찾기
					{
						if (bullet_list[i][temp - bullet_list[i].begin()].getPosition().x == e.getPosition().x && bullet_list[i][temp - bullet_list[i].begin()].getPosition().y == e.getPosition().y)
						{
							int temp_i = 0;
							temp_i = temp - bullet_list[i].begin();
							bullet_list[i].erase(temp);
							vector <Position>::iterator temp2;
							temp2 = bullet_p[i].begin() + temp_i;
							bullet_p[i].erase(temp2);
							if (i >= 0 && i <= 5)
								R_count[i]--;
							else
								L_count[i - 6]--;
							break;
						}
					}
				}
				else
				{
					if (e.getPosition().x > WIDTH - 100 || e.getPosition().x < 0)										// 총알이 벽에 닿으면 제거 
					{
						for (auto temp = bullet_list[i].begin(); temp < bullet_list[i].end(); temp++)					// 닿은 총알 찾기
						{
							if (bullet_list[i][temp - bullet_list[i].begin()].getPosition().x == e.getPosition().x && bullet_list[i][temp - bullet_list[i].begin()].getPosition().y == e.getPosition().y)
							{
								int temp_i = 0;
								temp_i = temp - bullet_list[i].begin();
								bullet_list[i].erase(temp);
								vector <Position>::iterator temp2;
								temp2 = bullet_p[i].begin() + temp_i;
								bullet_p[i].erase(temp2);
								if (i >= 0 && i <= 5)
									R_count[i]--;
								else
									L_count[i - 6]--;
								break;
							}
						}
					}
					if (e.getPosition().y < 0)																			// 총알 천장에 닿으면 제거
					{
						for (auto temp = bullet_list[i].begin(); temp < bullet_list[i].end(); temp++)					// 닿은 총알 찾기
						{
							if (bullet_list[i][temp - bullet_list[i].begin()].getPosition().x == e.getPosition().x && bullet_list[i][temp - bullet_list[i].begin()].getPosition().y == e.getPosition().y)
							{
								int temp_i = 0;
								temp_i = temp - bullet_list[i].begin();
								bullet_list[i].erase(temp);
								vector <Position>::iterator temp2;
								temp2 = bullet_p[i].begin() + temp_i;
								bullet_p[i].erase(temp2);
								if (i >= 0 && i <= 5)
									R_count[i]--;
								else
									L_count[i - 6]--;
								break;
							}
						}
					}
				}
			}
		}
	}
}