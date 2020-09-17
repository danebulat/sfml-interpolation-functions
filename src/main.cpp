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

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui/imgui_utils.hpp"
#include "imgui/imgui_demos.hpp"

#include <cmath>

using namespace animation;
using namespace demo::camera;

Circle makeCircle(const sf::Color& color) {
    return Circle(color);
}

void CameraDemo(RenderWindow&, const Vector2f&);
void EasingDemo(RenderWindow&, const Vector2f&);
void TweenSpawnDemo(RenderWindow&, const Vector2f&);

unsigned int current_demo = 3;

DemoManager demoManager; // ImGui

int main()
{
    util::Platform platform;

    Vector2f resolution(1024.f, 640.f);
    sf::RenderWindow window(sf::VideoMode(resolution.x,resolution.y,32), "Camera Animation Using Easing Functions With SFML", sf::Style::Default);

    // Initialise ImGui
    ImGui::SFML::Init(window);
	demoManager.initialise(window);

    // NOTE: Set frame rate limit in Engine
    window.setFramerateLimit(60);

    while (current_demo != 0) {
        switch (current_demo) {
        case 1:
            EasingDemo(window, resolution);
            break;

        case 2:
            TweenSpawnDemo(window, resolution);
            break;

        case 3:
            CameraDemo(window, resolution);
            break;
        }
    }

    // clean up ImGui, such as deleting the internal font atlas
    ImGui::SFML::Shutdown();

    return 0;
}

/*------------------------------------------------------------
 Camera demo
 ------------------------------------------------------------*/
