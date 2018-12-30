#ifndef UTIL
#define UTIL

//#define DEBUG

#include <vector>

#include "structs.h"
#include "Mat4.h"

#define VERTEX_COMP_SIZE 2
#define WIN_WIDTH 900
#define WIN_HEIGHT 600

#define SIZE_LARGE 1.5f
#define SIZE_MEDIUM 1.f
#define SIZE_SMALL 0.5f

#define MAX_PROJECTILE 4
#define PROJECTILE_MAX_LIFETIME 1.5f
#define GAP_PROJECTILE_SHIP 10
#define PROJECTILE_SPEED 6
#define ROTATION_ZONE 45
#define ASTEROID_MIN_VELOCITY 20
#define ASTEROID_MAX_VELOCITY 50
#define ASTEROID_PIECE_COUNT 2

#define PARTICLE_COUNT 2
#define PARTICLE_MAX_LIFETIME 1
#define PARTICLE_MIN_VELOCITY 1
#define PARTICLE_MAX_VELOCITY 2

#define INITAL_ENTITY_COUNT 2
#define SMALL_SAUCER_INTERVAL 40
#define BIG_SAUCER_INTERVAL 20
#define SAUCER_MIN_VELOCITY 10
#define SAUCER_MAX_VELOCITY 30

enum ModelClass {
	CLASS_ASTEROID, CLASS_SHIP, CLASS_SAUCER, CLASS_PROJECTILE, CLASS_LINE_SEGMENT, CLASS_UNDEFINED
};

enum Model {
	ASTEROID1, ASTEROID2, ASTEROID3, ASTEROID4, SHIP, SAUCER, SHIP_MOVING, PROJECTILE, LINE_SEGMENT,
	CHARA, CHAR0, CHAR1,
	CHAR2, CHAR3, CHAR4,
	CHAR5, CHAR6, CHAR7,
	CHAR8, CHAR9
};

struct Dimension {
	float width;
	float height;
};

struct RenderUnit {
	Mat4 transformation;
	Model model;
};

struct CustomBufferData {
	unsigned int vao, vao1;
	unsigned int ebo;
	unsigned int vbo;
	int indexCount, indexCount1;
	int drawMode;
};

struct CollisionInfo {
	ModelClass classOfObj;
	float objSize;
	Vec2 collisionLocation;
};

static Dimension operator*(const Dimension dim, const float scale) {
	return { dim.width * scale, dim.height * scale };
}

static ModelClass getClassFromModel(const Model model) {
	switch (model) {
		case ASTEROID1:
		case ASTEROID2:
		case ASTEROID3:
		case ASTEROID4: return CLASS_ASTEROID; break;
		case SHIP:
		case SHIP_MOVING: return CLASS_SHIP; break;
		case SAUCER: return CLASS_SAUCER; break;
		case PROJECTILE: return CLASS_PROJECTILE; break;
		case LINE_SEGMENT: return CLASS_LINE_SEGMENT; break;
		default: return CLASS_ASTEROID; break;
	}
}

// Returns a random number between min and max. Note: min and max included.
static int random(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}

static Vec2 getRandomPosition() {
	int x = random(0, WIN_WIDTH);
	int y = random(0, WIN_HEIGHT);

	return Vec2(x, y);
}

#endif UTIL