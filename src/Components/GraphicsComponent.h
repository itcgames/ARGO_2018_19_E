#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include "Components.h"
#include <iostream>

using namespace std;

class GraphicComponent : public Component
{
public:
	GraphicComponent(string path, int w, int h) : m_path(path), m_w(w), m_h(h) {}

	string getTexturePath() { return m_path; }
	void setHealth(std::string path) { this->m_path = path; }

	int getX() { return m_x; }
	void setX(int x) { this->m_x = x; }

	int getY() { return m_y; }
	void setY(int y) { this->m_y = y; }

	int getW() { return m_w; }
	void setW(int w) { this->m_w = w; }

	int getH() { return m_h; }
	void setH(int h) { this->m_h = h; }

	std::string m_tag = "GRAPHIC";

	std::string getType() { return m_tag; }

private:
	string m_path;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
};
#endif // !GRAPHICCOMPONENT_H
