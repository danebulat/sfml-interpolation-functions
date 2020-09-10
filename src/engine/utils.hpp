#ifndef Utils_Hpp
#define Utils_Hpp

template<class T> void SafeDelete( T*& pVal ) {
	if (pVal != nullptr) {
		delete pVal;
		pVal = nullptr;
	}
}

template<typename T> void SafeDeleteArray(T*& pVal) {
    if (pVal != nullptr) {
		delete [] pVal;
		pVal = nullptr;
	}
}

#endif