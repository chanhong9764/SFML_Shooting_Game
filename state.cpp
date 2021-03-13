#include "state.h"

void HP::decrease_DragonHP()
{
	dragon_gauge -= 10;
	if (dragon_gauge <= 0)
	{
		exit(1);											// Game over
	}
}

void HP::decrease_ShooterHP()
{
	shooter_gauge -= 50;
	if (shooter_gauge <= 0)
	{
		exit(1);											// Game over
	}
}

void HP::incre_HP()											// 물약 HP 증가
{
	shooter_gauge += 100;
	if (shooter_gauge >= 500)
	{
		shooter_gauge = 500;
	}
}

void HP::setTextureImg()									// 텍스쳐 설정
{
	shooterHP_t.loadFromFile("Shooter_HP.png");
	dragonHP_t.loadFromFile("Dragon_HP.png");
}

void HP::setSpirteImg()										// 스프라이트 설정
{
	shooterHP_s.setTexture(shooterHP_t);
	dragonHP_s.setTexture(dragonHP_t);
}


Sprite HP::getShooterImg()									// 슈터 HP 글씨 스프라이트 반환
{
	return shooterHP_s;
}

Sprite HP::getDragonImg()									// 드래곤 HP 글씨 스프라이트 반환
{
	return dragonHP_s;
}

void HP::setImgPosition()									// 글씨 이미지 위치 설정
{
	shooterHP_s.setPosition(30, 913);
	dragonHP_s.setPosition(840, 913);
}

void HP::setUnits_HP()										// 유닛 HP 설정
{
	shooter_HP.setSize(Vector2f(shooter_gauge ,30));
	shooter_HP.setPosition(200, 920);
	shooter_HP.setFillColor(Color(255,0,0));

	dragon_HP.setSize(Vector2f(dragon_gauge, 30));
	dragon_HP.setPosition(1000, 920);
	dragon_HP.setFillColor(Color(255, 0, 0));
}

RectangleShape HP::getShooter_HP()							// 슈터 HP 반환
{
	return shooter_HP;
}


RectangleShape HP::getDragon_HP()							// 드래곤 HP 반환
{
	return dragon_HP;
}




void MP::setShooter_MP()									// 슈터 MP 설정
{
	shooter_MP.setSize(Vector2f(gauge, 30));
	shooter_MP.setPosition(200, 970);
	shooter_MP.setFillColor(Color(1, 0, 255));
}

RectangleShape MP::getShooter_MP()							// 슈터 MP 반환
{
	return shooter_MP;
}

void MP::setTextureImg()									// 슈터 MP 글씨 텍스쳐 설정
{
	shooterMP_t.loadFromFile("Shooter_MP.png");
}

void MP::setSpriteImg()										// 슈터 MP 글씨 스프라이트 설정
{
	shooterMP_s.setTexture(shooterMP_t);
}

Sprite MP::getSpriteImg()									// 슈터 MP 글씨 스프라이트 반환
{
	return shooterMP_s;
}

void MP::setSpriteImg_MP()									// 슈터 MP 글씨 위치 설정
{
	shooterMP_s.setPosition(30,967);
}

float MP::get_MP()											// MP 반환
{
	return gauge;
}

void MP::decreMP()											// MP 감소 스킬 쓸 때 사용
{
	if (gauge <= 0)
	{
		gauge = 0;
	}
	else
	{
		gauge -= 50;
	}
}

void MP::incre_MP()											// MP 증가 아이템 획득 시 사용
{
	gauge += 100;
	if (gauge>= 500)
	{
		gauge = 500;
	}
}