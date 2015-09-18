//includes
#include "Sprite.h"
#include "HeroSprite.h"



void Sprite::command(Command direction)
{
	graphic.issueNewTranslationCommand(direction);
}



Graphic* Sprite::getGraphic()
{
	return &graphic;
}



SpriteType Sprite::getType()
{
	return spriteType;
}



bool Sprite::hasCollidedWithHero()
{
	return collidedWithHero;
}



/*
Returns the distance relationship of two Sprites.
Returns COLLIDING if the Sprites share both an X and Y coordinate.
Returns CLOSE if the Sprites only share a singular coordinate.
Returns FAR if the Sprites do not share a coordinate.
If the HeroSprite is COLLIDING with another, collects the non-Hero Sprite and sets its collission flag.
*/
SpriteRelation Sprite::relationTo(Sprite& other)
{
	///getting coordinates
	Coordinate xThis, yThis, xOther, yOther;

	this->graphic.currentWindowCoordinates(xThis, yThis);
	other.graphic.currentWindowCoordinates(xOther, yOther);



	//determining distance relationship
	bool xWithinRange = abs(xThis - xOther) < Graphic::GRAPHIC_SIZE;
	bool yWithinRange = abs(yThis - yOther) < Graphic::GRAPHIC_SIZE;

	SpriteRelation relation;
	if (xWithinRange && yWithinRange)
		relation = SpriteRelation::COLLIDING;
	else if (xWithinRange || yWithinRange)
		relation = SpriteRelation::CLOSE;
	else
		relation = SpriteRelation::FAR;



	//
	if (relation == SpriteRelation::COLLIDING)
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



SpriteType Sprite::randomType()
{
	return (SpriteType)(rand() % 5);
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


//12345comment: find better way to initialize graphic from the HeroSprite constructor w/o having to have a default value
Sprite::Sprite(SpriteType spriteType, int speedSetting) : spriteType(spriteType), graphic(spriteType, speedSetting), collidedWithHero(false)
{

}