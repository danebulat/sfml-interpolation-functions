#include "engine/tween.hpp"
#include "engine/interpolate.hpp"

// TODO: Initialise enum to choose interpolation
// function type.

using namespace animation;

Tween::Tween()
		: m_startValue(0.f)
		, m_targetValue(0.f)
		, m_changeValue(0.f)
		, m_duration(0.f)
		, m_elapsedTime(0.f)
		, m_isAnimating(false) {
	m_property = nullptr;
}

// Custom constructor to initialise data members with custom values.
Tween::Tween(float* property, float startValue, float targetValue, float duration)
		: m_startValue(startValue)
		, m_targetValue(targetValue)
		, m_changeValue(targetValue-startValue)
		, m_duration(duration)
		, m_elapsedTime(0.f)
		, m_isAnimating(false) {
	m_property = property;
}

Tween::~Tween() {
	// The animated property pointer is pointing to a
	// stack variable or dynamically allocated data that
	// will be cleaned up in it's respectable class.
}

void Tween::resetAndStop() {
	m_elapsedTime = 0.f;
	(*m_property) = m_startValue;
	m_isAnimating = false;
}

void Tween::resetAndPlay() {
	m_elapsedTime = 0.f;
	(*m_property) = m_startValue;
	m_isAnimating = true;
}

void Tween::start() {
	m_isAnimating = true;
}

void Tween::stop()
{
	m_isAnimating = false;
}

void Tween::update(float dt) {
	// Update the tween if it's animating
	if (m_isAnimating) {

		// Update the elapsed time with delta-time
		m_elapsedTime += dt;

		// Stop the tween if it's ran its duration
		if (m_elapsedTime >= m_duration) {
			(*m_property) = m_targetValue;
			m_elapsedTime = 0.f;
			m_isAnimating = false;
			return;
		}

		// Otherwise, continue the animation
		float interpolatedValue = Interpolate::easeOutBounce(
			m_elapsedTime,
			m_startValue,
			m_changeValue,
			m_duration);

		(*m_property) = interpolatedValue;
	}
}

