#ifndef DEF_DECOR
#define DEF_DECOR

#include "menu.h"
#include "info.h"
#include "son.h"
#include "joueur.h"

class Decor
{
public:
    Decor(sf::RenderWindow& fenetre);
    Menu& getMenu();
    Info& getInfo();
    Son& getSon();
    Joueur& getJoueur();

    void afficheFondEc();

    ~Decor();



private:
    sf::RenderWindow* m_fenetre;
    Menu* m_menu;
    Info* m_info;
    Son* m_son;
    Joueur* m_joueur;

    sf::Texture m_tFondG;
    sf::Sprite m_sFondG;

};

#endif // DEF_DECOR
