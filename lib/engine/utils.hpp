#ifndef Utils_Hpp
#define Utils_Hpp

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
    // Initialise 31 easing labels
    void initEasingLabels(std::vector<std::string>& vec);
}

#endif