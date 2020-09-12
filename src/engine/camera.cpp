#include "engine/camera.hpp"
#include "engine/utils.hpp"

using namespace sf;

/** Initialises a camera with default values.
*
* Disables clamping to the background size and provides
* default interpolation and duration values for the tweens.
*/
Camera::Camera() {
	initDefault();
}

/** Initialises a camera for clamping to a background.
*
* Initialises data members to enable clamping the camera's
* position to the background container. Default interpolation
* and duration values are initialised.
*/
Camera::Camera(const Vector2f& position,
			   const Vector2u& backgroundSize,
			   const Vector2f& resolution,
			   bool clamp=true)
			   	: m_position(position)
				, m_backgroundSize(backgroundSize)
				, m_clampToBackground(clamp)
				, m_tweenX(nullptr)
				, m_tweenY(nullptr) {

	calculateMinMaxPos(backgroundSize, resolution);

	m_interpolation = InterpFunc::QuartEaseOut;
	m_duration = 1.f;
	m_tweenXActive = false;
	m_tweenYActive = false;
}

/** Deallocates camera's tween objects.
*/
Camera::~Camera() {
	SafeDelete(m_tweenX);
	SafeDelete(m_tweenY);
}

void Camera::initDefault() {
	m_position.x = 0.f;
	m_position.y = 0.f;
	m_backgroundSize.x = 0.f;
	m_backgroundSize.y = 0.f;

	m_clampToBackground = false;
	m_minX = 0.f;
	m_minY = 0.f;
	m_maxX = 0.f;
	m_maxY = 0.f;

	m_interpolation = InterpFunc::QuartEaseOut;
	m_duration = 1.f;
	m_tweenX = nullptr;
	m_tweenY = nullptr;
	m_tweenXActive = false;
	m_tweenYActive = false;
}

void Camera::clampPosition(const Vector2f& pos) {
	if (pos.x < m_minX)
		m_position.x = m_minX;
	else if (pos.x > m_maxX)
		m_position.x = m_maxX;
	else
		m_position.x = pos.x;

	if (pos.y < m_minY)
		m_position.y = m_minY;
	else if (pos.y < m_maxY)
		m_position.y = m_maxY;
	else
		m_position.y = pos.y;
}

void Camera::calculateMinMaxPos(const sf::Vector2u& backgroundSize,
						const sf::Vector2f& resolution) {

	m_minX = resolution.x * .5f;
	m_minY = resolution.y * .5f;

	m_maxX = ((float)backgroundSize.x) - (resolution.x * .5f);
	m_maxY = ((float)backgroundSize.y) - (resolution.y * .5f);
}

void Camera::animateTo(const Vector2f& target) {

	// Animate only if there isn't an animation already playing
	if (m_tweenXActive || m_tweenYActive)
		return;

	spawnTweenX(target.x);
	spawnTweenY(target.y);
}

void Camera::spawnTweenX(float targetX) {
	if (targetX < m_minX) targetX = m_minX;
	if (targetX > m_maxX) targetX = m_maxX;

	m_tweenX = new Tween(&m_position.x, m_position.x, targetX, m_duration, m_interpolation);
	m_tweenX->start();
	m_tweenXActive = true;
}

void Camera::spawnTweenY(float targetY) {
	if (targetY < m_minY) targetY = m_minY;
	if (targetY > m_maxY) targetY = m_maxY;

	m_tweenY = new Tween(&m_position.y, m_position.y, targetY, m_duration, m_interpolation);
	m_tweenY->start();
	m_tweenYActive = true;
}

void Camera::clampTo(const sf::Vector2u& backgroundSize,
		     const sf::Vector2f& resolution) {

	m_clampToBackground = true;
	calculateMinMaxPos(backgroundSize, resolution);
}

// ----------------------------------------------------------------------
// Accessors
// ----------------------------------------------------------------------

void Camera::setInterpolation(InterpFunc interp) {
	m_interpolation = interp;
}

Vector2f Camera::getPosition() const {
	return m_position;
}

void Camera::setPosition(const Vector2f& pos) {
	if (m_clampToBackground) {
		clampPosition(pos);
	}
	else {
		m_position = pos;
	}
}

float Camera::getDuration() const {
	return m_duration;
}

void Camera::setDuration(float duration) {
	m_duration = duration;
}

// ----------------------------------------------------------------------
// Update
// ----------------------------------------------------------------------

bool Camera::isAnimating() const {
	return (m_tweenXActive || m_tweenYActive);
}

void Camera::update(float dt, const Circle& player) {

	// Deallocate tweens if it has finished animating, otherwise call update()
	if (m_tweenXActive && (!m_tweenX->m_isAnimating)) {
		m_tweenXActive = false;
		SafeDelete(m_tweenX);
	}
	else if (m_tweenXActive) {
		m_tweenX->update(dt);
	}

	if (m_tweenYActive && (!m_tweenY->m_isAnimating)) {
		m_tweenYActive = false;
		SafeDelete(m_tweenY);
	}
	else if (m_tweenYActive) {
		m_tweenY->update(dt);
	}

	// Camera position may be out of bounds of the background
	if (m_clampToBackground) {
		if (m_tweenXActive || m_tweenYActive) {

			float cameraX = 0.f;
            float cameraY = 0.f;

			// Clamp X if interpolated X position is outside of background
			if (m_position.x < m_minX)
				cameraX = m_minX;
			else if (m_position.x > m_maxX)
				cameraX = m_maxX;
			else
				cameraX = m_position.x;

			// Clamp Y if interpolated Y position is outside of background
			if (m_position.y < m_minY)
				cameraY = m_minY;
			else if (m_position.y > m_maxY)
				cameraY = m_maxY;
			else
				cameraY = m_position.y;
		}
	}

	// Update camera position based on the player if it's not animating
	float playerX = player.getCenter().x;
	float playerY = player.getCenter().y;

	bool clampOnMinX = false;
	bool clampOnMaxX = false;
	bool clampOnMinY = false;
	bool clampOnMaxY = false;

	if (playerX < m_minX)      clampOnMinX = true;
	else if (playerX > m_maxX) clampOnMaxX = true;

	if (playerY < m_minY)	   clampOnMinY = true;
	else if (playerY > m_maxY) clampOnMaxY = true;

	if (clampOnMinX)      m_position.x = m_minX;
	else if (clampOnMaxX) m_position.x = m_maxX;
	else 				  m_position.x = playerX;

	if (clampOnMinY) 	  m_position.y = m_minY;
	else if (clampOnMaxY) m_position.y = m_maxY;
	else 				  m_position.y = playerY;
}