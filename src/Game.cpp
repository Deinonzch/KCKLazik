#include "Game.h"
#include "Helper.h"

#include <iostream>

Game::Game()
{
    taskManager = new TaskManager(this);
}

void Game::start()
{
    loadTextures();
    tMap.setRepeated(true);
    sMap.setTexture(tMap);
    sMap.setTextureRect(sf::IntRect(0,0,3000,2000));

    window.create(sf::VideoMode(WINDOWX+200, WINDOWY), "sfmlview");

    rover.setTexture(tRover);
    rover.setOrigin(rover.getGlobalBounds().width/2, rover.getGlobalBounds().height/2);
    rover.setPosition(1500,1000);

    view.setSize(WINDOWX, WINDOWY);
    view.setCenter(rover.getPosition());
    view.setViewport(sf::FloatRect(0, 0, 0.8f, 1));
    window.setView(view);

    miniMap.setSize(200,150);
    miniMap.setCenter(view.getCenter());
    miniMap.setViewport(sf::FloatRect(0.8f, 0.75f, 0.2f, 0.25f));
    miniMap.zoom(16.0f);
    window.setView(miniMap);

    window.setFramerateLimit(60);

    srand(time(NULL));
    generateRandPosObjects(crater, 3, craters);
    for (Object * o : craters)
    {
        o->setScale((rand()%10+5)/10.f, (rand()%10+5)/10.f);
//        o->setRotation(rand()%360);
    }

    //vector of colliders

    //vector of noncolliders
    noncolliders.push_back(&craters);

    while (window.isOpen())
    {
        window.clear();

        while (window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                exit(0);
            }

//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) taskManager->move(-100, 0);
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) taskManager->move(100, 0);
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) taskManager->move(0, -100);
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) taskManager->move(0, 100);
        }

        window.setView(view);
        window.draw(sMap);
        for (Object * t : craters)
        {
            window.draw(*t);
        }

        window.draw(miniMapRect);

        window.draw(rover);

        window.setView(miniMap);
        window.draw(sMap);
        for (Object * t : craters)
        {
            window.draw(*t);
        }

        window.draw(rover);

        window.display();
    }

}

void Game::loadTextures()
{
    if (!tMap.loadFromFile("img/mars.jpg"))
    {
        exit(0);
    }
    if (!tRover.loadFromFile("img/rover.png"))
    {
        exit(0);
    }
    if (!crater.loadFromFile("img/crater.png"))
    {
        exit(0);
    }
}

void Game::generateRandPosObjects(sf::Texture & texture, int n, std::vector<Object*> & v)
{
    for (int i = 0; i<n; ++i)
    {
        Object * o = new Object(texture, "krater");
        o->setOrigin(o->getGlobalBounds().width/2, o->getGlobalBounds().height/2);
        o->setPosition(rand()%3000, rand()%2000);
        v.push_back(o);
    }
}

TaskManager * Game::getTaskManager()
{
    return taskManager;
}

TaskManager::TaskManager(Game * game)
{
    this->game = game;
}

bool TaskManager::move(int x, int y)
{
    sf::Vector2f v = game->rover.getPosition();
    v.y += y;
    v.x += x;

    if (goTo(v)) return true;
        else return false;
}

bool TaskManager::goCoordinates(int x, int y) {
    sf::Vector2f v;
    v.x = x;
    v.y = y;
    if (goTo(v)) return true;
        else return false;
}

sf::Vector2f TaskManager::getCoordinates() {
    return game->rover.getPosition();
}

bool TaskManager::goTo(sf::Vector2f v)
{
    if (!game->sMap.getGlobalBounds().contains(v)) {
        error = "Podana pozycja jest poza obszarem eksploracji";
        return false;
    }


    sf::Sprite rov = game->rover;

    while (v != rov.getPosition())
    {
        sf::sleep(sf::milliseconds(5));
        rov = game->rover;

        sf::Vector2f p1 = rov.getPosition();
        p1.x -= 1;
        sf::Vector2f p2 = rov.getPosition();
        p2.x += 1;
        sf::Vector2f p3 = rov.getPosition();
        p3.y -= 1;
        sf::Vector2f p4 = rov.getPosition();
        p4.y += 1;
        sf::Vector2f p13(p1.x, p3.y);
        sf::Vector2f p14(p1.x, p4.y);
        sf::Vector2f p23(p2.x, p3.y);
        sf::Vector2f p24(p2.x, p4.y);

        std::vector<sf::Vector2f *> p;
        p.push_back(&p1);
        p.push_back(&p2);
        p.push_back(&p3);
        p.push_back(&p4);
        p.push_back(&p13);
        p.push_back(&p14);
        p.push_back(&p23);
        p.push_back(&p24);

        rov.setPosition(*Helper::minimum(p, v));

        for (std::vector<Object*> * vect : game->colliders)
        {
            for (Object * o : *vect)
            {
                if (rov.getGlobalBounds().intersects(o->getGlobalBounds()))
                {
                    error =  "Nie można przejść gdyż napotkano obiekt: " + o->getName().toAnsiString();
                    return false;
                }
            }
        }

        game->rover.setPosition(rov.getPosition());
        if (!Helper::containsRect(Helper::getViewBounds(game->view), game->rover.getGlobalBounds())) game->view.setCenter(game->rover.getPosition());
    }

    return true;
}

void TaskManager::quit() {
    game->window.close();
    exit(0);
}

sf::String TaskManager::getError() {
    return error;
}

bool TaskManager::rotate(int angle)
{
    sf::Sprite rov = game->rover;

    rov.setRotation(angle);

    for (std::vector<Object*> * vect : game->colliders)
    {
        for (Object * o : *vect)
        {
            if (rov.getGlobalBounds().intersects(o->getGlobalBounds()))
            {
                error =  "Nie można się obrócić gdyż napotkano obiekt: " + o->getName().toAnsiString();
                return false;
            }
        }
    }

    game->rover.setRotation(rov.getRotation());

    return true;
}

Object * TaskManager::getLocalObject()
{
    for (std::vector<Object*> * vect : game->colliders)
    {
        for (Object * o : *vect)
        {
            if (game->rover.getGlobalBounds().intersects(o->getGlobalBounds())) return o;
        }
    }

    return NULL;
}

bool TaskManager::goToAuto(sf::Vector2f v)
{
    //
}
