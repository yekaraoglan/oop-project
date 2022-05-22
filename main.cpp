#include "object.h"
#include "object.cpp"
#include <iostream>
#include <vector>

/**
 * TODO:
 * - Set a background
 * - Smaller textures
 * - Bigger window
 * - Mouse - object interactions
 *
 */

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 720), "My window");
    window.setPosition(sf::Vector2i(0, 0));
    sf::Vector2i windowPose = window.getPosition();
    AndGate andGate(true);
    OrGate orGate(true);
    NotGate notGate(true);
    XorGate xorGate(true);
    DFlipFlop dFlipFlop(true);
    LogicOne logicOne(true);
    Gnd gnd(true);
    LED led(true);
    Clock clock(true);

    Simulator sim;

    std::vector<LogicElement *> menuObjects;
    menuObjects.push_back(&andGate);
    menuObjects.push_back(&orGate);
    menuObjects.push_back(&notGate);
    menuObjects.push_back(&xorGate);
    menuObjects.push_back(&dFlipFlop);
    menuObjects.push_back(&logicOne);
    menuObjects.push_back(&gnd);
    menuObjects.push_back(&led);
    menuObjects.push_back(&clock);

    // sf::Sprite background;
    // sf::Texture back_text;
    // back_text.loadFromFile("TemplateProject/assets/background.png");
    // background.setTexture(back_text);

    sf::Mouse mouse;
    sf::Keyboard keyboard;

    sf::Sprite start;
    sf::Texture start_text;
    start_text.loadFromFile("TemplateProject/assets/START.png");
    start.setTexture(start_text);
    start.setPosition(sf::Vector2f(150, 50));

    sf::Sprite stop;
    sf::Texture stop_text;
    stop_text.loadFromFile("TemplateProject/assets/STOP.png");
    stop.setTexture(stop_text);
    stop.setPosition(sf::Vector2f(400, 50));

    LogicElement *selected;
    sf::Sprite selectedSprite;
    bool draggingObject = false;
    std::vector<sf::Sprite> mainSprites;
    std::vector<sf::Sprite> addedSprites;

    mainSprites.push_back(start);
    mainSprites.push_back(stop);
    mainSprites.push_back(andGate.sprite);
    mainSprites.push_back(orGate.sprite);
    mainSprites.push_back(notGate.sprite);
    mainSprites.push_back(xorGate.sprite);
    mainSprites.push_back(dFlipFlop.sprite);
    mainSprites.push_back(logicOne.sprite);
    mainSprites.push_back(gnd.sprite);
    mainSprites.push_back(led.sprite);
    mainSprites.push_back(clock.sprite);

    for (int j=0; j<mainSprites.size(); j++)
    {
        std::cout << j << std::endl;
        std::cout << mainSprites[j].getGlobalBounds().width << std::endl;
        std::cout << mainSprites[j].getGlobalBounds().height << std::endl;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear();
            // window.draw(background);
            for (int i = 0; i < mainSprites.size(); i++)
                window.draw(mainSprites[i]);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (int i = 0; i < menuObjects.size(); i++)
                    {
                        if (menuObjects[i]->getSprite().getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                        {
                            selected = menuObjects[i];
                            selectedSprite = selected->getSprite();
                            draggingObject = true;
                            // std::cout << floatrect.top << " " << floatrect.left << " " << floatrect.width << " " << floatrect.height << std::endl;
                            
                            std::cout << "Selected object" << std::endl;

                            break;
                        }
                    }
                    for (int j = 0; j < sim.getLogicElements().size(); j++)
                    {
                        if (sim.getLogicElements()[j]->getSprite().getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                        {
                            for (int k = 0; k < sim.getLogicElements()[j]->getNumPins(); k++){
                                if (sim.getLogicElements()[j]->getPins()[k].rect.contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                                {
                                    std::cout << "Selected pin" << std::endl;
                                    
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (selected != nullptr){
                    draggingObject = false;
                    // Create new object
                    sim.addLogicElement(selected->createNewLogicElement(mouse));
                    
                    addedSprites.push_back(selectedSprite);
                }
                selected = nullptr;
                // std::cout << "Dragging stopped" << std::endl;
            }

            if (draggingObject)
            {
                selectedSprite.setPosition(mouse.getPosition().x - window.getPosition().x, mouse.getPosition().y - window.getPosition().y);
                // addedSprites.push_back(selectedSprite);
                window.draw(selectedSprite);
                // std::cout << "Dragging" << std::endl;
            }

            for (int i = 0; i < addedSprites.size(); i++)
                window.draw(addedSprites[i]);
        }       

        window.display();
    }
    return 0;
}