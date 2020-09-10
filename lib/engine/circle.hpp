#ifndef Circle_Hpp
#define Circle_Hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Circle {
private:
	CircleShape m_sprite;
	Vector2f    m_position;

	static const float DEFAULT_POSITION;
	static const float DEFAULT_RADIUS;
	static const float DEFAULT_LINE_THICKNESS;

private:
	void initialise();

public:
	Circle();
	Circle(const Color& color);
	Circle(const Vector2f& position,
		   const Color& color,
		   const float radius);
	~Circle();

	FloatRect getBoundingBox();

	void setPosition(const Vector2f& position);
	void setPosition(float x, float y);

	void update(float fps);
	void draw(RenderWindow& window);
};

#endif