/*
Created By:
Andrew George
of Kings of Tyrants Development
http://www.KingsOfTyrants.com
Copyright 2015

License:
Commercial use of this code or any derivative work that may come of it is strictly prohibited.

eMotion - HeroSprite.h:
Class defintion of a unique instance of Sprite that is controlled by the User.

Comments:
get rid of the imaginary number
*/



#ifndef HERO_SPRITE_HEADER
#define HERO_SPRITE_HEADER



//includes
#include "common.h"
#include "Sprite.h"
#include "SpriteTypeCollectionQueue.h"



class HeroSprite : public Sprite
{
public:
	//updates the Hero's collection poll and the ShelfArea
	void collectSprite(SpriteType spriteType);


	//returns hero
	static HeroSprite* getHeroSprite();


	//overloads base class Sprite's move() method to prevent auto movement of the HeroSprite
	void move();


	//returns true if Hero has collected an equal number of sprites
	bool victoryConditionMet();


private:
	//the HeroSprite is controlled by the user
	//there is only one user, therefore there only needs to be one HeroSprite
	static HeroSprite *hero;


	//creates a Sprite with type HERO_SPRITE
	HeroSprite();


	//the Sprite Types the Hero posseses
	//when there is a balance among all Types, victory condition is reached
	SpriteTypeCollectionQueue collection;
};



#endif