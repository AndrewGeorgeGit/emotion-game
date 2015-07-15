#include "MasterHeader.h"
#include "Sprite.h"
#include "Graphic.h"
#include "Collider.h"



Collider::Collider(Sprite *sprites[], int count)
{
	collisionGroupIndex = new int[count];

	for (int currSprite = 0; currSprite < count; currSprite++)
		collisionGroupIndex[currSprite] = -1;	//-1 indicates a particular Sprite has yet to be added to a CollisionGroup



	for (int currSprite = 0; currSprite < count; currSprite++)
	{
		if (collisionGroupIndex[currSprite] == -1)
		{
			collisions.push_back(Collision());

			collisionGroupIndex[currSprite] = collisions.size() - 1;

			collisions[collisionGroupIndex[currSprite]].push_back(sprites[currSprite]);
		}



		int j = currSprite + 1;
		int proximity;
		while (j < count && (proximity = *sprites[currSprite] >> *sprites[j]) > OUT_OF_RANGE) //12345comment: if y is always within rage, loop will continue. Interesting.
		{
			if (proximity == COLLISION)
			{
				collisions[collisionGroupIndex[currSprite]].push_back(sprites[j]);

				collisionGroupIndex[j] = collisionGroupIndex[currSprite];
			}
			j++;
		}
	}

	for (int i = 0; i < collisions.size(); i++)
		Graphic::avoid(collisions[i]);



	delete[] collisionGroupIndex;
}