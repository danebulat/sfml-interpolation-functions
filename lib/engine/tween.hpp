#ifndef Tween_Hpp
#define Tween_Hpp

struct Tween {
	// Reference to the property being animated
	float* m_property;

    float m_startValue;
    float m_targetValue;
	float m_changeValue;
    float m_duration;
    float m_elapsedTime;
    bool  m_isAnimating;

    // Default constructor where members should be initialised
	// manually after instantiation.
    Tween();
	~Tween();

	// Custom constructor to initialise data members with custom values.
    Tween(float* property, float startValue, float targetValue, float duration);

	// Disable copy constructor and assignment operator
	Tween& operator= (const Tween&) = delete;
	Tween(const Tween&) = delete;

    // API called from parent class
    void resetAndStop();
	void resetAndPlay();
	void start();
	void stop();
	void update(float dt);
};

#endif