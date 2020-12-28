#ifndef DEF_JOUEUR
#define DEF_JOEUEUR

#include <iostream>
#include "enums.h"
#include "constantes.h"
#include "varG.h"



class Joueur
{
public:
    Joueur(sf::RenderWindow& fenetre);

    void initPlateauJeu();
    void melangeDomino();
    void distribuerDomino();
    void piocherDomino(int joueur);
    bool selectionDomino(int joueur);
    bool coupPossible(int joueur, ElDomino& domino);
    bool placerDomino(int joueur, int noDominoP,int noDominoE); //noDominoP represente le domino sur lequel on va attacher le nouveau
    //noDominoE represente le position du domino dans le vecteurDominos du joueur correspondant non pas son noDomino

    void arrangerDomino(int noCadre); //pour arranger les dominos dans les cadres
    void retourneDominos(int joueur,bool rendreVisible);
    void changementEchelleD(int categorie,sf::Vector2f facteur);
    void glisserDeposerD(int action);

    PlateauJeu& getPlateauJeu();
    bool finPartie();
    void gestTextureD();

    bool collisionTS(sf::FloatRect elem);
    bool boutonSelect();
    void gestBouton();

    void gestMaj();

    //gestion type de jeu Memory
    void selectionDominoTMem(int joueur);
    void gestionSelectionDom();


    void affichePartie();
    void afficheBouton();

    ~Joueur();

private:
    sf::RenderWindow* m_fenetre;
    PlateauJeu m_plateauJeu;
    sf::Texture m_tFond,m_tDominos,m_tElements;
    sf::Sprite m_sFond;

    //bouton pause
    sf::Sprite m_sbPause;

    //pour le bot
    sf::Vector2f m_positionFinal;
    std::vector<int > m_vecDominoABouger;


};

#endif // DEF_JOUEUR