void CameraDemo(RenderWindow& window, const Vector2f& resolution) {

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

    /* Easing Demo Button */
    float btnX = resolution.x - 100.f;
    float btnY = resolution.y - 100.f;

    gui::button btnEasingDemo("Easing Demo #1", myfont, Vector2f(btnX, btnY), gui::style::clean);
    btnEasingDemo.setSize(14);
    btnEasingDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnEasingDemo.makeActive(true);
    btnEasingDemo.setBorderThickness(1.f);
    btnEasingDemo.setBorderColor(sf::Color::White);

    btnY += 40.f;
    gui::button btnCircleDemo("Easing Demo #2", myfont, Vector2f(btnX, btnY), gui::style::clean);
    btnCircleDemo.setSize(14);
    btnCircleDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnCircleDemo.makeActive(true);
    btnCircleDemo.setBorderThickness(1.f);
    btnCircleDemo.setBorderColor(sf::Color::White);

    btnY += 40.f;
    gui::button btnCameraDemo("Easing Demo #3", myfont, Vector2f(btnX, btnY), gui::style::none);
    btnCameraDemo.setSize(14);
    btnCameraDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnCameraDemo.makeActive(true);
    btnCameraDemo.setBorderThickness(1.f);
    btnCameraDemo.setBorderColor(sf::Color::White);

    sf::Clock clock;
    bool player1Active = true;

    // ------------------------------
    // Camera
    // ------------------------------
    Camera camera(player1.getCenter(), background.getTexture()->getSize(),
        resolution, true);
    camera.setDuration(.5f);
    camera.setInterpolation(InterpFunc::ElasticEaseOut);

    bool doClickDemo1 = false;
    bool doClickDemo2 = false;

    // ------------------------------
    // ImGui
    // ------------------------------
    int comboIndex = 0;
    float tweenDuration = camera.getDuration();
    float player1Col[4] = { 1.f, 1.f, 0.f };
    float player2Col[4] = { 0.f, 1.f, 0.f };

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        // Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            // process ImGui events
            ImGui::SFML::ProcessEvent(event);

            // Close window: exit
            if (event.type == sf::Event::Closed) {
                current_demo = 0;
                window.close();
            }

            player1.handleInput(event);
            player2.handleInput(event);

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    current_demo = 0;
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

        // update ImGui
        ImGui::SFML::Update(window, dt);

        /*----------------------------------------------------------------------
         Start ImGui
         ----------------------------------------------------------------------*/
        ImGui::Begin("Camera Demo");

        float cameraPos[2] = { camera.getPosition().x, camera.getPosition().y };
        float player1Pos[2] = { player1.getCenter().x, player1.getCenter().y };
        float player2Pos[2] = { player2.getCenter().x, player2.getCenter().y };

        if (ImGui::CollapsingHeader("Animation Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

            // Switch player only if the tween is NOT active
            float windowWidth = ImGui::GetWindowContentRegionWidth();
            int i = 0;
            ImGui::PushID(i);

            if (!camera.isAnimating()) {
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));

                if (ImGui::Button("Animate", ImVec2(windowWidth, 45))) {

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
                }
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.3f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.35f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.4f));
                ImGui::Button("Animate", ImVec2(windowWidth, 45));
            }

            ImGui::PopStyleColor(3);
            ImGui::PopID();

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Easing Function"); ImGui::SameLine(130);
            //ImGui::PushItemWidth(70.f);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::Combo("##EasingFunction", &comboIndex, easingLabels)) {
                camera.setInterpolation(static_cast<InterpFunc>(comboIndex + 1));
            }

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Tween Duration"); ImGui::SameLine(130);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::SliderFloat("##TweenDuration", &tweenDuration, 0.2f, 30.0f, "%.1f secs")) {
                camera.setDuration(tweenDuration);
            }
        }

        if (ImGui::CollapsingHeader("Colors", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Player 1"); ImGui::SameLine(80);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::ColorEdit3("##Player1", player1Col,
                    ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayHSV)) {
                player1.setFillColor(sf::Color(
                    static_cast<sf::Uint8>(player1Col[0] * 255.f),
                    static_cast<sf::Uint8>(player1Col[1] * 255.f),
                    static_cast<sf::Uint8>(player1Col[2] * 255.f)));
            }

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Player 2"); ImGui::SameLine(80);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::ColorEdit3("##Player2", player2Col,
                    ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayHSV)) {
                player2.setFillColor(sf::Color(
                    static_cast<sf::Uint8>(player2Col[0] * 255.f),
                    static_cast<sf::Uint8>(player2Col[1] * 255.f),
                    static_cast<sf::Uint8>(player2Col[2] * 255.f)));
            }
        }

        if (ImGui::CollapsingHeader("Positions", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Camera"); ImGui::SameLine(80);
            ImGui::PushItemWidth(156.f);
            ImGui::SetNextItemWidth(-1);
            ImGui::InputFloat2("##Camera", cameraPos, 4, ImGuiInputTextFlags_ReadOnly);

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Player 1"); ImGui::SameLine(80);
            ImGui::PushItemWidth(156.f);
            ImGui::SetNextItemWidth(-1);
            ImGui::InputFloat2("##Player1", player1Pos, 4, ImGuiInputTextFlags_ReadOnly);

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Player 2"); ImGui::SameLine(80);
            ImGui::PushItemWidth(156.f);
            ImGui::SetNextItemWidth(-1);
            ImGui::InputFloat2("##Player2", player2Pos, 4, ImGuiInputTextFlags_ReadOnly);
        }

        if (ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Space");
            ImGui::SameLine(80);
            ImGui::Text("Switch player");

            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "WASD");
            ImGui::SameLine(80);
            ImGui::Text("Move active player");
        }

        ImGui::End();
        /*----------------------------------------------------------------------
         End ImGui
         ----------------------------------------------------------------------*/

        // Update buttons
        btnEasingDemo.update(event, window);
        btnCircleDemo.update(event, window);
        btnCameraDemo.update(event, window);

        if(btnEasingDemo.getState() == gui::state::active) {
            btnEasingDemo.setActive(false);
            if (doClickDemo1) {
                doClickDemo1 = false;
                current_demo = 1;
            }
        }
        else {
            doClickDemo1 = true;
        }

        if (btnCircleDemo.getState() == gui::state::active) {
            btnCircleDemo.setActive(false);
            if (doClickDemo2) {
                doClickDemo2 = false;
                current_demo = 2;
            }
        }
        else {
            doClickDemo2 = true;
        }

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

        window.setView(hud);

        if (showHUD) {
            window.draw(label);
            window.draw(controlsLabel);
        }

        window.draw(btnEasingDemo);
        window.draw(btnCircleDemo);
        window.draw(btnCameraDemo);

        // Render ImGui windows
        ImGui::SFML::Render(window);

        window.display();

        // Switch to another demo?
        if (current_demo != 3)
            break;
    }
}

/*------------------------------------------------------------
 Tween spawn circle demo
 ------------------------------------------------------------*/
