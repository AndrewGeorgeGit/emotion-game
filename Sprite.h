#include "MasterHeader.h"
#include "Graphic.h"



#ifndef SPRITE_HEADER
#define SPRITE_HEADER



class Sprite
{
public:
	//required default constructor for subclass
	Sprite() : collidedWithHero(false) {};


	//creates a sprite of the passed type
	Sprite(Type spriteType, int speedSetting);


	//returns a random Type
	static Type randomType();


	//Returns true if (1) this is left of other or (2) this is directly below other
	bool operator< (const Sprite& other);


	//"is inside"/"overlaps"/"collission" operator. Returns true if two Sprites overlap.
	//12345comment: really uncomfortable about removing const
	virtual SpriteRelation operator>> (Sprite& other);


	//
	void command(Command direction);


	//returns graphic
	Graphic* getGraphic();


	//returns spriteType
	Type getType();


	//returns collidedWithHero
	bool hasCollidedWithHero();


	//
	virtual void move();

	
	//changes collidedWithHero from true to false
	//12345comment: try to find a way to make this protected?
	void setCollidedWithHero();


protected:
	//the sprite's type
	Type spriteType;


	//the corresponding on-screen Graphic
	Graphic graphic;


private:
	//state variable which tells where a particular Sprite has been in a collision with the HeroSprite
	//this indicates the Sprite is flagged for deletion
	bool collidedWithHero;
};



#endif