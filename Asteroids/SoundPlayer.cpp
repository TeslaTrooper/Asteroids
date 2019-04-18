#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : elapsedTime(0), isBackgroundSoundPlaying(true), beat(0) {
	soundDriver.load(SOUND_BANG_LARGE, SoundFiles::bangLarge);
	soundDriver.load(SOUND_BANG_MEDIUM, SoundFiles::bangMedium);
	soundDriver.load(SOUND_BANG_SMALL, SoundFiles::bangSmall);
	soundDriver.load(SOUND_BEAT1, SoundFiles::beat1);
	soundDriver.load(SOUND_BEAT2, SoundFiles::beat2);
	soundDriver.load(SOUND_EXTRA_SHIP, SoundFiles::extraShip);
	soundDriver.load(SOUND_FIRE, SoundFiles::fire);
	soundDriver.load(SOUND_SAUCER_BIG, SoundFiles::saucerBig);
	soundDriver.load(SOUND_SAUCER_SMALL, SoundFiles::saucerSmall);
	soundDriver.load(SOUND_THRUST, SoundFiles::thrust);
}

void SoundPlayer::update(float dt) {
	this->elapsedTime += dt;

	if (!isBackgroundSoundPlaying)
		return;

	bool evenSecond = ((int) elapsedTime) % 2 == 0;
	if (beat != 0 && evenSecond)
		soundDriver.play(SOUND_BEAT1, PLAY_MODE_ONCE, false);
	else if (beat != 1 && !evenSecond)
		soundDriver.play(SOUND_BEAT2, PLAY_MODE_ONCE, false);

	beat = (char) (((int) elapsedTime) % 2);
}

void SoundPlayer::playBang(float size) const {
	if (size == SIZE_LARGE)
		soundDriver.play(SOUND_BANG_LARGE, PLAY_MODE_ONCE, true);
	else if (size == SIZE_MEDIUM)
		soundDriver.play(SOUND_BANG_MEDIUM, PLAY_MODE_ONCE, true);
	else if (size == SIZE_SMALL)
		soundDriver.play(SOUND_BANG_SMALL, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playBackgroundSound() {
	this->isBackgroundSoundPlaying = true;
}

void SoundPlayer::playExtraShip() const {
	soundDriver.play(SOUND_EXTRA_SHIP, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playFire() const {
	soundDriver.play(SOUND_FIRE, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playSaucer(float type) const {
	if (type == SIZE_LARGE)
		soundDriver.play(SOUND_SAUCER_BIG, PLAY_MODE_LOOP, false);
	else
		soundDriver.play(SOUND_SAUCER_SMALL, PLAY_MODE_LOOP, false);
}

void SoundPlayer::playThrust() const {
	soundDriver.play(SOUND_THRUST, PLAY_MODE_LOOP, false);
}

void SoundPlayer::stopThrust() const {
	soundDriver.stop(SOUND_THRUST);
}

void SoundPlayer::stopBackgroundSound() {
	this->isBackgroundSoundPlaying = false;
}

void SoundPlayer::stopSaucer(float type) const {
	if (type == SIZE_LARGE)
		soundDriver.stop(SOUND_SAUCER_BIG);
	else
		soundDriver.stop(SOUND_SAUCER_SMALL);
}
