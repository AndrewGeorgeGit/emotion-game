#include "MasterHeader.h"
#include "Sprite.h"
#include "Shader.h"
#include "Graphic.h"
#include "Collider.h"
#include "ActiveArea.h"
#include "HeroSprite.h"



//12345comment: assuming active area will always be square. Consider size being a measure of bottom left to top right
ActiveArea *ActiveArea::singleton = nullptr;
const int ActiveArea::MIN_X = 0,
ActiveArea::MAX_X = WINDOW_WIDTH - Graphic::GRAPHIC_SIZE,
ActiveArea::MIN_Y = SHELF_HEIGHT,
ActiveArea::MAX_Y = WINDOW_HEIGHT - Graphic::GRAPHIC_SIZE,
ActiveArea::SIZE = MAX_X - MIN_X;



bool ActiveArea::addSprite(Type spriteType)
{
	if (spriteCount == MAX_SPRITES)
		return false;

	if (spriteType == Type::INVALID_TYPE)
		spriteType = determineNewSpriteType();


	//save reference to new Sprite
	sprites[spriteCount] = new Sprite(spriteType, -1);
	

	//record new Sprite's Type
	distribution[sprites[spriteCount]->getType()]++;


	//increment number of sprites
	spriteCount++;


	return true;
}



Type ActiveArea::determineNewSpriteType()
{
	if (spriteCount == 1) return Sprite::randomType();


	double odds[5][2];

	for (int i = 0; i < 5; i++)
	{
		odds[i][0] = i;
		odds[i][1] = (double)distribution[i] / spriteCount * 100.0;

		for (int j = i; j > 0; j--)
		{
			if (odds[j][1] < odds[j - 1][1])
			{
				double tempType = odds[j - 1][0],
					tempOdds = odds[j - 1][1];

				odds[j - 1][0] = odds[j][0];
				odds[j - 1][1] = odds[j][1];

				odds[j][0] = tempType;
				odds[j][1] = tempOdds;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = 0, j = 4; i < j; i++, j--)
	{
		double tempOdds = odds[i][1];
		odds[i][1] = odds[j][1];
		odds[j][1] = tempOdds;
	}

	int sum = 0;
	for (int i = 1; i < 5; i++)
	{
		odds[i][1] += odds[i - 1][1];
	}

	int choice = rand() % (int)odds[4][1];

	for (int i = 0;; i++)
	{
		if (choice < odds[i][1])
			return (Type)(int)odds[i][0];
	}
}



ActiveArea* ActiveArea::getActiveArea()
{
	if (singleton == nullptr)
		singleton = new ActiveArea;

	return singleton;
}



void ActiveArea::order()
{
	for (int i = 1; i < spriteCount; i++)
	{
		int j = i;
		while ( j > 0 && *sprites[j] < *sprites[j - 1])
		{
			Sprite *temp = sprites[j];
			sprites[j] = sprites[j - 1];
			sprites[j - 1] = temp;
			j--;
		}
	}
}



void ActiveArea::play()
{
	/* --- drawing sprites --- */
	Shader::useShaderProgram();
	for (int i = 0; i < spriteCount; i++)
		sprites[i]->move();

	/* ---  --- */
	order();

	Collider(sprites, spriteCount);



	/* --- --- */
	for (int i = 0; i < spriteCount; i++)
		if (sprites[i]->hasCollidedWithHero())
			removeSprite(i);
}



void ActiveArea::removeSprite(int index)
{
	/* --- swaping sprite to be deleted to the last active element --- */
	Sprite *deleting = sprites[index],
		*saving = sprites[spriteCount - 1];

	sprites[index] = saving;
	sprites[spriteCount - 1] = deleting;


	/* --- updating counters and deleting --- */
	distribution[deleting->getType()]--;
	spriteCount--;
	delete deleting;
	

	/* --- adding a  sprite if none of its kind exist --- */
	//1345comment: under the assumption there is room
	for (int i = 0; i < 5; i++)
		if (distribution[i] == 0)
		{
			addSprite((Type)i);
		}
			


	/* ** pontentially generating new sprites --- */
	int spawn = rand() % 3;
	for (int i = 0; i < spawn; i++)
		addSprite();
}



//12345comment: not initialzing
ActiveArea::ActiveArea() : spriteCount(1)	//initialized to 1 because we add the user immediately
{
	spriteCount = 1;
	sprites[0] = HeroSprite::getHeroSprite();


	for (int i = 0; i < 5; i++)
		distribution[i] = 0;


	for (int i = 1; i < MAX_SPRITES; i++)
		sprites[i] = nullptr;
}