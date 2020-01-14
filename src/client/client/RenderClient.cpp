#include "../client.h"
#include "../render.h"


#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;

RenderClient::RenderClient()
{

}

void RenderClient::runRender()
{
    cout << "---------------render ---------------------" << endl;
    State state;
    
    state.initPlayers();            

    //initiate Terrain
    state.setTerrain(FlintTerrain); // ThorkTerrain, FlintTerrain, KuroTerrain
    
    TextureManager *textureManager = textureManager->getInstance();
    if (textureManager->load())
    {
        cout << "texuture manager ok!" << endl;
    }
    else
    {
        cout << "texuture manager loading failed!" << endl;
        //return EXIT_FAILURE;
    }

    sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");
  
    //registering statelayer to observer
    StateLayer stateLayer(window, state);
    state.registerObserver(&stateLayer);
   
    bool attackPress = false;

    stateLayer.draw();
    //cout << "drawing ok!" << endl;

    while (window.isOpen())
    {
        // Close the window if the close button is pressed
        sf::Event event;
        sf::Font font;
        if (!font.loadFromFile("./res/Fonts/FontFile.ttf"))
        {
            cout << "font loading failed!" << endl;
            //return false;
            
        }
        sf::Text text1;
        text1.setFont(font);
        text1.setString("Health Points");
        text1.setCharacterSize(40);

        sf::Text text2;
        text2.setFont(font);
        text2.setString("Health Points");
        text2.setCharacterSize(40);
        text2.setPosition(530.f, 0.f);

        sf::Texture hpBarTexture;
        if (!hpBarTexture.loadFromFile("./res/redBg.jpg", sf::IntRect(0, 0, 100, 10)))
        {
            cout << "hpBAr loading failed!" << endl;
            //return false;
        }

        sf::Sprite hpBarP1;
        hpBarP1.setTexture(hpBarTexture);
        hpBarP1.setPosition(0.f, 40.f);

        sf::Sprite hpBarP2;
        hpBarP2.setTexture(hpBarTexture);
        hpBarP2.setPosition(530.f, 40.f);

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::A:
                    cout << " touche A ENCLENCHE" << endl;
                    attackPress = true;
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::MouseMoved:
                break;
            default:
                state.notifyObservers({StateEventID::ALLCHANGED}, state);
                break;
            }
        }

        sf::Texture arena;
        sf::Sprite arenaSprite;
        int frame = 0;
        int row = 1;
        int frameCounter = 0;


        if (!arena.loadFromFile("./res/Terrains/seku_terrain.png"))
    {
        std::cout << "Load Failed" << std::endl;
        system("Pause");
    }
    
    arenaSprite.setTexture(arena);

    //display fighter1
    sf::Texture spriteSheet;
    
    if (!spriteSheet.loadFromFile("./res/Fighters/Kuro.png")) //,rectSourceSprite));
    {
        std::cout << "Load Failed" << std::endl;
        system("Pause");
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(spriteSheet);
    // put fighter on the right of the arena
    playerSprite.setPosition(sf::Vector2f(50.f, 250.f));

        if (attackPress)
        {
            playerSprite.setTextureRect(sf::IntRect(100 * frame, 100 * row, 100, 100));
            if (frameCounter == 100)
            {
                frame = (frame + 1) % 3;
                frameCounter = 0;
            }
            frameCounter++;
        }
        // cout << "frame = " << frame << endl;
        // cout << "frame counter = " << frameCounter << endl;

        
    }
}
    

