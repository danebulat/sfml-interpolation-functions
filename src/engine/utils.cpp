#include "engine/utils.hpp"

#include <sstream>
#include <iostream>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

// Initialise 31 easing labels
namespace demo
{
	namespace camera
	{
		/** Inserts easing function label strings into the passed vector.
		*/
		void initEasingLabels(vector<string>& vec) {
			vec = {
				"Linear",
				"Quad Ease In",
				"Quad Ease Out",
				"Quad Ease In Out",
				"Cubic Ease In",
				"Cubic Ease Out",
				"Cubic Ease In Out",
				"Quart Ease In",
				"Quart Ease Out",
				"Quart Ease In Out",
				"Quint Ease In",
				"Quint Ease Out",
				"Quint Ease In Out",
				"Sine Ease In",
				"Sine Ease Out",
				"Sine Ease In Out",
				"Expo Ease In",
				"Expo Ease Out",
				"Expo Ease In Out",
				"Circ Ease In",
				"Circ Ease Out",
				"Circ Ease In Out",
				"Back Ease In",
				"Back Ease Out",
				"Back Ease In Out",
				"Elastic Ease In",
				"Elastic Ease Out",
				"Elastic Ease In Out",
				"Bounce Ease In",
				"Bounce Ease Out",
				"Bounce Ease In Out" };
		}

		/** Returns HUD string for the current frame.
		*/
		string updateHUD(View& view,
							  Circle& player,
							  vector<string>& easeFuncVec,
							  InterpFunc interpf,
							  float dur) {

			int i = static_cast<int>(interpf);

			stringstream ss;
			ss << ""
				"-----------------------------------------------\n"
				"HUD:       Camera X  " << view.getCenter().x   << "\n"
				"           Camera Y  " << view.getCenter().y   << "\n"
				"           Player X: " << player.getCenter().x << "\n"
				"           Player Y: " << player.getCenter().y << "\n\n"
				"Selected Ease:  " << easeFuncVec[i-1]
								   << " (" << static_cast<int>(interpf)
								   << "/" << easeFuncVec.size()
								   << ")\n"
				"Tween Duration: " << dur << " seconds\n"
				"-----------------------------------------------\n";

			return ss.str();
		}

		/** Returns a string representing the "controls" HUD.
		*/
		string getControlsString() {
			return ""
				"-----------------------------------------------\n"
				"Controls:  H           Toggle HUD\n"
				"           Space       Switch player\n"
				"           WASD        Move active player\n"
				"           Up/Down     Change easing function\n"
				"           Left/Right  Modify tween duration\n"
				"-----------------------------------------------";
		}
	}
}