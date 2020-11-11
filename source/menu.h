#ifndef DEF_MENU
#define DEF_MENU

#include "enums.h"
#include "constantes.h"
#include "varG.h"

class Menu
{
public:
    Menu(sf::RenderWindow& fenetre);

    void initMenuP();
    void initMenuSelectP();
    void initMenuI();
    void initMenuPause();
    void initMenuFinPart();

    void setTypeMenu(int menuActuel);
    TypeMenu getTypeMenu();

    void retourMenuP();
    void elementActif();
    void selectionElActif();
    bool collisionTS(sf::FloatRect elem);
    int getBoutonPress();
    void resetBoutonPress();
    void quitterJeu();

    void gestTexture(int bouton, int type);

    void afficheMenuP();
    void afficheMenuSelectP();
    void afficheMenuI();
    void afficheMenuPause();
    void afficheMenuFinPart();
    void afficheMenu();

    ~Menu();

private:
    sf::RenderWindow* m_fenetre;

    TypeMenu m_typeMenu;
    sf::Font m_font;
    sf::Font m_font2;
    sf::Font m_font3;

    int m_elementActif;

    int m_boutonPress;

    //textures pour les boutons
    sf::Texture m_tSelectInstr,m_tSelectMP,m_tSelectTypeJ,m_tSelectMPause,m_tSelectMGO;

    //sprites pour les boutons
    sf::Sprite m_sbInfo,m_sbSon,m_sbJoueur1;//menuPrincipal
    sf::Sprite m_sbMenu,m_sbType1,m_sbType2,m_sbType3,m_sbType4,m_sbNiveau1,m_sbNiveau2,m_sbNiveau3,m_sbJouer;//menuSelectTypeJ
    sf::Sprite m_sbOk;//menuInstructions
    sf::Sprite m_sbResume,m_sbRejouer,m_sbInstructions,m_sbQuitter;//menuPause
    sf::Sprite m_sbMenuFP,m_sbRejouerFP;//menu finPartie


    //pour menu principal
    sf::Texture m_tMenuP;
    sf::Sprite m_sMenuP;

    //pour menu TypeJeu
    sf::Texture m_tTypeJeu;
    sf::Sprite m_sTypeJeu;

    //pour menu instructions
    sf::Texture m_tMenuI;
    sf::Sprite m_sMenuI;

    sf::Texture m_tMenuI1;
    sf::Sprite m_sMenuI1;

    sf::Texture m_tMenuI2;
    sf::Sprite m_sMenuI2;

    sf::Texture m_tMenuI3;
    sf::Sprite m_sMenuI3;

    sf::Texture m_tMenuI4;
    sf::Sprite m_sMenuI4;


    //pour menu pause
    sf::Texture m_tMenuPause;
    sf::Sprite m_sMenuPause;

    //pour menu fin partie
    sf::Texture m_tMenuFinP;
    sf::Sprite m_sMenuFinP;


};


#endif // DEF_MENU
