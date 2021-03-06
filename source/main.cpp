#include <iostream>
#include <SFML/Graphics.hpp>

#include "controleur.h"
#include <ctime>

using namespace sf;

//les variables globales
bool jeuEnCours=false;
bool jeuPause=false;
bool jeuFinPartie=false;
bool jeuDebut=false;
bool jeuRejouer=false;
bool boutonPresse=false;//pour savoir s'il y a clic
bool laMain=false,laMainBot=false; //laMainBot pour le CPU
int sourisX=0,sourisY=0;
bool glisser=false,deposer=false,piocher=false; //pour autoriser les actions glisser, deposer ou piocher
sf::Vector2f posFinalD; //pour enregister la position finale ou on doit mettre le domino joue par le CPU
sf::Vector2f posFinalD2;
std::vector<int > animAActiver;
bool attente=true; //pour eviter les joueurs d'effectuer des actions pendant les transitions

int main()
{
    srand(time(0));

    sf::RenderWindow fenetre(sf::VideoMode(900,700),"Domino");
    fenetre.setVerticalSyncEnabled(true);

    Controleur controleurJ(fenetre);

    while(fenetre.isOpen())
    {
        sf::Event evenement;
        while(fenetre.pollEvent(evenement))
        {
            if(evenement.type==sf::Event::Closed)
            {
                fenetre.close();
            }

            if(evenement.type==Event::MouseMoved)
            {
                sourisX=evenement.mouseMove.x;
                sourisY=evenement.mouseMove.y;
                if(!jeuEnCours)
                {
                    controleurJ.gestionDplSouris();

                }
                else if(jeuEnCours && jeuPause)
                {
                    controleurJ.gestionDplSouris();
                }
                else
                {

                }
            }

            switch(evenement.type)
            {
            case Event::MouseButtonPressed:
                if(jeuEnCours)
                {
                    if(jeuPause)
                    {
                        Mouse::Button button = evenement.mouseButton.button;

                        if (button == Mouse::Left) // Bouton gauche
                        {
                            controleurJ.gestionSelecSouris();
                            boutonPresse=true;


                        }

                        if (button == Mouse::Right) // Bouton droite
                        {

                        }

                    }
                    else
                    {
                        Mouse::Button button = evenement.mouseButton.button;

                        if (button == Mouse::Left) // Bouton gauche
                        {
                            controleurJ.gestBoutonsJeu();
                            if(laMain && !attente)
                            {
                                if(!glisser && !piocher)
                                {
                                    controleurJ.glisserDeposer(GLISSER);
                                }
                                else if(glisser && !deposer)
                                {
                                    controleurJ.glisserDeposer(DEPOSER);
                                }
                                else if(piocher)
                                {
                                    controleurJ.piocherD();
                                }
                                else
                                {

                                }
                            }
                        }

                        if (button == Mouse::Right) // Bouton droite
                        {

                        }
                    }
                }
                else
                {
                    Mouse::Button button = evenement.mouseButton.button;
                    if (button == Mouse::Left) // Bouton gauche
                    {
                        controleurJ.gestionSelecSouris();
                    }
                }

                break;

            case Event::KeyPressed:
                if(jeuEnCours)
                {
                    if(!jeuPause)
                    {
                        if(sf::Keyboard::isKeyPressed(Keyboard::Left))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Right))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Down))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Z))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::C))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Escape))
                        {

                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Space))
                        {

                        }
                        else
                        {

                        }

                    }
                    else
                    {
                        if(sf::Keyboard::isKeyPressed(Keyboard::Escape))
                        {

                        }
                    }
                }
                else
                {

                }
                break;

            case Event::KeyReleased:
                if(jeuEnCours)
                {

                }
                break;

            case Event::TextEntered:
                break;

            default:;
            }


        }

        //traitement des donnees
        controleurJ.gestionMaJ();

        if(jeuEnCours)
        {

        }
        else
        {

        }

        fenetre.clear(sf::Color(82,82,82));

        //gestion des affichages

        controleurJ.afficheFondEc();

        if(jeuEnCours)
        {
            controleurJ.afficheJeu();
        }
        else
        {
            controleurJ.afficheMenu();
        }

        fenetre.display();
    }

    return 0;
}
