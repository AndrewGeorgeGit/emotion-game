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



bool ActiveArea::addSprite()
{
	if (spriteCount == MAX_SPRITES)
		return false;

	sprites[spriteCount++] = new Sprite(Sprite::randomType(), -1);

	return true;
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


	/* --- deleting sprite --- */
	delete sprites[spriteCount - 1];
	spriteCount--;

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

	for (int i = 1; i < MAX_SPRITES; i++)
		sprites[i] = nullptr;
}