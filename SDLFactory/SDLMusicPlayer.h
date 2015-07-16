/*
 * SDLMusicPlayer.h
 *
 *  Created on: 14-apr.-2015
 *      Author: Thomas
 */

#ifndef SDLFACTORY_SDLMUSICPLAYER_H_
#define SDLFACTORY_SDLMUSICPLAYER_H_

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "SDLMusic.h"
#include "../Game/MusicPlayer.h"
#include "../Game/Music.h"

namespace CCG_SDL
{
	/*
	 * SDL implementation of the music player class
	 */
	class SDLMusicPlayer : public CCG::MusicPlayer
	{
		public:
			SDLMusicPlayer(void);
			~SDLMusicPlayer(void);

			void setMusic(CCG::Music* music);
			void pushMusic(CCG::Music* music);
			void popMusic(void);

			void releasePlaylist(void);

			void startMusic(bool gradually);
			void resumeMusic(void);
			void pauseMusic(void);
			void rewindMusic(void);
			void stopMusic(bool gradually);

			void pauseSFXSounds(void);
			void resumeSFXSounds(void);

			void setMusicVolume(int volume);
			void setSFXVolume(int volume);
			void setFadeOutTime(int fadeOut);
			void setFadeInTime(int fadeIn);

			int getMusicVolume(void);
			int getSFXVolume(void);
			int getFadeOutTime(void);
			int getFadeInTime(void);

		private:
			std::vector<SDLMusic*>* playList;
			bool mixTrack, nextMusicGradually;
			int fadeIn, fadeOut;
	};
}

#endif /* SDLFACTORY_SDLMUSICPLAYER_H_ */
