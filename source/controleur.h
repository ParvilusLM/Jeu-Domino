#ifndef DEF_CONTROLEUR
#define DEF_CONTROLEUR

#include "decor.h"
#include "animations.h"

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
    Animations* m_animations;


};

#endif // DEF_CONTROLEUR
