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
Tween::Tween(float* property, float startValue, float targetValue, float duration,
			 InterpFunc function)
		: m_function(function)
		, m_startValue(startValue)
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

void Tween::stop() {
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
		float t = m_elapsedTime;
		float b = m_startValue;
		float c = m_changeValue;
		float d = m_duration;

		switch (m_function) {
		case InterpFunc::Linear:
			(*m_property) = Interpolate::linear(t, b, c, d);
			break;

		case InterpFunc::QuadEaseIn:
			(*m_property) = Interpolate::easeInQuad(t, b, c, d);
			break;

		case InterpFunc::QuadEaseOut:
			(*m_property) = Interpolate::easeOutQuad(t, b, c, d);
			break;

		case InterpFunc::QuadEaseInOut:
			(*m_property) = Interpolate::easeInOutQuad(t, b, c, d);
			break;

		case InterpFunc::CubicEaseIn:
			(*m_property) = Interpolate::easeInCubic(t, b, c, d);
			break;

		case InterpFunc::CubicEaseOut:
			(*m_property) = Interpolate::easeOutCubic(t, b, c, d);
			break;

		case InterpFunc::CubicEaseInOut:
			(*m_property) = Interpolate::easeInOutCubic(t, b, c, d);
			break;

		case InterpFunc::QuartEaseIn:
			(*m_property) = Interpolate::easeInQuart(t, b, c, d);
			break;

		case InterpFunc::QuartEaseOut:
			(*m_property) = Interpolate::easeOutQuart(t, b, c, d);
			break;

		case InterpFunc::QuartEaseInOut:
			(*m_property) = Interpolate::easeInOutQuart(t, b, c, d);
			break;

		case InterpFunc::QuintEaseIn:
			(*m_property) = Interpolate::easeInQuint(t, b, c, d);
			break;

		case InterpFunc::QuintEaseOut:
			(*m_property) = Interpolate::easeOutQuint(t, b, c, d);
			break;

		case InterpFunc::QuintEaseInOut:
			(*m_property) = Interpolate::easeInOutQuint(t, b, c, d);
			break;

		case InterpFunc::SineEaseIn:
			(*m_property) = Interpolate::easeInSine(t, b, c, d);
			break;

		case InterpFunc::SineEaseOut:
			(*m_property) = Interpolate::easeOutSine(t, b, c, d);
			break;

		case InterpFunc::SineEaseInOut:
			(*m_property) = Interpolate::easeInOutSine(t, b, c, d);
			break;

		case InterpFunc::ExpoEaseIn:
			(*m_property) = Interpolate::easeInExpo(t, b, c, d);
			break;

		case InterpFunc::ExpoEaseOut:
			(*m_property) = Interpolate::easeOutExpo(t, b, c, d);
			break;

		case InterpFunc::ExpoEaseInOut:
			(*m_property) = Interpolate::easeInOutExpo(t, b, c, d);
			break;

		case InterpFunc::CircEaseIn:
			(*m_property) = Interpolate::easeInCirc(t, b, c, d);
			break;

		case InterpFunc::CircEaseOut:
			(*m_property) = Interpolate::easeOutCirc(t, b, c, d);
			break;

		case InterpFunc::CircEaseInOut:
			(*m_property) = Interpolate::easeInOutCirc(t, b, c, d);
			break;

		case InterpFunc::BackEaseIn:
			(*m_property) = Interpolate::easeInBack(t, b, c, d);
			break;

		case InterpFunc::BackEaseOut:
			(*m_property) = Interpolate::easeOutBack(t, b, c, d);
			break;

		case InterpFunc::BackEaseInOut:
			(*m_property) = Interpolate::easeInOutBack(t, b, c, d);
			break;

		case InterpFunc::ElasticEaseIn:
			(*m_property) = Interpolate::easeInElastic(t, b, c, d);
			break;

		case InterpFunc::ElasticEaseOut:
			(*m_property) = Interpolate::easeOutElastic(t, b, c, d);
			break;

		case InterpFunc::ElasticEaseInOut:
			(*m_property) = Interpolate::easeInOutElastic(t, b, c, d);
			break;

		case InterpFunc::BounceEaseIn:
			(*m_property) = Interpolate::easeInBounce(t, b, c, d);
			break;

		case InterpFunc::BounceEaseOut:
			(*m_property) = Interpolate::easeOutBounce(t, b, c, d);
			break;

		case InterpFunc::BounceEaseInOut:
			(*m_property) = Interpolate::easeInOutBounce(t, b, c, d);
			break;

		default:
			(*m_property) = Interpolate::easeOutQuart(t, b, c, d);
			break;
		}
	}
}
