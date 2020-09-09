#ifndef Interpolate_Hpp
#define Interpolate_Hpp

#include <cmath>

namespace animation {

	/**
    Interpolation functions implemented for all the standard easing
	functions documented here:
	https://easings.net/
	*/

	class Interpolate {
	private:
		static const float f_PI;

	public:
		Interpolate() = delete;
		Interpolate(const Interpolate&) = delete;
		Interpolate& operator= (const Interpolate&) = delete;

		// linear - no easing, no acceleration
		static float linear(float t, float b, float c, float d) {
			return c * t/d + b;
		}

		// quadratic easing in - accelerating from zero velocity
		static float easeInQuad(float t, float b, float c, float d) {
			t /= d;
			return c*t*t + b;
		}

		static float easeInQuad(float t) {
			return t*t;
		}

		// quadratic easing out - decelerating to zero velocity
		static float easeOutQuad(float t, float b, float c, float d) {
			t /= d;
			return -c * t*(t-2.f) + b;
		}

		static float easeOutQuad(float t) {
			return 1.f - (1.f - t) * (1.f - t);
		}

		// quadratic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutQuad(float t, float b, float c, float d) {
			t /= d/2.f;
			if (t < 1.f)
				return c/2.f*t*t + b;
			t--;
			return -c/2.f * (t*(t-2.f) - 1.f) + b;
		}

		static float easeInOutQuad(float t) {
			return t < 0.5f ?
				2.f * t * t :
				1.f - pow(-2.f * t + 2.f, 2.f) / 2.f;
		}

		// cubic easing in - accelerating from zero velocity
		static float easeInCubic(float t, float b, float c, float d) {
			t /= d;
			return c*t*t*t + b;
		}

		static float easeInCubic(float t) {
			return t * t * t;
		}

		// cubic easing out - decelerating to zero velocity
		static float easeOutCubic(float t, float b, float c, float d) {
			t /= d;
			t--;
			return c*(t*t*t + 1.f) + b;
		}

		static float easeOutCubic(float t) {
			return 1.f - std::powf(1.f - t, 3);
		}

