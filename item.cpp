#include "item.h"

void item::setDisappear(int index, bool temp)									// 슈터가 아이템을 먹으면 true, 안먹으면 false
{
	switch (index)
	{
	case 0:
	{
		disappear[0] = temp;
		break;
	}
	case 1:
	{
		disappear[1] = temp;
		break;
	}
	case 2:
	{
		disappear[2] = temp;
		break;
	}
	default:
	{
		disappear[3] = temp;
		break;
	}
	}
}

bool item::getDisappear(int index)												// disappear 반환
{	
	switch (index)
	{
	case 0:
		return disappear[0];
	case 1:
		return disappear[1];
	case 2:
		return disappear[2];
	default:
		return disappear[3];
	}
}

void item::setTextureImg()														// 텍스쳐 설정
{
	speed_up_t.loadFromFile("item.png");
	Shooter_speed_t.loadFromFile("item2.png");
	HP_up_t.loadFromFile("item3.png");
	MP_up_t.loadFromFile("item4.png");
}

void item::setSpriteImg()														// 스프라이트 설정
{
	speed_up_s.setTexture(speed_up_t);
	Shooter_speed_s.setTexture(Shooter_speed_t);
	HP_up_s.setTexture(HP_up_t);
	MP_up_s.setTexture(MP_up_t);
}

void item::Bottom_f(float bottom)
{
	bottom = bottom;
	temp_bottom1[0] = bottom + 105;
	temp_bottom2[0] = bottom + 115;
	temp_bottom1[1] = bottom + 85;
	temp_bottom2[1] = bottom + 95;
	temp_bottom1[2] = temp_bottom1[3] = bottom + 70;
	temp_bottom2[2] = temp_bottom2[3] = bottom + 80;

}

Sprite* item::getSpriteImg(int index)											// 스프라이트 반환 포인터 쓴 이유는 슈터에서 써야함
{
	switch (index)
	{
	case 0:
		return &speed_up_s;
	case 1:
		return &Shooter_speed_s;
	case 2:
		return &HP_up_s;
	default :
		return &MP_up_s;
	}
}

void item::drop_item(int temp)
{
	if (time[temp] == 0)														// 시간 랜덤으로 드랍
	{
		getSpriteImg(temp)->setPosition((float)(rand() % 1600) + 100, 0);		// 아이템 위치 설정
		switch (temp)
		{
		case 0:
		{
			time[temp] = rand() % 600 + 1800;									// 시간 랜덤 설정	
			break;
		}
		case 1:
		{
			time[temp] = rand() % 600 + 1800;
			break;
		}
		case 2:
		{
			time[temp] = rand() % 1800 + 3600;
			break;
		}
		default:
		{
			time[temp] = rand() % 1800 + 3600;
			break;
		}
		}	
		disappear[temp] = false;
		make[temp] = true;														// 아이템 제작 확인
	}
	else if (time[temp] > 0)
	{
		if (make[temp])															// 아이템 생성 됬다면 실행
		{
			if (getSpriteImg(temp)->getPosition().y <= temp_bottom1[temp])		// 바닥까지 하강
			{
				getSpriteImg(temp)->setPosition(getSpriteImg(temp)->getPosition().x, getSpriteImg(temp)->getPosition().y + 10);
			}
			else
			{
				getSpriteImg(temp)->setPosition(getSpriteImg(temp)->getPosition().x, temp_bottom2[temp]);
				make[temp] = false;												// 바닥이므로 더 이상 if문 안돌림
			}
		}
		time[temp]--;
	}
	else if (time[temp] < 0)
	{
		time[temp] = 0;
	}
}