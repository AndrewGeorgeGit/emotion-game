//includes
#include "ActiveArea.h"
#include "Sprite.h"
#include "HeroSprite.h"
#include "ShelfArea.h"
#include "Shader.h"
//#include "Graphic.h"



ActiveArea *ActiveArea::singleton = nullptr;



//12345comment: assuming active area will always be square. Consider size being a measure of bottom left to top right
const int
ActiveArea::HEIGHT = 800,
ActiveArea::WIDTH = 800,
ActiveArea::MIN_X = 0,
ActiveArea::MAX_X = ActiveArea::MIN_X + (ActiveArea::WIDTH - Graphic::GRAPHIC_SIZE),
ActiveArea::MIN_Y = ShelfArea::SHELF_HEIGHT, //starts where the ShelfArea ends
ActiveArea::MAX_Y = ActiveArea::MIN_Y + (ActiveArea::HEIGHT - Graphic::GRAPHIC_SIZE);

const double ActiveArea::DIAGONAL = sqrt(pow(HEIGHT, 2) + pow(WIDTH, 2));


bool ActiveArea::add(SpriteType spriteType)
{
	if (count == MAX_SPRITES)
		return false;

	if (spriteType == SpriteType::RANDOM_TYPE)
		spriteType = generateNextSpriteType();

	sprites[count++] = new Sprite(spriteType, -1);
	distribution[spriteType]++;

	return true;
}



void ActiveArea::collide()
{
	//every Sprite is consider involved in a Collision even if it is only with itself
	//meaning every Sprite holds a reference (the index value) to its related collision once it has been determined
	std::vector<Collision> collisions;
	int *associatedCollision = new int[count];
	const int no_collision_group = -1;
	for (int i = 0; i < count; i++) associatedCollision[i] = no_collision_group;



	for (int current = 0; current < count; current++)
	{
		if (associatedCollision[current] == no_collision_group)
		{
			associatedCollision[current] = collisions.size();
			collisions.push_back(Collision());
			collisions[associatedCollision[current]].push_back(sprites[current]);
		}



		for (int neighbor = current + 1, relation;
			 (neighbor < count) && ( (relation = sprites[current]->relationTo(*sprites[neighbor])) > SpriteRelation::FAR);
			 neighbor++)
		{
			if (relation == SpriteRelation::COLLIDING)
			{
				associatedCollision[neighbor] = associatedCollision[current];
				collisions[associatedCollision[neighbor]].push_back(sprites[neighbor]);
			}
		}
	}



	for (int i = 0, n = collisions.size(); i < n; i++)
		Graphic::collide(collisions[i]);


	
	delete[] associatedCollision;
}



void ActiveArea::destroy()
{
	delete singleton;
}



/*
(1) calculates a SpriteType's appearance rate in the current ActiveArea
(2) swaps high-low pairs, this means the lowest appearing SpriteType has the highest odds 
(3) randomly selects SpriteType based on these odds
*/
SpriteType ActiveArea::generateNextSpriteType()
{
	if (count == 1) return Sprite::randomType();


	//[][0] holds Sprite type. [][1] holds odds.
	double spriteTypeOdds[NUMBER_OF_AI_SPRITE_TYPES][2];


	//calculating appearance rate of each SpriteType. Ordering them also.
	for (int i = 0; i < NUMBER_OF_AI_SPRITE_TYPES; i++)
	{
		spriteTypeOdds[i][0] = i;
		spriteTypeOdds[i][1] = (double)distribution[i] / (count - 1) * 100.0;

		for (int j = i; j > 0; j--)
		{
			if (spriteTypeOdds[j][1] < spriteTypeOdds[j - 1][1])
				std::swap(spriteTypeOdds[j], spriteTypeOdds[j - 1]);
			else
				break;
		}
	}


	//swapping high-low pairs
	for (int i = 0, j = NUMBER_OF_AI_SPRITE_TYPES - 1; i < j; i++, j--)
	{
		std::swap(spriteTypeOdds[i][1], spriteTypeOdds[j][1]);
	}



	for (int i = 1; i < NUMBER_OF_AI_SPRITE_TYPES; i++)
	{
		spriteTypeOdds[i][1] += spriteTypeOdds[i - 1][1];
	}


	//choosing next SpriteType
	int choice = rand() % (int)spriteTypeOdds[NUMBER_OF_AI_SPRITE_TYPES - 1][1];
	for (int i = 0;; i++)
	{
		if (choice < spriteTypeOdds[i][1])
			return (SpriteType)(int)spriteTypeOdds[i][0];
	}
}



ActiveArea* ActiveArea::get()
{
	if (singleton == nullptr)
		singleton = new ActiveArea;

	return singleton;
}



void ActiveArea::order()
{
	//insertion sort
	for (int i = 1; i < count; i++)
		for (int j = i; j > 0 && *sprites[j] < *sprites[j - 1]; j--)
			std::swap(sprites[j], sprites[j - 1]);
}



void ActiveArea::update()
{
	/* --- drawing sprites --- */
	Shader::useShaderProgram();
	for (int i = 0; i < count; i++)
		sprites[i]->move();

	/* --- resolving collisions --- */
	order();
	collide();

	/* --- removing collected sprites --- */
	for (int i = 0; i < count; i++)
		if (sprites[i]->hasCollidedWithHero())
			remove(i);
}



void ActiveArea::remove(int index)
{
	/* --- swaping sprite to be deleted to the last active element --- */
	std::swap(sprites[index], sprites[count - 1]);



	Sprite *deleting = sprites[count - 1];
	SpriteType spriteType = deleting->getType();



	/* --- updating counters and deleting --- */
	distribution[spriteType]--;
	count--;
	delete deleting;
	


	/* --- adding a sprite if none of its kind exist --- */
	if (distribution[(int)spriteType] == 0) add(spriteType);
			


	/* --- pontentially generating new sprites --- */
	int spawn = rand() % 3;
	while (spawn-- > 0)
		add();
}



ActiveArea::ActiveArea()
{
	sprites[0] = HeroSprite::getHeroSprite();
	count = 1;

	for (int i = 0; i < 5; i++)
		distribution[i] = 0;

	for (; count < STARTING_AI_SPRITES + 1;)
		add();

	for (int i = count; i < MAX_SPRITES; i++)
		sprites[i] = nullptr;
}



ActiveArea::~ActiveArea()
{
	for (int i = 0; i < count; i++)
		delete sprites[i];
}