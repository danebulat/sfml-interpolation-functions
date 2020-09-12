#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Platform/Platform.hpp"
// #include <THOR/Shapes.hpp>
// #include <THOR/Graphics.hpp>
#include "engine/button.hpp"
#include "engine/circle.hpp"
#include "engine/interpolate.hpp"
#include "engine/tween.hpp"
#include "engine/camera.hpp"
#include "engine/utils.hpp"

#include <cmath>

using namespace animation;
using namespace demo::camera;

Circle makeCircle(const sf::Color& color) {
    return Circle(color);
}

int EasingDemo(RenderWindow&);
int TweenSpawnDemo(RenderWindow&);

int main()
{
    util::Platform platform;

    Vector2f resolution(800.f, 600.f);
    sf::RenderWindow window(sf::VideoMode(resolution.x,resolution.y,32), "Camera Animation Using Easing Functions With SFML", sf::Style::Default);

    // NOTE: Set frame rate limit in Engine
    window.setFramerateLimit(60);

    //return EasingDemo(window);
    //return TweenSpawnDemo(window);

    // Camera switch demo
    Circle player1(Vector2f(500.f, 575.f), sf::Color::Yellow, 30.f);
    Circle player2(Vector2f(800.f, 675.f), sf::Color::Green, 30.f);
    player1.setActive(true);

    sf::Font myfont;
    if(!myfont.loadFromFile("content/DroidSansMono.ttf")) {
        std::cerr << "Could not load font DroidSansMono.ttf." << std::endl;
    }

    sf::Texture backtexture;
    if (!backtexture.loadFromFile("content/background.png"))
        std::cerr << "Could not load texture background.png" << std::endl;

    sf::Sprite background;
    background.setTexture(backtexture);
    background.setPosition(0,0);

    sf::View hud(sf::FloatRect(0, 0, resolution.x, resolution.y));
    sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));
    view.setCenter(player1.getCenter());

    sf::Text label;
    sf::Text controlsLabel;
    std::vector<std::string> easingLabels;
    initEasingLabels(easingLabels);

    bool showHUD = true;

    label.setFont(myfont);
    label.setPosition(20.f, 1.f);
    label.setCharacterSize(12);

    controlsLabel.setFont(myfont);
    controlsLabel.setCharacterSize(12);
    controlsLabel.setString(getControlsString());
    controlsLabel.setPosition(20.f, resolution.y -
        controlsLabel.getLocalBounds().height - 10.f);

    sf::Clock clock;
    bool player1Active = true;

    // ------------------------------
    // Camera
    // ------------------------------
    Camera camera(player1.getCenter(), background.getTexture()->getSize(),
        resolution, true);
    camera.setDuration(.5f);
    camera.setInterpolation(InterpFunc::ElasticEaseOut);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        // Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            player1.handleInput(event);
            player2.handleInput(event);

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Up) {
                    int i = static_cast<int>(camera.getInterpolation());
                    if (++i <= 31)
                        camera.setInterpolation(static_cast<InterpFunc>(i));
                    else
                        camera.setInterpolation(static_cast<InterpFunc>(1));
                }

                if (event.key.code == sf::Keyboard::Down) {
                    int i = static_cast<int>(camera.getInterpolation());
                    if (--i >= 1)
                        camera.setInterpolation(static_cast<InterpFunc>(i));
                    else
                        camera.setInterpolation(static_cast<InterpFunc>(31));
                }

                if (event.key.code == sf::Keyboard::Right) {
                    camera.incrementDuration(.1f);
                }

                if (event.key.code == sf::Keyboard::Left) {
                    camera.incrementDuration(-.1f);
                }

                if (event.key.code == sf::Keyboard::H) {
                    showHUD = !showHUD;
                }

                // SPACE
                if (event.key.code == sf::Keyboard::Space) {

                    // Switch player only if the tween is NOT active
                    if (!camera.isAnimating()) {

                        // Determine which player to switch to
                        if (player1Active) {
                            player1.setActive(false);
                            player2.setActive(true);
                            camera.animateTo(player2.getCenter());
                        }
                        else {
                            player1.setActive(true);
                            player2.setActive(false);
                            camera.animateTo(player1.getCenter());
                        }

                        player1Active = !player1Active;
                    }// !tweenXActive && !tweenYActive
                }// event.key.code == sf::Keyboard::Space
            }
        }

        // ----------------------------------------------------------------------
        // Update
        // ----------------------------------------------------------------------

        // Update the active player position if camera is not animating
        if (!camera.isAnimating()) {
            player1.update(dt.asSeconds());
            player2.update(dt.asSeconds());
        }

        // Update camera (make it follow the player or animate to the active player)
        if (player1Active) {
            camera.update(dt.asSeconds(), player1);
            label.setString(updateHUD(view, player1, easingLabels,
                camera.getInterpolation(), camera.getDuration()));
        }
        else {
            camera.update(dt.asSeconds(), player2);
            label.setString(updateHUD(view, player2, easingLabels,
                camera.getInterpolation(), camera.getDuration()));
        }

        // Center view on camera's position
        view.setCenter(camera.getPosition());

        // Draw
        window.clear();
        window.setView(view);
        window.draw(background);
        player1.draw(window);
        player2.draw(window);

        if (showHUD) {
            window.setView(hud);
            window.draw(label);
            window.draw(controlsLabel);
        }

        window.display();
    }

    return 0;
}

