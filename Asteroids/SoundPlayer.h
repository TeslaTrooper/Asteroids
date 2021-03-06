#ifndef SOUND_PLAYER
#define SOUND_PLAYER

#define SOUND_BANG_LARGE	1
#define SOUND_BANG_MEDIUM	2
#define SOUND_BANG_SMALL	3
#define SOUND_BEAT1			4
#define SOUND_BEAT2			5
#define SOUND_EXTRA_SHIP	6
#define SOUND_FIRE			7
#define SOUND_SAUCER_BIG	8
#define SOUND_SAUCER_SMALL	9
#define SOUND_THRUST		10

#include <SoundDriver.h>
#include "Util.h"

class SoundPlayer {

	SoundDriver soundDriver;

	float elapsedTime;
	bool isBackgroundSoundPlaying;
	char beat;

public:

	SoundPlayer();

	void update(float dt);

	void playBang(float size) const;
	void playBackgroundSound();
	void playExtraShip() const;
	void playFire() const;
	void playSaucer(float type) const;
	void playThrust() const;

	void stopThrust() const;
	void stopBackgroundSound();
	void stopSaucer(float type) const;
};

#endif SOUND_PLAYER
