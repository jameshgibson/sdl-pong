#pragma once
#include<map>
#include"SDL.h"

/*
	Keep track of keyboard presses. Storing keys that are held down.
*/
class input
{
private:
	std::map<SDLKey, SDL_keysym> m_active_keys;
	std::map<SDLKey, SDL_keysym> m_pressed_keys;
public:
	void handle_keydown(const SDL_keysym &down)
	{
		m_active_keys.insert(std::pair<SDLKey, SDL_keysym>(down.sym,down));
		m_pressed_keys.insert(std::pair<SDLKey, SDL_keysym>(down.sym,down));
	}

	void handle_keyup(const SDL_keysym &up)
	{
		m_active_keys.erase(up.sym);
	}

	void reset_pressed()
	{
		m_pressed_keys.clear();
	}

	bool is_keypressed(const SDLKey &key, const SDLMod &mod = KMOD_NONE)
	{
		std::map<SDLKey,SDL_keysym>::const_iterator it = m_pressed_keys.begin();
		for(; it != m_pressed_keys.end(); it++)
		{
			SDLKey k = it->first;
			SDLMod m = it->second.mod;
			if(it->first==key && (it->second.mod==mod || it->second.mod==KMOD_NUM || it->second.mod==KMOD_CAPS))
				return true;
		}
		return false;
	}
	
	bool is_keydown(const SDLKey &key, const SDLMod &mod = KMOD_NONE)
	{
		std::map<SDLKey,SDL_keysym>::const_iterator it = m_active_keys.begin();
		for(; it != m_active_keys.end(); it++)
		{
			if(it->first==key && (it->second.mod==mod || it->second.mod==KMOD_NUM || it->second.mod==KMOD_CAPS))
				return true;
		}
		return false;
	}
};
