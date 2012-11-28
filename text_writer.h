#pragma once
#include<SDL_ttf.h>
#include<string>
#include<sstream>
#include<iostream>

class text_writer
{
 private:
  SDL_Surface *m_screen;
  TTF_Font *m_font;
  SDL_Color m_fg_color;
  SDL_Color m_bg_color;

 public:
 text_writer(SDL_Surface *screen) : m_screen(screen)
  {
    m_font = TTF_OpenFont("fonts/Cyen.ttf", 12);
    if(m_font == NULL)
      {
	std::cerr << "Failed to open the font file" << std::endl;
	exit(-1);
      }
    m_bg_color.r = m_bg_color.b = m_bg_color.g = 0xff;
    m_fg_color.r = m_fg_color.b = m_fg_color.g = 0;
  }

  void set_font(TTF_Font *font)
  {
    m_font = font;
  }

  void set_bg_color(const SDL_Color &color)
  {
    m_bg_color = color;
  }

  void set_fg_color(const SDL_Color &color)
  {
    m_fg_color = color;
  }

  void draw_text(Uint16 x, Uint16 y, const char *msg)
  {
    SDL_Rect dst;
    dst.x = x; dst.y = y;
    SDL_Surface *text_surface = TTF_RenderText_Shaded(m_font,msg, m_fg_color, m_bg_color);
    SDL_BlitSurface(text_surface,NULL,m_screen,&dst);
    SDL_FreeSurface(text_surface);
  }

  void draw_text(Uint16 x, Uint16 y, std::string msg)
  {
    SDL_Rect dst;
    dst.x = x; dst.y = y;
    SDL_Surface *text_surface = TTF_RenderText_Shaded(m_font,msg.c_str(), m_fg_color, m_bg_color);
    SDL_BlitSurface(text_surface,NULL,m_screen,&dst);
    SDL_FreeSurface(text_surface);
  }

  template<class T>
    void draw_text(Uint16 x, Uint16 y, T msg)
    {
      SDL_Rect dst;
      dst.x = x; dst.y = y;
      std::stringstream ss;
      ss << msg;
      SDL_Surface *text_surface = TTF_RenderText_Shaded(m_font,ss.str().c_str(), m_fg_color, m_bg_color);
      SDL_BlitSurface(text_surface,NULL,m_screen,&dst);
      SDL_FreeSurface(text_surface);
    }
};
