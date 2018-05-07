#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

//Init game const
    const double SCREEN_WIDTH=800;
    const double SCREEN_HEIGH=600;
    const int borderLeft=140;
    const int borderRight=660;
    const int racerWidth=40;
    const int racerHeight=70;
    string stringscore="";
    int score=0;
    double gameSpeed=0.3;

//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");

//Creat random Number for game loop
int getRandomNumber(int a, int b);

// Create gameover screen
int gameOver();

int main()
{
    //Init game music
    SoundBuffer gameSoundBuffer;
        gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
        GameSound.setBuffer(gameSoundBuffer);

    Texture background, racer, obs1, obs2, obs3, obs4,gameover;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/xirod.ttf");

    //Load all images
    if (!background.loadFromFile("cars/background.png")) return EXIT_FAILURE;
    if (!racer.loadFromFile("cars/racer.png")) return EXIT_FAILURE;
    if (!obs1.loadFromFile("cars/obs1.png")) return EXIT_FAILURE;
    if (!obs2.loadFromFile("cars/obs2.png")) return EXIT_FAILURE;
    if (!obs3.loadFromFile("cars/obs3.png")) return EXIT_FAILURE;
    if (!obs4.loadFromFile("cars/obs4.png")) return EXIT_FAILURE;

    //Create sprite
    Sprite Background(background),Background1(background),Racer(racer),Obs1(obs1),Obs2(obs2),Obs3(obs3),Obs4(obs4),Gameover(gameover);

    double RacerX, RacerY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y;

    //Set racer and Obs pos
	RacerX=SCREEN_WIDTH/2;
	RacerY=SCREEN_HEIGH-racerHeight;
	Obs1X=getRandomNumber(borderLeft,borderRight);
	Obs2X=getRandomNumber(borderLeft,borderRight);
	Obs3X=getRandomNumber(borderLeft,borderRight);
	Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300;
    double BackgroundY1=0;
    double BackgroundY2=-600;

    GameSound.play();
    GameSound.setLoop(true);

    //GAME LOOP
    while (app.isOpen())
    {
        //Init and count score
        stringscore="SCORE:"+to_string(score);
        Text text(stringscore, myfont, 15);
        text.setPosition(5,0);

        //Set car position
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);

        //Creat scrolling background
        Background.setPosition(0,BackgroundY1);
        Background1.setPosition(0,BackgroundY2);
        if (BackgroundY2>0)
        {
            BackgroundY1=0;
            BackgroundY2=BackgroundY1-500;
        }
        BackgroundY1+=0.1;
        BackgroundY2+=0.1;

        //Set Obs LOOP
        if (Obs1Y>SCREEN_HEIGH)
            {Obs1Y=0;Obs1X=getRandomNumber(borderLeft,borderRight);score++;} else {Obs1Y=Obs1Y+gameSpeed;}
        if (Obs2Y>SCREEN_HEIGH)
            {Obs2Y=0;Obs2X=getRandomNumber(borderLeft,borderRight);score++;} else {Obs2Y=Obs2Y+gameSpeed;}
        if (Obs3Y>SCREEN_HEIGH)
            {Obs3Y=0;Obs3X=getRandomNumber(borderLeft,borderRight);score++;} else {Obs3Y=Obs3Y+gameSpeed;}
        if (Obs4Y>SCREEN_HEIGH)
            {Obs4Y=0;Obs4X=getRandomNumber(borderLeft,borderRight);score++;} else {Obs4Y=Obs4Y+gameSpeed;}

        //Game level
        if(score>10 && score<18) {gameSpeed=0.4;}
        if(score>18 && score<25) {gameSpeed=0.5;}
        if(score>25 && score<35) {gameSpeed=0.6;}

        //Create event to handle input from keyboard
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

        //Check if accident happen
        if (((RacerX>=(Obs1X-30)) &&(RacerX<=(Obs1X+30)))&&((RacerY>=(Obs1Y-30)) &&(RacerY)<=(Obs1Y+30)))
            {
                GameSound.stop();gameOver();
            };
        if (((RacerX>=(Obs2X-30)) &&(RacerX<=(Obs2X+30)))&&((RacerY>=(Obs2Y-30)) &&(RacerY)<=(Obs2Y+30)))
            {
                GameSound.stop();gameOver();
            };
        if (((RacerX>=(Obs3X-30)) &&(RacerX<=(Obs3X+30)))&&((RacerY>=(Obs3Y-30)) &&(RacerY)<=(Obs3Y+30)))
            {
                GameSound.stop();gameOver();
            };
        if (((RacerX>=(Obs4X-30)) &&(RacerX<=(Obs4X+30)))&&((RacerY>=(Obs4Y-30)) &&(RacerY)<=(Obs4Y+30)))
            {
                GameSound.stop();gameOver();
            };

        //Clear and redraw position
        app.clear();
        app.draw(Background);
        app.draw(Background1);
        app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text);
        app.display();
    }
    return EXIT_SUCCESS;
}
int startGame()
{
    //TODO
}
//Game over
int gameOver()
{
    Texture gameover,troll;
        if (!gameover.loadFromFile("cars/over.png")) return EXIT_FAILURE;
        if(!troll.loadFromFile("cars/troll.png")) return EXIT_FAILURE;

    Sprite Gameover(gameover);
    Sprite Troll(troll);
    Troll.setPosition(10,350);
    SoundBuffer gameOver;
        gameOver.loadFromFile("sound/crash.wav");
    Sound GameOver;
        GameOver.setBuffer(gameOver);
        GameOver.play();
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        Font myfont;
            myfont.loadFromFile("font/xirod.ttf");
            stringscore="YOUR SCORE:"+to_string(score);
        Text text(stringscore, myfont, 30);
            text.setPosition(210,450);
        app.clear();
        app.draw(Gameover);
        app.draw(text);
        app.draw(Troll);
        app.display();

    }

}
int getRandomNumber(int a, int b)
    {
        static bool first = true; if (first){srand( time(NULL) );first = false;}
        int result=a + rand() % (( b + 1 ) - a);
        result=(result/10)*10;
        return result;
    }