void TweenSpawnDemo(RenderWindow& window, const Vector2f& resolution) {
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

    /* Easing Demo Button */
    float btnX = resolution.x - 100.f;
    float btnY = resolution.y - 100.f;

    gui::button btnEasingDemo("Easing Demo #1", myfont, Vector2f(btnX, btnY), gui::style::clean);
    btnEasingDemo.setSize(14);
    btnEasingDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnEasingDemo.makeActive(true);
    btnEasingDemo.setBorderThickness(1.f);
    btnEasingDemo.setBorderColor(sf::Color::White);

    btnY += 40.f;
    gui::button btnCircleDemo("Easing Demo #2", myfont, Vector2f(btnX, btnY), gui::style::none);
    btnCircleDemo.setSize(14);
    btnCircleDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnCircleDemo.makeActive(true);
    btnCircleDemo.setBorderThickness(1.f);
    btnCircleDemo.setBorderColor(sf::Color::White);

    btnY += 40.f;
    gui::button btnCameraDemo("Easing Demo #3", myfont, Vector2f(btnX, btnY), gui::style::clean);
    btnCameraDemo.setSize(14);
    btnCameraDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnCameraDemo.makeActive(true);
    btnCameraDemo.setBorderThickness(1.f);
    btnCameraDemo.setBorderColor(sf::Color::White);

    bool doClickDemo1 = false;
    bool doClickDemo3 = false;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        // Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            // process ImGui events
            ImGui::SFML::ProcessEvent(event);

            // Close window: exit
            if (event.type == sf::Event::Closed) {
                current_demo = 0;
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    current_demo = 0;
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
        // Update buttons
        btnEasingDemo.update(event, window);
        btnCircleDemo.update(event, window);
        btnCameraDemo.update(event, window);

        if(btnEasingDemo.getState() == gui::state::active) {
            btnEasingDemo.setActive(false);
            if (doClickDemo1) {
                doClickDemo1 = false;
                current_demo = 1;
            }
        }
        else {
            doClickDemo1 = true;
        }

        if (btnCameraDemo.getState() == gui::state::active) {
            btnCameraDemo.setActive(false);
            if (doClickDemo3) {
                doClickDemo3 = false;
                current_demo = 3;
            }
        }
        else {
            doClickDemo3 = true;
        }

        // update ImGui
        ImGui::SFML::Update(window, dt);
        demoManager.update(window);
		if (demoManager.get_current_demo() != 1)
        	window.clear();

        circle.update(dt.asSeconds());

        // Draw
        window.clear();
        circle.draw(window);
        window.draw(label);
        window.draw(btnEasingDemo);
        window.draw(btnCircleDemo);
        window.draw(btnCameraDemo);

        // Render ImGui windows
        ImGui::SFML::Render(window);

        window.display();

        // Switch to another demo?
        if (current_demo != 2) {
            break;
        }
    }
}

/*------------------------------------------------------------
 Easing Demo
 ------------------------------------------------------------*/

void EasingDemo(RenderWindow& window, const Vector2f& resolution) {
    sf::Event e;
    bool running = true;

    sf::Font myfont;
    if(!myfont.loadFromFile("content/contb.ttf")) {
        std::cerr<<"Could not load your font contb.ttf."<<std::endl;
    }

    sf::Font myfontB;
    if(!myfontB.loadFromFile("content/DroidSansMono.ttf")) {
        std::cerr << "Could not load font DroidSansMono.ttf." << std::endl;
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

    /* Easing Demo Button */
    float btnX = resolution.x - 100.f;
    float btnY = resolution.y - 100.f;

    gui::button btnEasingDemo("Easing Demo #1", myfontB, Vector2f(btnX, btnY), gui::style::none);
    btnEasingDemo.setSize(14);
    btnEasingDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnEasingDemo.makeActive(true);
    btnEasingDemo.setBorderThickness(1.f);
    btnEasingDemo.setBorderColor(sf::Color::White);

    btnY += 40.f;
    gui::button btnCircleDemo("Easing Demo #2", myfontB, Vector2f(btnX, btnY), gui::style::clean);
    btnCircleDemo.setSize(14);
    btnCircleDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnCircleDemo.makeActive(true);
    btnCircleDemo.setBorderThickness(1.f);
    btnCircleDemo.setBorderColor(sf::Color::White);

    btnY += 40.f;
    gui::button btnCameraDemo("Easing Demo #3", myfontB, Vector2f(btnX, btnY), gui::style::clean);
    btnCameraDemo.setSize(14);
    btnCameraDemo.setLabelOffset(Vector2f(0.f, 5.f));
    btnCameraDemo.makeActive(true);
    btnCameraDemo.setBorderThickness(1.f);
    btnCameraDemo.setBorderColor(sf::Color::White);

    bool doClickDemo2 = false;
    bool doClickDemo3 = false;

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
                current_demo = 0;
                window.close();
            }

            if(e.type == sf::Event::KeyPressed)
            {
                switch(e.key.code)
                {
                case sf::Keyboard::Escape:
                {
                    current_demo = 0;
                    window.close();
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

        // Update demo buttons
        btnEasingDemo.update(e, window);
        btnCircleDemo.update(e, window);
        btnCameraDemo.update(e, window);

        if(btnCircleDemo.getState() == gui::state::active) {
            btnCircleDemo.setActive(false);
            if (doClickDemo2) {
                doClickDemo2 = false;
                current_demo = 2;
            }
        }
        else {
            doClickDemo2 = true;
        }

        if (btnCameraDemo.getState() == gui::state::active) {
            btnCameraDemo.setActive(false);
            if (doClickDemo3) {
                doClickDemo3 = false;
                current_demo = 3;
            }
        }
        else {
            doClickDemo3 = true;
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

        window.draw(btnEasingDemo);
        window.draw(btnCircleDemo);
        window.draw(btnCameraDemo);

        window.display();

        // Switch to another demo?
        if (current_demo != 1)
            break;
    }
}
