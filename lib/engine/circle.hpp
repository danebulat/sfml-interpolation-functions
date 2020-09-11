#ifndef Circle_Hpp
#define Circle_Hpp

#include <SFML/Graphics.hpp>
#include "engine/tween.hpp"

using namespace sf;
using namespace std;

class Circle {
private:
	CircleShape m_sprite;
	Vector2f    m_position;

	static const float DEFAULT_POSITION;
	static const float DEFAULT_RADIUS;
	static const float DEFAULT_LINE_THICKNESS;
	static const float MOVE_SPEED;

	Tween* m_tweenA;
	Tween* m_tweenB;

	bool m_active;
	bool m_moveLeft;
	bool m_moveRight;
	bool m_moveUp;
	bool m_moveDown;

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
	sf::Vector2f getCenter() const;

	void update(float dt);
	void draw(RenderWindow& window);

	// Movement controls
	void moveUp(bool b);
	void moveDown(bool b);
	void moveLeft(bool b);
	void moveRight(bool b);

	bool movingUp() const;
	bool movingDown() const;
	bool movingLeft() const;
	bool movingRight() const;

	void stopMovement();
	void handleInput(sf::Event& event);
	void setActive(bool b);
	bool isActive() const;

	// Tween API
	void createDemoTween(InterpFunc func=InterpFunc::QuartEaseOut);
	void startStopTweenToggle();
	void startTween();
	void stopTween();
	void resetTween(bool start);

	// Dynamic tweens (custom animations for class)
	void spawnInTween();
	void spawnOutTween();
};

#endif