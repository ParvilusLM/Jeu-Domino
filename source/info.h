#ifndef DEF_INFO
#define DEF_INFO

#include "enums.h"
#include "constantes.h"
#include "varG.h"

class Info
{
public:
    Info(sf::RenderWindow& fenetre);

    //initialisation
    void initInfo();

    //traitement donnees
    void gestInfoPartEnCours();
    void majInfo();
    int getDonnees(int typDonnees);
    void setDonnees(int typDonnees, int action, int valeur=0);

    //affichage
    void afficheInfo();

    ~Info();

private:
    sf::RenderWindow* m_fenetre;

    //info joueur1
    sf::Text


    //info joueur2



};

#endif // DEF_INFO
