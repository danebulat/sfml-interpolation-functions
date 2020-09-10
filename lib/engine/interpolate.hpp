#ifndef Interpolate_Hpp
#define Interpolate_Hpp

#include <cmath>

namespace animation {

	/**
    Interpolation functions implemented for all the standard easing
	functions documented here:
	https://easings.net/

	Functions with a single float parameter accept a value between 0 and 1.
	*/

	class Interpolate {
	private:
		static const float fPI;

	public:
		Interpolate() = delete;
		Interpolate(const Interpolate&) = delete;
		Interpolate& operator= (const Interpolate&) = delete;

		// linear - no easing, no acceleration
		static float linear(float t, float b, float c, float d);

		// quadratic easing in - accelerating from zero velocity
		static float easeInQuad(float t, float b, float c, float d);
		static float easeInQuad(float t);

		// quadratic easing out - decelerating to zero velocity
		static float easeOutQuad(float t, float b, float c, float d);
		static float easeOutQuad(float t);

		// quadratic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutQuad(float t, float b, float c, float d);
		static float easeInOutQuad(float t);

		// cubic easing in - accelerating from zero velocity
		static float easeInCubic(float t, float b, float c, float d);
		static float easeInCubic(float t);

		// cubic easing out - decelerating to zero velocity
		static float easeOutCubic(float t, float b, float c, float d);
		static float easeOutCubic(float t);

		// cubic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutCubic(float t, float b, float c, float d);
		static float easeInOutCubic(float t);

		// quartic easing in - accelerating from zero velocity
		static float easeInQuart(float t, float b, float c, float d);
		static float easeInQuart(float t);

		// quartic easing out - decelerating to zero velocity
		static float easeOutQuart(float t, float b, float c, float d);
		static float easeOutQuart(float t);

		// quartic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutQuart(float t, float b, float c, float d);
		static float easeInOutQuard(float t);

		// quintic easing in - accelerating from zero velocity
		static float easeInQuint(float t, float b, float c, float d);
		static float easeInQuint(float t);

		// quintic easing out - decelerating to zero velocity
		static float easeOutQuint(float t, float b, float c, float d);
		static float easeOutQuant(float t);

		// quintic easing in/out - acceleration until halfway, then deceleration
		static float easeInOutQuint(float t, float b, float c, float d);
		static float easeInOutQuint(float t);

		// sinusoidal easing in - accelerating from zero velocity
		static float easeInSine(float t, float b, float c, float d);
		static float easeInSine(float t);

		// sinusoidal easing out - decelerating to zero velocity
		static float easeOutSine(float t, float b, float c, float d);
		static float easeOutSine(float t);

		// sinusoidal easing in/out - accelerating until halfway, then decelerating
		static float easeInOutSine(float t, float b, float c, float d);
		static float easeInOutSine(float t);

		// exponential easing in - accelerating from zero velocity
		static float easeInExpo(float t, float b, float c, float d);
		static float easeInExpo(float t);

		// exponential easing out - decelerating to zero velocity
		static float easeOutExpo(float t, float b, float c, float d);
		static float easeOutExpo(float t);

		// exponential easing in/out - accelerating until halfway, then decelerating
		static float easeInOutExpo(float t, float b, float c, float d);
		static float easeInOutExpo(float t);

		// circular easing in - accelerating from zero velocity
		static float easeInCirc(float t, float b, float c, float d);
		static float easeInCirc(float t);

		// circular easing out - decelerating to zero velocity
		static float easeOutCirc(float t, float b, float c, float d);
		static float easeOutCirc(float t);

		// circular easing in/out - acceleration until halfway, then deceleration
		static float easeInOutCirc(float t, float b, float c, float d);
		static float easeInOutCirc(float t);

		// ease in back - pulls back before easing in
		static float easeInBack(float t, float b, float c, float d, float c1=1.70158f);
		static float easeInBack(float t, float c1);

		// ease out back - over throws before easing out
		static float easeOutBack(float t, float b, float c, float d, float c1=1.70158f);
		static float easeOutBack(float t, float c1);

		// ease in out back - pull back and over throw
		static float easeInOutBack(float t, float b, float c, float d, float c1=1.70158f);
		static float easeInOutBack(float t, float c1);

		// ease in elastic
		static float easeInElastic(float t, float b, float c, float d);
		static float easeInElastic(float t);

		// ease out elastic
		static float easeOutElastic(float t, float b, float c, float d);
		static float easeOutElastic(float t);

		// ease in out elastic
		static float easeInOutElastic(float t, float b, float c, float d);
		static float easeInOutElastic(float t);

		// ease out bounce
		static float easeOutBounce(float t, float b, float c, float d);
		static float easeOutBounce(float t);

		// ease in bounce
		static float easeInBounce(float t, float b, float c, float d);
		static float easeInBounce(float t);

		// ease in out bounce
		static float easeInOutBounce(float t, float b, float c, float d);
	};
}

#endif