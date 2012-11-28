#pragma once
#include"SDL.h"
#include"SDL_ttf.h"

class world;

class ball
{
private:
	Uint16 m_diameter;
	int32_t m_x;
	int32_t m_y;
	Uint32 m_speed;
	int32_t m_direction[2];
	world *m_world;

public:
	ball(Uint16 x, Uint16 y, Uint16 diameter, world *w) : m_diameter(diameter), 
																	m_x(x),
																	m_y(y),
																	m_speed(0),
																	m_world(w) 
	{
		m_direction[0] = 1;
		m_direction[1] = 1;
	}
	
	void update(Uint32 time);
	void render();

	int32_t X() { return m_x; }
	int32_t Y() { return m_y; }
	Uint16 L() { return m_diameter; }
	void reverse_x() { m_direction[0] = -m_direction[0]; }
	void reverse_y() { m_direction[1] = -m_direction[1]; }

private:
	void move(Uint32 time);
	void inc_speed(Uint32 amount) { m_speed += amount; }
	void dec_speed(Uint32 amount) { m_speed -= amount; }
	void grow(Uint32 amount) { if(m_diameter<50) m_diameter += amount; }
	void shrink(Uint32 amount) { if(m_diameter>1) m_diameter -= amount; }
};
