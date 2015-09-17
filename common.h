/*
This file holds all forward declarations, typedefs, and enums.
It also includes 
*/

#ifndef COMMON_HEADER
#define COMMON_HEADER



//common includes
#include <vector>



//graphics includes
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>



//constants
namespace emotion_game {
	const int WINDOW_WIDTH = 800,
		WINDOW_HEIGHT = 900;
};

//forward declarations
class Sprite;
class HeroSprite;
class Graphic;
class Collider;
class AcitveArea;
class Shader;
class SpriteTypeCollectionQueue;



//typedefs
typedef std::vector<Sprite*> Collision;
typedef GLuint VaoName;
typedef GLfloat Coordinate;



//enums
enum SpriteRelation : int
{
	COLLIDING = 2,	//two sprites share an X,Y value
	CLOSE = 1,		//two sprites share only an X or Y value
	FAR = 0			//two sprites share neighter an X or Y value
};

enum Command : int
{
	MOVE_NORTH = GLFW_KEY_W,
	MOVE_NORTHEAST = GLFW_KEY_E,
	MOVE_EAST = GLFW_KEY_D,
	MOVE_SOUTHEAST = GLFW_KEY_C,
	MOVE_SOUTH = GLFW_KEY_X,
	MOVE_SOUTHWEST = GLFW_KEY_Z,
	MOVE_WEST = GLFW_KEY_A,
	MOVE_NORTHWEST = GLFW_KEY_Q,
	STOP = GLFW_KEY_S
};

enum SpriteType : char
{
	RANDOM_TYPE = -1,
	JOY_TYPE = 0,
	SADNESS_TYPE = 1,
	ANGER_TYPE = 2,
	DISGUST_TYPE = 3,
	FEAR_TYPE = 4,
	HERO_TYPE = 5
};


const int NUMBER_OF_AI_SPRITE_TYPES = 5;


#endif