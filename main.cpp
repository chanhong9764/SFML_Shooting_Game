#pragma once
#include <SFML/Graphics.hpp>
#include "shooter.h"
#include "dragons.h"
#include "state.h"
#include "item.h"

#define WIDTH 1920
#define HEIGHT 1080

using namespace std;
using namespace sf;


int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "LOC");									// 윈도우 크기 설정
	window.setFramerateLimit(60);															// 프레임 60으로 설정

	const float shooter_bottom = HEIGHT - 360;												// 맵 바닥
	const float dragon_bottom = HEIGHT - 530;												// 맵 바닥

	srand((unsigned int)time(NULL));														

	// 클래스 변수 생성
	shooter shoot;
	bullets bullet;
	dragons dragon;
	HP HP_state;
	MP MP_state;
	item items;
	
	// 배경 텍스쳐, 스프라이트 설정
	Texture background;
	Texture solid;
	Sprite background_s;
	Sprite solid_s;

	// 이미지 불러오기
	background.loadFromFile("background.png");
	solid.loadFromFile("solid.png");
	shoot.setTextureImg();
	bullet.setTextureImg1();
	bullet.setTextureImg2();
	dragon.setTextureImg();
	HP_state.setTextureImg();
	MP_state.setTextureImg();
	items.setTextureImg();

	// 스프라이트에 이미지 적용
	background_s.setTexture(background);
	solid_s.setTexture(solid);
	shoot.setSpriteImg();
	bullet.setSpriteImg1();
	bullet.setSpriteImg2();
	dragon.setSpriteImg();
	HP_state.setSpirteImg();
	MP_state.setSpriteImg();
	items.setSpriteImg();

	// 이미지 위치 설정
	solid_s.setPosition(0, HEIGHT - 200);
	shoot.setShooter_x(50);
	shoot.setShooter_y(shooter_bottom);
	shoot.setShooter_s();
	dragon.setDragon_x(1200);
	dragon.setDragon_y(dragon_bottom);
	dragon.setDragon_s();
	HP_state.setImgPosition();
	MP_state.setSpriteImg_MP();

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		
		// 슈터 & 총알 설정
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			shoot.check_Jumping();										// 점프 체크 함수 (점프 중인가 아닌가)
		}
		shoot.Jumping();												// 점프
		shoot.no_bottom(shooter_bottom);								// 슈터가 바닥 밑으로 가지 않게 하는 함수
		shoot.no_sky(shooter_bottom);									// 슈터가 하늘 위로 날아가지 않게 하는 함수

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			shoot.setTextureImg_left();									// 슈터 왼쪽 이미지로 변경
			shoot.move_left();											// 슈터 이동
			shoot.setDirection(false);									// 총알 방향 설정
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			shoot.setTextureImg();										// 슈터 오른쪽 이미지로 변경
			shoot.move_right();											// 슈터 이동
			shoot.setDirection(true);									// 총알 방향 설정
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			bullet.increAngle();										// 총알 각도 증가
		}
		if(Keyboard::isKeyPressed(Keyboard::Down))
		{
			bullet.decreAngle();										// 총알 각도 감소
		}

		shoot.L_wall();													// 슈터가 왼쪽 벽에 나가지 않게
		shoot.R_wall(WIDTH);											// 슈터가 오른쪽 벽에 나가지 않게

		shoot.setShooter_s();											// 계속 바뀌는 슈터 스프라이트 설정 ( 오른쪽 왼쪽 )

		bullet.shoot(shoot, shoot.getDirection());						// 각도에 맞춰 스프라이트 생성 및 위치
		bullet.shooting(WIDTH,dragon, HP_state);						// 총알 발사

		// 드래곤 설정
		dragon.dragon_fly(WIDTH, dragon_bottom);						// 드래곤 랜덤으로 날기
		dragon.setDragon_s();											// 계속 바뀌는 드래곤 스프라이트 설정( 오른쪽 왼쪽 )
		dragon.dragon_attack();											// 드래곤 불덩이 스프라이트 생성 및 위치 
		dragon.fire_shooting(WIDTH, shoot, HP_state, shooter_bottom);	// 불덩이 발사
		dragon.dragon_skill_1(MP_state);								// 슈터 S 스킬 
		dragon.dragon_skill_2(MP_state);								// 슈터 D 스킬
		shoot.Collision_dragon(dragon, HP_state);						// 드래곤 충돌 함수

		// HP & MP 설정
		HP_state.setUnits_HP();											// 유닛 HP 설정
		MP_state.setShooter_MP();										// 슈터 MP 설정

		// 아이템
		items.Bottom_f(shooter_bottom);									// 각 아이템 바닥 설정
		for (int i = 0; i < 4; i++)
		{
			items.drop_item(i);											// 1~4 아이템 드랍 
		}

		shoot.EatItem(items, bullet);									// 총알 속도 증가 아이템
		shoot.EatItem(items);											// 슈터 이동 속도 증가
		shoot.EatItem(items,HP_state);									// HP 회복 아이템
		shoot.EatItem(items,MP_state);									// MP 회복 아이템
					

		window.clear();

		window.draw(background_s);										// 배경
		window.draw(solid_s);											// 바닥
		window.draw(HP_state.getShooter_HP());							// HP 글씨 이미지
		window.draw(HP_state.getShooterImg());							// HP 도형 
		window.draw(MP_state.getShooter_MP());							// MP 글씨 이미지
		window.draw(MP_state.getSpriteImg());							// MP 도형
		window.draw(HP_state.getDragon_HP());							// 드래곤 글씨 이미지
		window.draw(HP_state.getDragonImg());							// 드래곤 도형
		window.draw(shoot.getSpriteImg());								// 슈터 
		for (int i = 0; i < 12; i++)									// 총알
		{
			for (auto& obj : bullet.getSpriteImg()[i])
			{
				window.draw(obj);
			}
		}
		window.draw(dragon.getDragon_s());								// 드래곤

		for (int i = 0; i < 2; i++)										// 불덩이
		{
			for (auto& obj : dragon.getSpriteImg()[i])
			{
				window.draw(obj);
			}
		}
		for (int i = 0; i < 4; i++)										// 아이템
		{
			if (!items.getDisappear(i))
			{
				window.draw(*(items.getSpriteImg(i)));
			}
		}
		window.display();
	}
	return 0;
}