/*------------------------------------------------------------
 Tween spawn circle demo
 ------------------------------------------------------------*/
int TweenSpawnDemo(RenderWindow& window) {
    Circle circle(Vector2f(30.f, 275.f), Color::Yellow, 50.f);
    circle.createDemoTween();

    sf::Clock clock;

    sf::Font myfont;
    if(!myfont.loadFromFile("content/DroidSansMono.ttf")) {
        std::cerr<<"Could not load your font contb.ttf."<<std::endl;
    }

    std::string text = ""
        "---------------------------------------------\n\n"
        "Controls\n"
        "---------------------------------------------\n\n"
        "Enter:        Toggle tween start() and stop()\n\n"
        "Right Shift:  spawnOutTween()\n\n"
        "Left Shift:   spawnInTween()\n\n"
        "---------------------------------------------";

    sf::Text label(text, myfont);
    label.setPosition(20.f, 20.f);
    label.setCharacterSize(14);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        // Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

                // Enter key starts tween from beginning
                if (event.key.code == sf::Keyboard::Enter) {
                    circle.startStopTweenToggle();
                }

                if (event.key.code == sf::Keyboard::LShift) {
                    circle.spawnInTween();
                }

                if (event.key.code == sf::Keyboard::RShift) {
                    circle.spawnOutTween();
                }
            }
        }

        // Update
        circle.update(dt.asSeconds());

        // Draw
        window.clear();
        circle.draw(window);
        window.draw(label);
        window.display();
    }

    return 0;
}

/*------------------------------------------------------------
 Easing Demo
 ------------------------------------------------------------*/

