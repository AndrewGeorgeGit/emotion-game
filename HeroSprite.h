#include "MasterHeader.h"
#include "Sprite.h"
#include "SpriteCollectionQueue.h"



#ifndef HERO_SPRITE_HEADER
#define HERO_SPRITE_HEADER



class HeroSprite : public Sprite
{
public:
	//updates the Hero's collection poll and the ShelfArea
	void collectSprite(Type spriteType);


	//returns the single instance of the HeroSprite
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
	//when there is a balance amongall Types, victory condition is reached
	SpriteCollectionQueue spriteCollection;
};



#endif