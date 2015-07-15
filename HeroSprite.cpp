#include "MasterHeader.h"
#include "Sprite.h"
#include "HeroSprite.h"
#include "Graphic.h"
#include "ShelfArea.h"



HeroSprite *HeroSprite::hero = nullptr;



void HeroSprite::collectSprite(Type spriteType)
{
	spriteCollection.enqeue(spriteType);
}



HeroSprite* HeroSprite::getHeroSprite()
{
	if (hero == nullptr)
		hero = new HeroSprite();
	return hero;
}



void HeroSprite::move()
{
	graphic.draw();
}



//12345comment: this has not been coded to handle more Types. 
bool HeroSprite::victoryConditionMet()
{
	int target = SpriteCollectionQueue::QUEUE_SIZE / 5;

	for (int i = 0; i < 5; i++)
	{
		if (spriteCollection.typeDemand((Type)i) != 0)
			return false;
	}

	return true;
}



//12345comment: maybe not as fluid as it can be
HeroSprite::HeroSprite() : Sprite(Type::HERO_TYPE, 2)
{
	ShelfArea::getShelfArea()->linkData(&spriteCollection);
}