int EasingDemo(RenderWindow& window) {
    sf::Event e;
    bool running = true;

    sf::Font myfont;
    if(!myfont.loadFromFile("content/contb.ttf")) {
        std::cerr<<"Could not load your font contb.ttf."<<std::endl;
    }

    //set up a canvas to showcase the easing
    sf::RectangleShape line(sf::Vector2f(800, 1));
    line.setPosition(0.f, 75.f);

    //smooth curve ease in
    gui::button smoothin("Ease In\nDemo", myfont, sf::Vector2f(50.f,54.f), gui::style::clean);
    smoothin.setSize(14);
    smoothin.makeActive(true);
    smoothin.setLabelOffset(sf::Vector2f(0.f,5.f));//use this because the line breaks interfere with the alignment of the label
    smoothin.setBorderThickness(1.f);
    smoothin.setBorderRadius(0.f);
    smoothin.setBorderColor(sf::Color(255,255,255,255));

    //smooth curve ease out
    gui::button smoothout("Ease Out\nDemo", myfont, sf::Vector2f(smoothin.getPosition().x + smoothin.getDimensions().x + 20.f,53.f), gui::style::clean);
    smoothout.setSize(14);
    smoothout.setLabelOffset(sf::Vector2f(0.f,5.f));
    smoothout.makeActive(true);
    smoothout.setBorderThickness(1.f);
    smoothout.setBorderRadius(0.f);
    smoothout.setBorderColor(sf::Color(255,255,255,255));

    //smooth curve ease in out
    gui::button smoothInOut("Ease In-Out\nDemo", myfont, sf::Vector2f(smoothout.getPosition().x + smoothout.getDimensions().x + 25.f,53.f), gui::style::clean);
    smoothInOut.setSize(14);
    smoothInOut.setLabelOffset(sf::Vector2f(0.f,5.f));
    smoothInOut.makeActive(true);
    smoothInOut.setBorderThickness(1.f);
    smoothInOut.setBorderRadius(0.f);
    smoothInOut.setBorderColor(sf::Color(255,255,255,255));

    auto circle_linear = makeCircle(sf::Color::Red);
    auto circle_quadratic = makeCircle(sf::Color::Blue);
    auto circle_cubic = makeCircle(sf::Color::Yellow);
    auto circle_quartic = makeCircle(sf::Color::Green);
    auto circle_quintic = makeCircle(sf::Color::Cyan);
    auto circle_sinesoidal = makeCircle(sf::Color::Magenta);
    auto circle_exponential = makeCircle(sf::Color::Red);
    auto circle_circular = makeCircle(sf::Color::Blue);
    auto circle_back = makeCircle(sf::Color::Yellow);
    auto circle_elastic = makeCircle(sf::Color::Green);
    auto circle_bounce = makeCircle(sf::Color::Cyan);

    circle_linear.setPosition(140.f, 90.f);
    circle_quadratic.setPosition(140.f, 130.f);
    circle_cubic.setPosition(140.f, 162.f);
    circle_quartic.setPosition(140.f, 198.f);
    circle_quintic.setPosition(140.f, 234.f);
    circle_sinesoidal.setPosition(140.f, 270.f);
    circle_exponential.setPosition(140.f, 306.f);
    circle_circular.setPosition(140.f, 342.f);
    circle_back.setPosition(140.f, 378.f);
    circle_elastic.setPosition(140.f, 414.f);
    circle_bounce.setPosition(140.f, 450.f);

    //set up labels
    sf::Text label("Linear\n\nQuadratic\n\nCubic\n\nQuartic\n\nQuintic\n\nSinusoidal\n\nExponential\n\nCircular\n\nBack\n\nElastic\n\nBounce", myfont);
    label.setPosition(10.f, 90.f);
    label.setCharacterSize(18);

    std::size_t easetype = 0;
    sf::Clock tickClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time duration = sf::Time::Zero;

    sf::Time TimePerFrame = sf::seconds(1.f/60.f);

    while(running)
    {
        while(window.pollEvent(e))
        {
            if (e.type == sf::Event::KeyPressed) {

                if (e.key.code == sf::Keyboard::Num1) {
                    easetype = 0;
                    std::cout << "> Ease In\n";
                }
                if (e.key.code == sf::Keyboard::Num2) {
                    easetype = 1;
                    std::cout << "> Ease Out\n";
                }
                if (e.key.code == sf::Keyboard::Num3) {
                    easetype = 2;
                    std::cout << "> Ease In-Out\n";
                }
            }

            if(e.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }

            if(e.type == sf::Event::KeyPressed)
            {
                switch(e.key.code)
                {
                case sf::Keyboard::Escape:
                {
                    window.close();
                    return 0;
                }
                break;

                case sf::Keyboard::Return:
                {
                    duration = sf::Time::Zero;
                }
                break;

                default:
                    break;
                }
            }
            if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
            {
                duration = sf::Time::Zero;
                circle_linear.setPosition(140.f, 90.f);
                circle_quadratic.setPosition(140.f, 127.f);
                circle_cubic.setPosition(140.f, 162.f);
                circle_quartic.setPosition(140.f, 198.f);
                circle_quintic.setPosition(140.f, 234.f);
                circle_sinesoidal.setPosition(140.f, 270.f);
                circle_exponential.setPosition(140.f, 306.f);;
                circle_circular.setPosition(140.f, 342.f);
                circle_back.setPosition(140.f, 378.f);
                circle_elastic.setPosition(140.f, 414.f);
                circle_bounce.setPosition(140.f, 450.f);
            }
        }

        //perform updates
        smoothin.update(e,window);
        smoothout.update(e,window);
        smoothInOut.update(e,window);

        if(smoothin.getState() == gui::state::active)
        {
            easetype = 0;
        }
        else if(smoothout.getState() == gui::state::active)
        {
            easetype = 1;
        }
        else if(smoothInOut.getState() == gui::state::active)
        {
            easetype = 2;
        }

        timeSinceLastUpdate += tickClock.restart();     // Increment time accumulated since last frame

        float changeX = 200.0f;
        float dur = 1.0f;

        while (timeSinceLastUpdate > TimePerFrame)      // While accumulated time is greater than 1/60th of a second
        {
            timeSinceLastUpdate -= TimePerFrame;        // Subtract 1/60 of a second from timeSinceLastFrame

            duration += TimePerFrame;                   // Add 1/60 of a second to duration

            switch(easetype)
            {
            case 0:
            {
                /* Ease-In Functions */
                if(duration.asSeconds() < dur)          // Call interpolation function if duration less than 1 second
                {
                    float t = duration.asSeconds();

                    circle_linear.setPosition(Interpolate::linear(t, 140.f, changeX, dur), 90.f);
                    circle_quadratic.setPosition(Interpolate::easeInQuad(t, 140.f, changeX, dur), 127.f);
                    circle_cubic.setPosition(Interpolate::easeInCubic(t, 140.f, changeX, dur), 162.f);
                    circle_quartic.setPosition(Interpolate::easeInQuart(t, 140.f, changeX, dur), 198.f);
                    circle_quintic.setPosition(Interpolate::easeInQuint(t, 140.f, changeX, dur), 234.f);
                    circle_sinesoidal.setPosition(Interpolate::easeInSine(t, 140.f, changeX, dur), 270.f);
                    circle_exponential.setPosition(Interpolate::easeInExpo(t, 140.f, changeX, dur), 306.f);
                    circle_circular.setPosition(Interpolate::easeInCirc(t, 140.f, changeX, dur), 342.f);
                    circle_back.setPosition(Interpolate::easeInBack(t, 140.f, changeX, dur), 378.f);
                    circle_elastic.setPosition(Interpolate::easeInElastic(t, 140.f, changeX, dur), 414.f);
                    circle_bounce.setPosition(Interpolate::easeInBounce(t, 140.f, changeX, dur), 450.f);
                }
            }
            break;
            case 1:
            {
                /* Ease-Out Functions */
                if(duration.asSeconds() < dur)  // Call interpolation function if duration is less than x second
                {
                    // float elapsedTime = duration.asSeconds();
                    // float xPos = Interpolate::easeOutBounce(
                    //                 elapsedTime,            // Same unit as total time (d), the starting time
                    //                 140.0f,                 // The beginning value of the property that we're animating
                    //                 160.0f,                 // The change between the beginning and destination value of the property.
                    //                 1.f);                   // Total time of the tween
                    //
                    // std::cout << "xPos: " << xPos << "\tduration: " << duration.asSeconds() << std::endl;
                    // std::cout.flush();
                    // circle_linear.setPosition(xPos, 170.0f);

                    float t = duration.asSeconds();

                    circle_linear.setPosition(Interpolate::linear(t, 140.f, changeX, dur), 90.f);
                    circle_quadratic.setPosition(Interpolate::easeOutQuad(t, 140.f, changeX, dur), 127.f);
                    circle_cubic.setPosition(Interpolate::easeOutCubic(t, 140.f, changeX, dur), 162.f);
                    circle_quartic.setPosition(Interpolate::easeOutQuart(t, 140.f, changeX, dur), 198.f);
                    circle_quintic.setPosition(Interpolate::easeOutQuint(t, 140.f, changeX, dur), 234.f);
                    circle_sinesoidal.setPosition(Interpolate::easeOutSine(t, 140.f, changeX, dur), 270.f);
                    circle_exponential.setPosition(Interpolate::easeOutExpo(t, 140.f, changeX, dur), 306.f);
                    circle_circular.setPosition(Interpolate::easeOutCirc(t, 140.f, changeX, dur), 342.f);
                    circle_back.setPosition(Interpolate::easeOutBack(t, 140.f, changeX, dur), 378.f);
                    circle_elastic.setPosition(Interpolate::easeOutElastic(t, 140.f, changeX, dur), 414.f);
                    circle_bounce.setPosition(Interpolate::easeOutBounce(t, 140.f, changeX, dur), 450.f);
                }
            }
            break;
            case 2:
            {
                /* Ease-In-Out Functions */
                if(duration.asSeconds() < dur)
                {
                    float t = duration.asSeconds();

                    circle_linear.setPosition(Interpolate::linear(t, 140.f, changeX, dur), 90.f);
                    circle_quadratic.setPosition(Interpolate::easeInOutQuad(t, 140.f, changeX, dur), 127.f);
                    circle_cubic.setPosition(Interpolate::easeInOutCubic(t, 140.f, changeX, dur), 162.f);
                    circle_quartic.setPosition(Interpolate::easeInOutQuart(t, 140.f, changeX, dur), 198.f);
                    circle_quintic.setPosition(Interpolate::easeInOutQuint(t, 140.f, changeX, dur), 234.f);
                    circle_sinesoidal.setPosition(Interpolate::easeInOutSine(t, 140.f, changeX, dur), 270.f);
                    circle_exponential.setPosition(Interpolate::easeInOutExpo(t, 140.f, changeX, dur), 306.f);
                    circle_circular.setPosition(Interpolate::easeInOutCirc(t, 140.f, changeX, dur), 342.f);
                    circle_back.setPosition(Interpolate::easeInOutBack(t, 140.f, changeX, dur), 378.f);
                    circle_elastic.setPosition(Interpolate::easeInOutElastic(t, 140.f, changeX, dur), 414.f);
                    circle_bounce.setPosition(Interpolate::easeInOutBounce(t, 140.f, changeX, dur), 450.f);
                }
            }
            break;

            default:
                break;
            }
        }

        window.clear();
        window.draw(line);
        window.draw(smoothin);
        window.draw(smoothout);
        window.draw(smoothInOut);

        window.draw(label);

        circle_linear.draw(window);
        circle_quadratic.draw(window);
        circle_cubic.draw(window);
        circle_quartic.draw(window);
        circle_quintic.draw(window);
        circle_sinesoidal.draw(window);
        circle_exponential.draw(window);
        circle_circular.draw(window);
        circle_back.draw(window);
        circle_elastic.draw(window);
        circle_bounce.draw(window);

        window.display();
    }

    return 0;
}
