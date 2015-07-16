/*
 * MusicPlayer.h
 *
 *  Created on: 14-apr.-2015
 *      Author: Thomas
 */

#ifndef GAME_MUSICPLAYER_H_
#define GAME_MUSICPLAYER_H_

#include "Music.h"

namespace CCG
{
	/*
	 * Abstract class for the music player
	 */
	class MusicPlayer
	{
		public:
			virtual ~MusicPlayer(void);

			/*
			 * Clear the music stack and set the current track
			 */
			virtual void setMusic(Music* music) = 0;

			/*
			 * Pause current track and play new track
			 */
			virtual void pushMusic(Music* music) = 0;

			/*
			 * Stop current track and play previous track of stack if available
			 */
			virtual void popMusic(void) = 0;

			/*
			 * Clear the playlist
			 */
			virtual void releasePlaylist(void) = 0;

			/*
			 * Start music
			 * @param gradually Start the music with a fade-in
			 */
			virtual void startMusic(bool gradually) = 0;

			/*
			 * Continue a paused track
			 */
			virtual void resumeMusic(void) = 0;

			/*
			 * Pause a playing track
			 */
			virtual void pauseMusic(void) = 0;

			/*
			 * Restart the track from the beginning
			 */
			virtual void rewindMusic(void) = 0;

			/*
			 * Stop a playing track
			 * @param gradually Stop the music with a fade-out
			 */
			virtual void stopMusic(bool gradually) = 0;

			/*
			 * Pause all playing sound-effects
			 */
			virtual void pauseSFXSounds(void) = 0;

			/*
			 * Resume all paused sound-effects
			 */
			virtual void resumeSFXSounds(void) = 0;

			/*
			 * Set the volume of the background music
			 * @param volume The new set volume for the music [0 - 100]
			 */
			virtual void setMusicVolume(int volume) = 0;

			/*
			 * Set the volume of the sound-effects
			 * @param volume The new set volume for the sound-effects [0 - 100]
			 */
			virtual void setSFXVolume(int volume) = 0;

			/*
			 * Set the fade-out time when gradually fading-out
			 * @param fadeOut Fade-out time in ms
			 */
			virtual void setFadeOutTime(int fadeOut) = 0;

			/*
			 * Set the fade-in time when gradually fading-in
			 * @param fadeIn Fade-in time in ms
			 */
			virtual void setFadeInTime(int fadeIn) = 0;

			/*
			 * Get the music volume
			 * @return Get the set volume [0 - 100]
			 */
			virtual int getMusicVolume(void) = 0;

			/*
			 * Get the sound-effect volume
			 * @return Get the set volume [0 - 100]
			 */
			virtual int getSFXVolume(void) = 0;

			/*
			 * Get the fade-out time
			 * @return Fade-out time in ms
			 */
			virtual int getFadeOutTime(void) = 0;

			/*
			 * Get the fade-in time
			 * @return Fade-in time in ms
			 */
			virtual int getFadeInTime(void) = 0;

		protected:
			MusicPlayer(void);
	};
}

#endif /* GAME_MUSICPLAYER_H_ */
