#include "MasterHeader.h"
#include "Sprite.h"
#include "HeroSprite.h"
#include "Graphic.h"
#include "ActiveArea.h"



void Sprite::command(Command direction)
{
	graphic.issueNewTranslationInstruction(direction);
}



Graphic* Sprite::getGraphic()
{
	return &graphic;
}



Type Sprite::getType()
{
	return spriteType;
}



bool Sprite::hasCollidedWithHero()
{
	return collidedWithHero;
}



void Sprite::setCollidedWithHero()
{
	collidedWithHero = true;
}



void Sprite::move()
{
	if (!graphic.draw()) //if Graphic fails to draw, indicating it is waiting on a new instruction
	{
		Command direction;
		switch (rand() % 8)
		{
		case 0:
			direction = MOVE_NORTH;
			break;
		case 1:
			direction = MOVE_NORTHEAST;
			break;
		case 2:
			direction = MOVE_EAST;
			break;
		case 3:
			direction = MOVE_SOUTHEAST;
			break;
		case 4:
			direction = MOVE_SOUTH;
			break;
		case 5:
			direction = MOVE_SOUTHWEST;
			break;
		case 6:
			direction = MOVE_WEST;
			break;
		case 7:
			direction = MOVE_NORTHWEST;
			break;
		}
		command(direction);
	}
}



Type Sprite::randomType()
{
	return (Type)(rand() % 5);
}


bool Sprite::operator< (const Sprite& other)
{
	Coordinate xThis, yThis, xOther, yOther;

	this->graphic.currentWindowCoordinates(xThis, yThis);
	other.graphic.currentWindowCoordinates(xOther, yOther);


	if (xThis < xOther)
		return true;
	else if (xThis > xOther)
		return false;
	else if (yThis < yOther)
		return true;
	else //if the this is above other or if they both have the same coordinate
		return false;
}



SpriteRelation Sprite::operator>> (Sprite& other)
{
	Coordinate xThis, yThis, xOther, yOther;

	this->graphic.currentWindowCoordinates(xThis, yThis);
	other.graphic.currentWindowCoordinates(xOther, yOther);



	bool xWithinRange = abs(xThis - xOther) < Graphic::GRAPHIC_SIZE;
	bool yWithinRange = abs(yThis - yOther) < Graphic::GRAPHIC_SIZE;

	SpriteRelation relation;
	if (xWithinRange && yWithinRange)
		relation = COLLISION;
	else if (xWithinRange || yWithinRange)
		relation = IN_RANGE;
	else
		relation = OUT_OF_RANGE;

	if (relation == COLLISION)
	{
		if (this->spriteType == HERO_TYPE)
		{
			other.setCollidedWithHero();
			((HeroSprite*)this)->collectSprite(other.spriteType);
		}
			
		else if (other.spriteType == HERO_TYPE)
		{
			this->setCollidedWithHero();
			Sprite *heroSprite = &other;
			((HeroSprite*)heroSprite)->collectSprite(this->spriteType);
		}
	}

	return relation;
}


//12345comment: find better way to initialize graphic from the HeroSprite constructor w/o having to have a default value
Sprite::Sprite(Type spriteType, int speedSetting) : spriteType(spriteType), graphic(spriteType, speedSetting), collidedWithHero(false)
{

}