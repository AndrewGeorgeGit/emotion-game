/*
Created By:
Andrew George
of Kings of Tyrants Development
http://www.KingsOfTyrants.com
Copyright 2015

License:
Commercial use of this code or any derivative work that may come of it is strictly prohibited.

eMotion - Sprite.h:

*/



#ifndef SPRITE_HEADER
#define SPRITE_HEADER



//includes
#include "common.h"
#include "Graphic.h"



class Sprite
{
public:
	//required default constructor for subclass
	Sprite() : collidedWithHero(false) {};


	//creates a sprite of the passed type
	Sprite(SpriteType spriteType, int speedSetting);


	//returns a random Type
	static SpriteType randomType();


	//Returns true if (1) this is left of other or (2) this is directly below other
	bool operator< (const Sprite& other);


	//"is inside"/"overlaps"/"collission" operator. Returns true if two Sprites overlap.
	//12345comment: really uncomfortable about removing const
	virtual SpriteRelation relationTo(Sprite &other);


	//
	void command(Command direction);


	//returns graphic
	Graphic* getGraphic();


	//returns spriteType
	SpriteType getType();


	//returns collidedWithHero
	bool hasCollidedWithHero();


	//
	virtual void move();

	
	//changes collidedWithHero from true to false
	//12345comment: try to find a way to make this protected?
	void setCollidedWithHero();


protected:
	//the sprite's type
	SpriteType spriteType;


	//the corresponding on-screen Graphic
	Graphic graphic;


private:
	//state variable which tells where a particular Sprite has been in a collision with the HeroSprite
	//this indicates the Sprite is flagged for deletion
	bool collidedWithHero;
};



#endif