#include "decor.h"

Decor::Decor(sf::RenderWindow& fenetre):m_fenetre(0),m_menu(0),m_info(0),m_son(0),m_joueur(0)
{
    m_fenetre=&fenetre;

    m_menu= new Menu(*m_fenetre);
    m_info= new Info(*m_fenetre);
    m_son= new Son(*m_fenetre);
    m_joueur= new Joueur(*m_fenetre);

    m_tFondG.loadFromFile("donnees/fondEc.png");
    m_sFondG.setTexture(m_tFondG);
}

Menu& Decor::getMenu()
{
    return *m_menu;
}

Info& Decor::getInfo()
{
    return *m_info;
}

Son& Decor::getSon()
{
    return *m_son;
}

Joueur& Decor::getJoueur()
{
    return *m_joueur;
}

void Decor::afficheFondEc()
{
    m_fenetre->draw(m_sFondG);
}

Decor::~Decor()
{
    delete m_menu;
    delete m_info;
    delete m_son;
    delete m_joueur;
}

