#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>

using namespace std;
using namespace sf;

int getRandomNumber(int a, int b)
    {static bool first = true; if (first){srand( time(NULL) );first = false;} return a + rand() % (( b + 1 ) - a);}

int main()
{
    const double SCREEN_WIDTH=800;
    const double SCREEN_HEIGH=600;
    const int borderLeft=140;
    const int borderRight=660;
    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");

    Texture background, racer, obs1, obs2, obs3, obs4;
    if (!background.loadFromFile("cars/background.png")) return EXIT_FAILURE;
    if (!racer.loadFromFile("cars/racer.png")) return EXIT_FAILURE;
    if (!obs1.loadFromFile("cars/obs1.png")) return EXIT_FAILURE;
    if (!obs2.loadFromFile("cars/obs2.png")) return EXIT_FAILURE;
    if (!obs3.loadFromFile("cars/obs3.png")) return EXIT_FAILURE;
    if (!obs4.loadFromFile("cars/obs4.png")) return EXIT_FAILURE;

    Sprite Background(background),
            Racer(racer),
            Obs1(obs1),
            Obs2(obs2),
            Obs3(obs3),
            Obs4(obs4);

    double RacerX, RacerY,
           Obs1X, Obs1Y,
           Obs2X, Obs2Y,
           Obs3X, Obs3Y,
           Obs4X, Obs4Y;

	RacerX=SCREEN_WIDTH/2;
	RacerY=SCREEN_HEIGH-70;
	Obs1X=getRandomNumber(borderLeft,borderRight);
	Obs2X=getRandomNumber(borderLeft,borderRight);
	Obs3X=getRandomNumber(borderLeft,borderRight);
	Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=0,Obs3Y=0,Obs4Y=0;
    while (app.isOpen())
    {
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);

        if (Obs1Y>SCREEN_HEIGH)
        {
            Obs1Y=0;
            Obs1X=getRandomNumber(borderLeft,borderRight);
        } else {Obs1Y=Obs1Y+0.3;}
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        {if(RacerX>borderLeft) {RacerX=RacerX-10;}}
                    if (event.key.code == sf::Keyboard::Right)
                        {if(RacerX<borderRight){RacerX=RacerX+10;}}
                    if (event.key.code == sf::Keyboard::Up)
                        {if(RacerY>0){RacerY=RacerY-10;}}
                    if (event.key.code == sf::Keyboard::Down)
                        {if(RacerY<SCREEN_HEIGH-70){RacerY=RacerY+10;}}
                }
        }
        app.clear();
        app.draw(Background);
        app.draw(Racer);
        app.draw(Obs1);
        app.display();
    }
    return EXIT_SUCCESS;
}
