#ifndef DEF_CONTROLEUR
#define DEF_CONTROLEUR

#include "decor.h"

class Controleur
{
public:
    Controleur(sf::RenderWindow& fenetre);

    void debutJeu();

    void gestionDplSouris();
    void gestionSelecSelecSouris();

    gestionMaJ();

    void afficheMenu();
    void afficheFondEc();
    void afficheJeu();
    void afficheInfo();

    ~Controleur();

private:
    sf::RenderWindow* m_fenetre;
    Decor* m_decor;


};

#endif // DEF_CONTROLEUR
