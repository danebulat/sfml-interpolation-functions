#ifndef Utils_Hpp
#define Utils_Hpp

#include "engine/tween.hpp"
#include "engine/circle.hpp"

template<class T>
void SafeDelete(T*& pVal) {
	if (pVal != nullptr) {
		delete pVal;
		pVal = nullptr;
	}
}

template<class T>
void SafeDeleteArray (T*& pVal) {
    if (pVal != nullptr) {
		delete [] pVal;
		pVal = nullptr;
	}
}

namespace demo
{
	namespace camera
	{
		/** Inserts easing function label strings into the passed vector.
		*/
    	void initEasingLabels(std::vector<std::string>& vec);

		/** Returns HUD string for the current frame.
		*/
		std::string updateHUD(View& view,
							  Circle& player,
    						  std::vector<std::string>& easeFuncVec,
							  InterpFunc interpf,
							  float dur);

		/** Returns a string representing the "controls" HUD.
		*/
		std::string getControlsString();
	}
}

#endif