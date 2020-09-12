#ifndef Camera_Hpp
#define Camera_Hpp

#include <SFML/Graphics.hpp>
#include "engine/tween.hpp"
#include "engine/circle.hpp"

class Camera {
private:

	/** General data
	*/
	sf::Vector2f	m_position;

	sf::Vector2u    m_backgroundSize;
	float 			m_minX;
	float 			m_minY;
	float			m_maxX;
	float			m_maxY;
	bool			m_clampToBackground;

	/** Data for tween animation
	*/
	InterpFunc 		m_interpolation;
	float      		m_duration;
	Tween*			m_tweenX;
	Tween*			m_tweenY;
	bool 			m_tweenXActive;
	bool 			m_tweenYActive;

private:
	void initDefault();
	void clampPosition(const sf::Vector2f& pos);
	void calculateMinMaxPos(
		const sf::Vector2u& backgroundSize, const sf::Vector2f& resolution);

	void spawnTweenX(float targetX);
	void spawnTweenY(float targetY);

public:
	/** Initialises a camera with default values.
	*
	* Disables clamping to the background size and provides
	* default interpolation and duration values for the tweens.
	*/
	Camera();

	/** Initialises a camera for clamping to a background.
	*
	* Initialises data members to enable clamping the camera's
	* position to the background container. Default interpolation
	* and duration values are initialised.
	*/
	Camera(const sf::Vector2f& position,
		   const sf::Vector2u& backgroundSize,
		   const sf::Vector2f& resolution,
		   bool  clamp /*=true*/ );

	/** Deallocates camera's tween objects.
	*/
	~Camera();

	// TODO: Copy constructor
	// TODO: Copy assignment operator
	// TODO: Move contructor
	// TODO: Move assignment operator

	/** Public API
	*/
	void animateTo(const sf::Vector2f& target);
	void clampTo(const sf::Vector2u& backgroundSize,
			     const sf::Vector2f& resolution);
	bool isAnimating() const;
	void update(float dt, const Circle& player);

	/** Accessors
	*/
	void setInterpolation(InterpFunc interp);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& pos);

	float getDuration() const;
	void setDuration(float duration);
};

#endif