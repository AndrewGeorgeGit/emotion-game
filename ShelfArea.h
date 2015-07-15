#include "MasterHeader.h"
#include "SpriteCollectionQueue.h"



#ifndef SHELF_AREA_HEADER
#define SHELF_AREA_HEADER



class ShelfArea
{
public:
	//updates shelf
	void draw();


	//returns the single instance of this class
	static ShelfArea* getShelfArea();


	//sets data to passed pointer
	void linkData(SpriteCollectionQueue* d);


private:
	//creates and initializes all VAOs
	ShelfArea();


	//the only object of this type to be created
	static ShelfArea *singleton;	//12345comment: do you delete?


	//holds vao names
	GLuint indicatorVao[5], plus, minus;


	//the data that determines 
	SpriteCollectionQueue* data;


	//
	void drawPlus(int indicator);
	void drawMinus(int indicator);
};



#endif