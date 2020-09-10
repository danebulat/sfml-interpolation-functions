#include "engine/circle.hpp"
#include "engine/utils.hpp"

/*------------------------------------------------------------
  Static member initialisation
  ------------------------------------------------------------ */

const float Circle::DEFAULT_POSITION = 10.0f;
const float Circle::DEFAULT_LINE_THICKNESS = 1.0f;
const float Circle::DEFAULT_RADIUS = 10.0f;

/*------------------------------------------------------------
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

	m_tweenA = nullptr;
	m_tweenB = nullptr;
	m_position = position;

	m_sprite.setPosition(position);
	m_sprite.setFillColor(color);
	m_sprite.setRadius(radius);
	m_sprite.setOutlineThickness(1.f);
	m_sprite.setOutlineColor(Color::White);
}

Circle::~Circle() {
	SafeDelete(m_tweenA);
	SafeDelete(m_tweenB);
}

/*------------------------------------------------------------
  Initialisation
  ------------------------------------------------------------ */

void Circle::initialise() {
	m_sprite.setPosition(DEFAULT_POSITION, DEFAULT_POSITION);
	m_sprite.setFillColor(Color::Yellow);
	m_sprite.setOutlineThickness(DEFAULT_LINE_THICKNESS);
	m_sprite.setOutlineColor(Color::White);
	m_sprite.setRadius(DEFAULT_RADIUS);

	m_tweenA = nullptr;
	m_position = m_sprite.getPosition();
}

/*------------------------------------------------------------
  Tween API
  ------------------------------------------------------------ */

void Circle::createDemoTween(InterpFunc func) {
	m_tweenA = new Tween(&m_position.x, 30.f, (800.f-130.f), 5.f);
}

// Starts or stops the tween by inverting its animation flag
void Circle::startStopTweenToggle() {
	if (!m_tweenA->m_isAnimating) {
		m_tweenA->start();
	}
	else {
		m_tweenA->stop();
	}
}

void Circle::startTween() {
	m_tweenA->start();
}

// Stops the tween at its current position
void Circle::stopTween() {
	m_tweenA->stop();
}

// Moves object to start position; pass bool for the animation flag
// NOTE: Return pointer to tween for chaining calls
void Circle::resetTween(bool start) {
	start ? m_tweenA->resetAndPlay() : m_tweenA->resetAndStop();
}


void Circle::spawnInTween() {

	// We will animate the circle back to its original position.
	// We shall delete the current tween if it exists because we don't
	// want it  to interfere with our new tween.

	if (m_tweenA != nullptr) {
		m_tweenA->stop();
		SafeDelete(m_tweenA);
	}

	float target  = 30.0f;
	float current = m_position.x;

	m_tweenA = new Tween(&m_position.x, current, target, .5f, InterpFunc::QuintEaseOut);
	m_tweenA->start();
}

void Circle::spawnOutTween() {
	if (m_tweenA != nullptr) {
		m_tweenA->stop();
		SafeDelete(m_tweenA);
	}

	float target = 670.f;
	float current = m_position.x;

	m_tweenA = new Tween(&m_position.x, current, target, 2.f, InterpFunc::BounceEaseOut);
	m_tweenA->start();
}

/*------------------------------------------------------------
  Accessors
  ------------------------------------------------------------*/

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

/*------------------------------------------------------------
  Update and draw functions
  ------------------------------------------------------------ */

void Circle::update(float dt) {
	m_tweenA->update(dt);				// update position
	m_sprite.setPosition(m_position);	// apply position
}

void Circle::draw(RenderWindow& window) {
	window.draw(m_sprite);
}