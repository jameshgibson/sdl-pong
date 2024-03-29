#pragma once
#include<SDL.h>

class world;

class paddel
{
 private:
  int32_t m_x;
  int32_t m_y;
  Uint16 m_width;
  Uint16 m_height;
  Uint32 m_speed;
  SDLKey m_key_up;
  SDLKey m_key_down;
  world *m_world;

 public:
 paddel(Uint16 x, Uint16 y, Uint16 w, Uint16 h, world *wd) : m_x(x), m_y(y), 
    m_width(w), 
    m_height(h), 
    m_speed(2),
    m_key_up(SDLK_UP),
    m_key_down(SDLK_DOWN),
    m_world(wd)
    {}

  void update(Uint32 time);
  void render();

  int32_t X() { return m_x; }
  int32_t Y() { return m_y; }
  Uint16 W() { return m_width; }
  Uint16 H() { return m_height; }


 private:
  friend class world;

  void bind_up(const SDLKey &k) { m_key_up = k; }
  void bind_down(const SDLKey &k) { m_key_down = k; }
};
