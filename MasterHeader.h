#ifndef MASTER_HEADER
#define MASTER_HEADER



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 900

//The active area is where moving sprites are contained within
#define ACTIVE_AREA_HEIGHT WINDOW_WIDTH

//the shelf is where the player's collection queue is held
#define SHELF_HEIGHT (WINDOW_HEIGHT - ACTIVE_AREA_HEIGHT)

#define BUFFER_SIZE 512

//the number of Sprites that will initially appear on screen along with the user
#define STARTING_SPRITE_COUNT 20



#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


//12345comment: turn collider class into ActiveArea function
class Sprite;
class HeroSprite;
class Graphic;
class Collider;
class AcitveArea;
class Shader;



typedef std::vector<Sprite*> Collision;
typedef GLuint VaoName;
typedef GLfloat Coordinate;



enum SpriteRelation : int
{
	COLLISION = 1,
	IN_RANGE = 0,
	OUT_OF_RANGE = -1
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


enum Type : char
{
	INVALID_TYPE = -1,
	JOY_TYPE = 0,
	SADNESS_TYPE = 1,
	ANGER_TYPE = 2,
	DISGUST_TYPE = 3,
	FEAR_TYPE = 4,
	HERO_TYPE = 5
};



void error_callback(int error, const char* description);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void clear_error_flag(const char *message);
#endif