#include <iostream>
#include <SFML/Graphics.hpp>
// #include <THOR/Shapes.hpp>
// #include <THOR/Graphics.hpp>
#include "engine/button.hpp"
#include "engine/circle.hpp"
#include "Platform/Platform.hpp"
#include "engine/interpolate.hpp"

#include <cmath>

using namespace animation;

Circle makeCircle(const sf::Color& color) {
    return Circle(color);
}

int main(void)
{
    util::Platform platform;

    sf::RenderWindow window(sf::VideoMode(800,600,32), "Robert Penner's Easing Equations with SFML", sf::Style::Default);

   // NOTE: Set frame rate limit in Engine
   window.setFramerateLimit(60);

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
