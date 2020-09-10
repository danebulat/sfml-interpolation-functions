#include "engine/circle.hpp"

/* ------------------------------------------------------------
   Static member initialisation
   ------------------------------------------------------------ */

const float Circle::DEFAULT_POSITION = 10.0f;
const float Circle::DEFAULT_LINE_THICKNESS = 1.0f;
const float Circle::DEFAULT_RADIUS = 10.0f;

/* ------------------------------------------------------------
   Constructors
   ------------------------------------------------------------ */

Circle::Circle() {
	initialise();
}

Circle::Circle(const Color& color) {
	initialise();
	m_sprite.setFillColor(color);
}

Circle::Circle(const Vector2f& position,
	   const Color& color,
	   const float radius) {
	m_sprite.setPosition(position);
	m_sprite.setFillColor(color);
	m_sprite.setRadius(radius);
	m_sprite.setOutlineThickness(1.f);
	m_sprite.setOutlineColor(Color::White);
}

Circle::~Circle()
{}

/* ------------------------------------------------------------
   Initialisation
   ------------------------------------------------------------ */

void Circle::initialise() {
	m_sprite.setPosition(DEFAULT_POSITION, DEFAULT_POSITION);
	m_sprite.setFillColor(Color::Yellow);
	m_sprite.setOutlineThickness(DEFAULT_LINE_THICKNESS);
	m_sprite.setOutlineColor(Color::White);
	m_sprite.setRadius(DEFAULT_RADIUS);
}

/* ------------------------------------------------------------
   Accessors
   ------------------------------------------------------------ */

FloatRect Circle::getBoundingBox() {
	return m_sprite.getGlobalBounds();
}

void Circle::setPosition(const Vector2f& position) {
	m_position = position;
	m_sprite.setPosition(position);
}

void Circle::setPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;
	m_sprite.setPosition(x, y);
}

/* ------------------------------------------------------------
   Update and draw functions
   ------------------------------------------------------------ */

void Circle::update(float fps)
{}

void Circle::draw(RenderWindow& window) {
	window.draw(m_sprite);
}