#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : elapsedTime(0), isBackgroundSoundPlaying(true), beat(0) {
	soundMaster.load(SOUND_BANG_LARGE, SoundFiles::bangLarge);
	soundMaster.load(SOUND_BANG_MEDIUM, SoundFiles::bangMedium);
	soundMaster.load(SOUND_BANG_SMALL, SoundFiles::bangSmall);
	soundMaster.load(SOUND_BEAT1, SoundFiles::beat1);
	soundMaster.load(SOUND_BEAT2, SoundFiles::beat2);
	soundMaster.load(SOUND_EXTRA_SHIP, SoundFiles::extraShip);
	soundMaster.load(SOUND_FIRE, SoundFiles::fire);
	soundMaster.load(SOUND_SAUCER_BIG, SoundFiles::saucerBig);
	soundMaster.load(SOUND_SAUCER_SMALL, SoundFiles::saucerSmall);
	soundMaster.load(SOUND_THRUST, SoundFiles::thrust);
}

void SoundPlayer::update(float dt) {
	this->elapsedTime += dt;

	if (!isBackgroundSoundPlaying)
		return;

	bool evenSecond = ((int) elapsedTime) % 2 == 0;

	// Distinguish between even and uneven seconds
	// For every even second, play SOUND_BEAT1
	// For every uneven second, play SOUND_BEAT2
	if (beat != 0 && evenSecond)
		soundMaster.play(SOUND_BEAT1, PLAY_MODE_ONCE, false);
	else if (beat != 1 && !evenSecond)
		soundMaster.play(SOUND_BEAT2, PLAY_MODE_ONCE, false);

	beat = (char) (((int) elapsedTime) % 2);
}

void SoundPlayer::playBang(float size) const {
	if (size == SIZE_LARGE)
		soundMaster.play(SOUND_BANG_LARGE, PLAY_MODE_ONCE, true);
	else if (size == SIZE_MEDIUM)
		soundMaster.play(SOUND_BANG_MEDIUM, PLAY_MODE_ONCE, true);
	else if (size == SIZE_SMALL)
		soundMaster.play(SOUND_BANG_SMALL, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playBackgroundSound() {
	this->isBackgroundSoundPlaying = true;
}

void SoundPlayer::playExtraShip() const {
	soundMaster.play(SOUND_EXTRA_SHIP, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playFire() const {
	soundMaster.play(SOUND_FIRE, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playSaucerBig() const {
	soundMaster.play(SOUND_SAUCER_BIG, PLAY_MODE_LOOP, false);
}

void SoundPlayer::playSaucerSmall() const {
	soundMaster.play(SOUND_SAUCER_SMALL, PLAY_MODE_LOOP, false);
}

void SoundPlayer::playThrust() const {
	// Currently, SOUND_THRUST cannot be loaded via WaveLoader
	// => Instead, we use SOUND_BEAT1 temporarily
	soundMaster.play(SOUND_THRUST, PLAY_MODE_LOOP, false);
}

void SoundPlayer::stopThrust() const {
	soundMaster.stop(SOUND_THRUST);
}

void SoundPlayer::stopBackgroundSound() {
	this->isBackgroundSoundPlaying = false;
}

void SoundPlayer::stopSaucerBig() const {
	soundMaster.stop(SOUND_SAUCER_BIG);
}

void SoundPlayer::stopSaucerSmall() const {
	soundMaster.stop(SOUND_SAUCER_SMALL);
}
