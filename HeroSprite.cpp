//includes
#include "HeroSprite.h"
#include "ShelfArea.h"


HeroSprite *HeroSprite::hero = nullptr;



void HeroSprite::collectSprite(SpriteType spriteType)
{
	collection.collect(spriteType);
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



bool HeroSprite::victoryConditionMet()
{
	for (int i = 0; i < NUMBER_OF_AI_SPRITE_TYPES; i++)
		if (collection.demandFor((SpriteType)i) != 0)
			return false;

	return true;
}



//12345comment: maybe not as fluid as it can be
HeroSprite::HeroSprite() : Sprite(SpriteType::HERO_TYPE, 2)
{
	ShelfArea::getShelfArea()->linkData(&collection);
}