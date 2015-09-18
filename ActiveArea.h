/*
Created By:
Andrew George
Kings of Tyrants Development
http://www.KingsOfTyrants.com
Copyright 2015

License:
Commercial use of this code or any derivative work that may come of it is strictly prohibited.

eMotion - ActiveArea.h:
The ActiveArea is the area on screen where the Sprites move.
This class serves as the Sprite container as a result.
It also controls program execution that occurs in the game loop.

Comments:
delete Collider.h/.cpp files in project directory
Is the size variable still needed?
*/



#ifndef ACTIVE_AREA_HEADER
#define ACTIVE_AREA_HEADER



//includes
#include "common.h"



class ActiveArea
{
public:
	//the initial number of sprites at the start 
	static const int STARTING_AI_SPRITES = 25;


	//1 (for the hero) + 2 * STARTING_AI_SPRITES (to account for collected Sprites' ability to spawn two more)
	static const int MAX_SPRITES = 1 + 2 * STARTING_AI_SPRITES;


	//the size of the ActiveArea and where its starting/ending pixel values
	static const int HEIGHT, WIDTH, MIN_X, MAX_X, MIN_Y, MAX_Y;


	//the length of the ActiveArea's diagonal
	static const double DIAGONAL;


	//returns singleton
	static ActiveArea* get();


	//deletes singleton
	static void destroy();


	//executes a single cycle of move, redraw, and collide commands
	void update();


	//adds Sprite unless MAX_SPRITES already exist, thereby returning false
	bool add(SpriteType spriteType = SpriteType::RANDOM_TYPE);


private:
	//intializes sprites[] with STARTING_AI_SPRITES and nullptrs
	ActiveArea();


	//frees memory allocated by contained sprites
	~ActiveArea();


	//deletes sprites[index]
	void remove(int index);


	//the only allowable instance of the class
	static ActiveArea *singleton;


	//sprites contained within the ActiveArea/Sprite container
	Sprite *sprites[MAX_SPRITES];


	//count of each SpriteType
	int distribution[5];


	//total Sprites
	int count;


	//uses SpriteType distribution to semi-randomly determine the next SpriteType to be added
	SpriteType generateNextSpriteType();


	//sorts sprites[] from bottom left to top right
	void order();


	//determines which Sprites are in contact with each other before passing of the collisions to Graphic::collide()
	void collide();
};



#endif