		// cubic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutCubic(float t, float b, float c, float d) {
			t /= d/2.f;
			if (t < 1.f)
				return c/2.f*t*t*t + b;
			t -= 2.f;
			return c/2*(t*t*t + 2.f) + b;
		}

		static float easeInOutCubic(float t) {
			return t < 0.5f ?
				4.f * t * t * t :
				1.f - std::powf(-2.f * t + 2.f, 3.f) / 2.f;
		}

		// quartic easing in - accelerating from zero velocity
		static float easeInQuart(float t, float b, float c, float d) {
			t /= d;
			return c*t*t*t*t + b;
		}

		static float easeInQuart(float t) {
			return t * t * t * t;
		}

		// quartic easing out - decelerating to zero velocity
		static float easeOutQuart(float t, float b, float c, float d) {
			t /= d;
			t--;
			return -c * (t*t*t*t - 1.f) + b;
		}

		static float easeOutQuart(float t) {
			return 1.f - std::powf(1 - t, 4.f);
		}

		// quartic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutQuart(float t, float b, float c, float d) {
			t /= d/2.f;
			if (t < 1.f) return c/2.f*t*t*t*t + b;
			t -= 2.f;
			return -c/2.f * (t*t*t*t - 2.f) + b;
		}

		static float easeInOutQuard(float t) {
			return t < 0.5f ?
				8.f * t * t * t * t :
				1.f - std::powf(-2.f * t + 2.f, 4.f) / 2.f;
		}

		// quintic easing in - accelerating from zero velocity
		static float easeInQuint(float t, float b, float c, float d) {
			t /= d;
			return c*t*t*t*t*t + b;
		}

		static float easeInQuint(float t) {
			return t * t * t * t * t;
		}

		// quintic easing out - decelerating to zero velocity
		static float easeOutQuint(float t, float b, float c, float d) {
			t /= d;
			t--;
			return c*(t*t*t*t*t + 1.f) + b;
		}

		static float easeOutQuant(float t) {
			return 1.f - std::powf(1.f - t, 5.f);
		}

		// quintic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutQuint(float t, float b, float c, float d) {
			t /= d/2.f;
			if (t < 1.f)
				return c/2*t*t*t*t*t + b;
			t -= 2.f;
			return c/2.f*(t*t*t*t*t + 2.f) + b;
		}

		static float easeInOutQuint(float t) {
			return t < 0.5f ?
				16.f * t * t * t * t * t :
				1.f - std::pow(-2.f * t + 2.f, 5.f) / 2.f;
		}

		// sinusoidal easing in - accelerating from zero velocity
		static float easeInSine(float t, float b, float c, float d) {
			return -c * std::cos(t/d * (f_PI/2.f)) + c + b;
		}

		static float easeInSine(float t) {
			  return 1.f - std::cosf((t * f_PI) / 2.f);
		}

		// sinusoidal easing out - decelerating to zero velocity
		static float easeOutSine(float t, float b, float c, float d) {
			return c * std::sin(t/d * (f_PI/2.f)) + b;
		}

		static float easeOutSine(float t) {
			return std::sinf((t * f_PI) / 2.f);
		}

		// sinusoidal easing in/out - accelerating until halfway, then decelerating
		static float easeInOutSine(float t, float b, float c, float d) {
			return -c/2.f * (std::cos(f_PI*t/d) - 1.f) + b;
		}

		static float easeInOutSine(float t) {
			return -(std::cosf(f_PI * t) - 1.f) / 2.f;
		}

		// exponential easing in - accelerating from zero velocity
		static float easeInExpo(float t, float b, float c, float d) {
			return c * std::powf( 2.f, 10.f * (t/d - 1.f) ) + b;
		}

		static float easeInExpo(float t) {
			return t == 0 ? 0 : std::powf(2.f, 10.f * t - 10.f);
		}

		// exponential easing out - decelerating to zero velocity
		static float easeOutExpo(float t, float b, float c, float d) {
			return c * ( -std::powf( 2.f, -10.f * t/d ) + 1.f ) + b;
		}

		static float easeOutExpo(float t) {
			return t == 1.f ?
				1.f :
				1.f - std::powf(2.f, -10.f * t);
		}

		// exponential easing in/out - accelerating until halfway, then decelerating
		static float easeInOutExpo(float t, float b, float c, float d) {
			t /= d/2.f;
			if (t < 1.f)
				return c/2.f * std::powf( 2.f, 10.f * (t - 1.f) ) + b;
			t--;
			return c/2 * ( -std::powf( 2.f, -10.f * t) + 2.f ) + b;
		}

		static float easeInOutExpo(float t) {
			if (t == 0) {
				return 0;
			}
			else {
				if (t == 1) {
					return 1;
				} else {
					if (t < 0.5f) {
						return std::powf(2.f, 20.f * t - 10) / 2.f;
					}
					else {
						return (2.f - std::powf(2.f, -20.f * t + 10.f)) / 2.f;
					}
				}
			}
		}

		// circular easing in - accelerating from zero velocity
		static float easeInCirc(float t, float b, float c, float d) {
			t /= d;
			return -c * (std::sqrtf(1.f - t*t) - 1.f) + b;
		}

		static float easeInCirc(float t) {
			return 1.f - std::sqrtf(1.f - std::powf(t, 2.f));
		}

		// circular easing out - decelerating to zero velocity
		static float easeOutCirc(float t, float b, float c, float d) {
			t /= d;
			t--;
			return c * std::sqrtf(1.f - t*t) + b;
		}

		static float easeOutCirc(float t) {
			return std::sqrtf(1.f - std::powf(t - 1.f, 2.f));
		}

		// circular easing in/out - acceleration until halfway, then deceleration
		static float easeInOutCirc(float t, float b, float c, float d) {
			t /= d/2.f;
			if (t < 1.f)
				return -c/2.f * (std::sqrtf(1.f - t*t) - 1.f) + b;
			t -= 2.f;
			return c/2.f * (std::sqrtf(1.f - t*t) + 1.f) + b;
		}

		static float easeInOutCirc(float t) {
			return t < 0.5f
				? (1.f - std::sqrtf(1.f - std::powf(2.f * t, 2.f))) / 2.f
				: (std::sqrtf(1.f - std::powf(-2.f * t + 2.f, 2.f)) + 1.f) / 2.f;
		}

		// ease in back - pulls back before easing in
		static float easeInBack(float t, float b, float c, float d, float c1=1.70158f) {
			// tweak x for a more dramatic pull back
			t /= d; // 0-1 on curve
			float c3 = c1 + 1.f;
			float val = c3 * t * t * t - c1 * t * t; // modify t with ease in back formula
			return (c * val) + b;
		}

		static float easeInBack(float t, float c1=1.70158f) {
			float c3 = c1 + 1.f;
			return c3 * t * t * t - c1 * t * t;
		}

		// ease out back - over throws before easing out
		static float easeOutBack(float t, float b, float c, float d, float c1=1.70158f) {
			// tweak c1 value for a more dramatic over throw
			t /= d; // 0-1 on curve
			float c3 = c1 + 1.f;
			float val = 1.f + c3 * std::powf(t - 1.f, 3.f) + c1 * std::powf(t - 1.f, 2.f); // apply ease in back formula
			return (c * val) + b;
		}

		static float easeOutBack(float t, float c1=1.70158f) {
			float c3 = c1 + 1;
			return 1.f + c3 * std::powf(t - 1.f, 3.f) + c1 * std::powf(t - 1.f, 2.f);
		}

		// ease in out back - pull back and over throw
		static float easeInOutBack(float t, float b, float c, float d, float c1=1.70158) {
			// tweak c1 value for a more dramatic pull back and over throw
			t /= d;
			float c2 = c1 * 1.525f;

			// apply pull back / over throw formula
			float val = t < 0.5f
				? (pow(2.f * t, 2.f) * ((c2 + 1.f) * 2.f * t - c2)) / 2.f
				: (pow(2.f * t - 2.f, 2.f) * ((c2 + 1.f) * (t * 2.f - 2.f) + c2) + 2.f) / 2.f;

			return (c * val) + b;
		}

		static float easeInOutBack(float t, float c1=1.70158) {
			float c2 = c1 * 1.525;

			return t < 0.5f
				? (std::powf(2.f * t, 2.f) * ((c2 + 1.f) * 2.f * t - c2)) / 2.f
				: (std::powf(2.f * t - 2.f, 2.f) * ((c2 + 1.f) * (t * 2.f - 2.f) + c2) + 2.f) / 2.f;
		}

		// ease in elastic
		static float easeInElastic(float t, float b, float c, float d) {
			t /= d;
			float x = 10.75f; // magic number
			float c4 = (2.f * f_PI) / 3.f;
			float val = t == 0
				? 0
				: t == 1.f
					? 1.f
					: -std::powf(2.f, 10.f * t - 10.f) * std::sinf((t * 10.f - x) * c4);

			return (c * val) + b;
		}

		static float easeInElastic(float t) {
			float c4 = (2.f * f_PI) / 3.f;
			float x = 10.75f; // magic number
			return t == 0
				? 0
				: t == 1.f
					? 1.f
					: -std::powf(2.f, 10.f * t - 10.f) * std::sinf((t * 10.f - x) * c4);
		}

		// ease out elastic
		static float easeOutElastic(float t, float b, float c, float d) {
			t /= d;
			float x = 0.75f; // magic number
			float c4 = (2.f * f_PI) / 3.f;
			float val = t == 0
				? 0
				: t == 1.f
					? 1.f
					: std::powf(2.f, -10.f * t) * std::sinf((t * 10.f - x) * c4) + 1.f;

			return (c * val) + b;
		}

		static float easeOutElastic(float t) {
			float c4 = (2.f * f_PI) / 3.f;
			float x = 0.75f; // magic number

			return t == 0
				? 0
				: t == 1.f
					? 1.f
					: std::powf(2.f, -10.f * t) * std::sinf((t * 10.f - x) * c4) + 1.f;
		}

		// ease in out elastic
		static float easeInOutElastic(float t, float b, float c, float d) {
			t /= d;
			float x = 11.125f; // magic number
			float c5 = (2.f * f_PI) / 4.5f;
			float val = t == 0
				? 0
				: t == 1.f
					? 1.f
					: t < 0.5f
						? -(std::powf(2.f, 20.f * t - 10.f) * std::sinf((20.f * t - x) * c5)) / 2.f
						: (std::powf(2.f, -20.f * t + 10.f) * std::sinf((20.f * t - x) * c5)) / 2.f + 1.f;

			return (c * val) + b;
		}

		static float easeInOutElastic(float t) {
			float x = 11.125f; // magic number
			float c5 = (2.f * f_PI) / 4.5f;

			return t == 0
				? 0
				: t == 1.f
					? 1.f
					: t < 0.5f
						? -(std::powf(2.f, 20.f * t - 10.f) * std::sinf((20.f * t - x) * c5)) / 2.f
						: (std::powf(2.f, -20.f * t + 10.f) * std::sinf((20.f * t - x) * c5)) / 2.f + 1.f;

		}

		// ease out bounce
		static float easeOutBounce(float t, float b, float c, float d) {
			t /= d;
			float n1 = 7.5625f;
			float d1 = 2.75f;
			float val = 0.f;

			if (t < 1.f / d1) {
				val = n1 * t * t;
			} else if (t < 2.f / d1) {
				t -= (1.5f / d1);
				val = n1 * t * t + 0.75f;;
			} else if (t < 2.5f / d1) {
				t -= (2.25f / d1);
				val = n1 * t * t + 0.9375f;
			} else {
				t -= (2.625f / d1);
				val = n1 * t * t + 0.984375f;
			}

			return (c * val) + b;
		}

		// ease out bounce - pass value between 0 and 1 (also utility for easeInBounce())
		static float easeOutBounce(float t) {
			float n1 = 7.5625f;
			float d1 = 2.75f;
			float val = 0.f;

			if (t < 1.f / d1) {
				val = n1 * t * t;
			} else if (t < 2.f / d1) {
				t -= (1.5f / d1);
				val = n1 * t * t + 0.75f;;
			} else if (t < 2.5f / d1) {
				t -= (2.25f / d1);
				val = n1 * t * t + 0.9375f;
			} else {
				t -= (2.625f / d1);
				val = n1 * t * t + 0.984375f;
			}

			return val;
		}

		// ease in bounce
		static float easeInBounce(float t, float b, float c, float d) {
			float x = t /= d;
			float val = 1.f - easeOutBounce(1.f - x);

			return (c * val) + b;
		}

		// ease in bounce - pass value between 0 and 1 (utility for easeInOutBounce())
		static float easeInBounce(float t) {
			return 1.f - easeOutBounce(1.f - t);
		}

		// ease in out bounce
		static float easeInOutBounce(float t, float b, float c, float d) {
			t /= d;
			float val = t < 0.5f
				? (1.f - easeOutBounce(1.f - 2.f * t)) / 2.f
				: (1.f + easeOutBounce(2.f * t - 1.f)) / 2.f;

			return (c * val) + b;
		}
	};

	const float Interpolate::f_PI = static_cast<float>(M_PI);
}

#endif