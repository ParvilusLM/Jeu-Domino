#ifndef DEF_CONTROLEUR
#define DEF_CONTROLEUR

#include "decor.h"

class Controleur
{
public:
    Controleur(sf::RenderWindow& fenetre);

    void debutJeu();
    void pauseJeu();

    void gestionDplSouris();
    void gestionSelecSouris();

    void gestionMaJ();
    void gestBoutonsJeu();//gestion boutons autres que ceux du menu

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
