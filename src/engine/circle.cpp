#include "engine/utils.hpp"
#include "engine/circle.hpp"

/*------------------------------------------------------------
  Static member initialisation
  ------------------------------------------------------------ */

const float Circle::DEFAULT_POSITION = 10.0f;
const float Circle::DEFAULT_LINE_THICKNESS = 1.0f;
const float Circle::DEFAULT_RADIUS = 10.0f;
const float Circle::MOVE_SPEED = 250.0f;

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

	m_active = false;
	m_tweenA = nullptr;
	m_tweenB = nullptr;
	m_position = position;

	m_sprite.setPosition(position);
	m_sprite.setFillColor(color);
	m_sprite.setRadius(radius);
	m_sprite.setOutlineThickness(1.f);
	m_sprite.setOutlineColor(Color::White);

	stopMovement();
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

	m_active = false;
	m_tweenA = nullptr;
	m_tweenB = nullptr;
	m_position = m_sprite.getPosition();

	stopMovement();
}

void Circle::stopMovement() {
	m_moveLeft = false;
	m_moveRight = false;
	m_moveUp = false;
	m_moveDown = false;
}

void Circle::handleInput(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::W) {
			moveUp(true);
		}

		if (event.key.code == sf::Keyboard::S) {
			moveDown(true);
		}

		if (event.key.code == sf::Keyboard::A) {
			moveLeft(true);
		}

		if (event.key.code == sf::Keyboard::D) {
			moveRight(true);
		}
	}

	if (event.type == sf::Event::KeyReleased) {

		if (event.key.code == sf::Keyboard::W) {
			moveUp(false);
		}

		if (event.key.code == sf::Keyboard::S) {
			moveDown(false);
		}

		if (event.key.code == sf::Keyboard::A) {
			moveLeft(false);
		}

		if (event.key.code == sf::Keyboard::D) {
			moveRight(false);
		}
	}
}

void Circle::setActive(bool b) {
	m_active = b;
}

bool Circle::isActive() const {
	return m_active;
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

sf::Vector2f Circle::getCenter() const {
	sf::FloatRect localBounds = m_sprite.getLocalBounds();
	float halfWidth = localBounds.width * .5f;
	float halfHeight = localBounds.height * .5f;
	return Vector2f(m_position.x + halfWidth, m_position.y + halfHeight);
}

void Circle::moveUp(bool b)    { m_moveUp = b; }
void Circle::moveDown(bool b)  { m_moveDown = b; }
void Circle::moveLeft(bool b)  { m_moveLeft = b; }
void Circle::moveRight(bool b) { m_moveRight = b; }

bool Circle::movingUp()    const { return m_moveUp; }
bool Circle::movingDown()  const { return m_moveDown; };
bool Circle::movingLeft()  const { return m_moveLeft; };
bool Circle::movingRight() const { return m_moveRight; };

/*------------------------------------------------------------
  Update and draw functions
  ------------------------------------------------------------ */

void Circle::update(float dt) {
	if (m_tweenA != nullptr) {
		m_tweenA->update(dt); 			// update position
	}

	if (m_active) {
		if (m_moveUp)    m_position.y -= MOVE_SPEED * dt;
		if (m_moveDown)  m_position.y += MOVE_SPEED * dt;
		if (m_moveLeft)  m_position.x -= MOVE_SPEED * dt;
		if (m_moveRight) m_position.x += MOVE_SPEED * dt;
	}

	m_sprite.setPosition(m_position);	// apply position
}

void Circle::draw(RenderWindow& window) {
	window.draw(m_sprite);
}