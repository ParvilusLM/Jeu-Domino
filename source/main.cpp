#include <iostream>
#include <SFML/Graphics.hpp>

#include "controleur.h"

using namespace std;



int main()
{
    srand(time(0));

    sf::RenderWindow fenetre(sf::VideoMode(900,700),"Domino");
    fenetre.setVerticalSyncEnabled(true);

    while(fenetre.isOpen())
    {
        sf::Event evenement;
        while(fenetre.pollEvent(evenement))
        {
            if(evenement.type==sf::Event::Closed)
            {
                fenetre.close();
            }
        }

        fenetre.clear(sf::Color(82,82,82));

        fenetre.display();
    }

    return 0;
}
