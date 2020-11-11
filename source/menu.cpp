#include "menu.h"

using namespace std;

Menu::Menu(sf::RenderWindow& fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;

    //textures pour les boutons
    m_tSelectMP.loadFromFile("donnees/bMenuP.png");
    m_tSelectInstr.loadFromFile("donnees/bInstructions.png");
    m_tSelectTypeJ.loadFromFile("donnees/bTypeJeu.png");
    m_tSelectMPause.loadFromFile("donnees/bMenuPause.png");
    m_tSelectMGO.loadFromFile("donnees/bGameOver.png");

    //sprites pour les boutons
    m_sbInfo.setTexture(m_tSelectMP);
    m_sbInfo.setPosition(1.f*20.f,1.f*20.f);
    gestTexture(B_INFO,1);

    m_sbSon.setTexture(m_tSelectMP);
    m_sbSon.setPosition(39.f*20.f,1*20.f);
    gestTexture(B_SON,1);

    m_sbJoueur1.setTexture(m_tSelectMP);
    m_sbJoueur1.setPosition(24.5f*20.f,28.5f*20.f);
    gestTexture(B_JOUEUR1,1);


    m_sbMenu.setTexture(m_tSelectTypeJ);
    m_sbMenu.setPosition(1.f*20.f,1.f*20.f);
    gestTexture(B_MENU,1);

    m_sbType1.setTexture(m_tSelectTypeJ);
    m_sbType1.setPosition(11.5f*20.f,11.2f*20.f);
    gestTexture(B_TYPE1,1);

    m_sbType2.setTexture(m_tSelectTypeJ);
    m_sbType2.setPosition(22.5f*20.f,11.2f*20.f);
    gestTexture(B_TYPE2,1);

    m_sbType3.setTexture(m_tSelectTypeJ);
    m_sbType3.setPosition(11.5f*20.f,13.4f*20.f);
    gestTexture(B_TYPE3,1);

    m_sbType4.setTexture(m_tSelectTypeJ);
    m_sbType4.setPosition(22.5f*20.f,13.4f*20.f);
    gestTexture(B_TYPE4,1);

    m_sbNiveau1.setTexture(m_tSelectTypeJ);
    m_sbNiveau1.setPosition(11.5f*20.f,20.8f*20.f);
    gestTexture(B_NIVEAU1,1);

    m_sbNiveau2.setTexture(m_tSelectTypeJ);
    m_sbNiveau2.setPosition(17.9*20.f,20.8f*20.f);
    gestTexture(B_NIVEAU2,1);

    m_sbNiveau3.setTexture(m_tSelectTypeJ);
    m_sbNiveau3.setPosition(25.4f*20.f,20.8f*20.f);
    gestTexture(B_NIVEAU3,1);

    m_sbOk.setTexture(m_tSelectInstr);
    m_sbOk.setPosition(20.5f*20.f,27.f*20.f);
    gestTexture(B_OK,1);

    m_sbResume.setTexture(m_tSelectMPause);
    m_sbResume.setPosition(16.5f*20.f,10.f*20.f);
    gestTexture(B_PAUSER,1);

    m_sbRejouer.setTexture(m_tSelectMPause);
    m_sbRejouer.setPosition(16.5f*20.f,14.f*20.f);
    gestTexture(B_PAUSEREJ,1);

    m_sbInstructions.setTexture(m_tSelectMPause);
    m_sbInstructions.setPosition(16.5f*20.f,18.f*20.f);
    gestTexture(B_PAUSEI,1);

    m_sbQuitter.setTexture(m_tSelectMPause);
    m_sbQuitter.setPosition(16.5f*20.f,22.f*20.f);
    gestTexture(B_PAUSEQ,1);

    m_sbMenuFP.setTexture(m_tSelectMGO);
    m_sbMenuFP.setPosition(16.f*20.f,27.f*20.f);
    gestTexture(B_FINPQ,1);

    m_sbRejouerFP.setTexture(m_tSelectMGO);
    m_sbRejouerFP.setPosition(26.5f*20.f,27.f*20.f);
    gestTexture(B_FINPR,1);



    //textures pour les differents menus
    m_tMenuI.loadFromFile("donnees/instructions.png");
    m_tMenuI1.loadFromFile("donnees/instruct1.png");
    m_tMenuI2.loadFromFile("donnees/instruct2.png");
    m_tMenuI3.loadFromFile("donnees/instruct3.png");
    m_tMenuI4.loadFromFile("donnees/instruct4.png");
    m_tMenuPause.loadFromFile("donnees/menuPause.png");
    m_tMenuFinP.loadFromFile("donnees/gameOver.png");
    m_tTypeJeu.loadFromFile("donnees/typeJeu.png");


    m_typeMenu=MenuPrincipal;

    initMenuP();
    initMenuI();
    initMenuSelectP();
    initMenuPause();
    initMenuFinPart();

    m_boutonPress=AUCUN_EL_ACT;


}

void Menu::initMenuP()
{
    //m_sMenuP.setTexture(m_tMenuP);
}

void Menu::initMenuSelectP()
{
    m_sTypeJeu.setTexture(m_tTypeJeu);
}

void Menu::initMenuI()
{
    m_sMenuI.setTexture(m_tMenuI);
}

void Menu::initMenuPause()
{
    m_sMenuPause.setTexture(m_tMenuPause);
}

void Menu::initMenuFinPart()
{
    m_sMenuFinP.setTexture(m_tMenuFinP);
}

void Menu::setTypeMenu(int menuActuel)
{
    if(menuActuel==MenuPrincipal)
    {
        m_typeMenu=MenuPrincipal;
    }
    else if(menuActuel==MenuInstructions)
    {
        m_typeMenu=MenuInstructions;
    }
    else if(menuActuel==MenuSelectTypeJ)
    {
        m_typeMenu=MenuSelectTypeJ;
    }
    else if(menuActuel==MenuPause)
    {
        m_typeMenu=MenuPause;
    }
    else if(menuActuel==MenuFinPartie)
    {
        m_typeMenu=MenuFinPartie;
    }
    else
    {

    }
}

TypeMenu Menu::getTypeMenu()
{
    return m_typeMenu;
}

void Menu::retourMenuP()
{
    m_typeMenu=MenuPrincipal;
    m_elementActif=AUCUN_EL_ACT;
}

void Menu::elementActif()
{
    int compt=0;
    while(compt<15)
    {
        gestTexture(compt,1);
        compt++;
    }

    if(m_typeMenu==MenuPrincipal)
    {
        if(collisionTS(m_sbJoueur1.getGlobalBounds()))
        {
            m_elementActif=JOUEUR1_ACTIF;
            gestTexture(B_JOUEUR1,2);
        }
        else if(collisionTS(m_sbInfo.getGlobalBounds()))
        {
            m_elementActif=INSTRUCTIONS_ACTIF;
            gestTexture(B_INFO,2);
        }
        else if(collisionTS(m_sbSon.getGlobalBounds()))
        {
            m_elementActif=SON_ACTIF;
            gestTexture(B_SON,2);
        }
        else
        {
            m_elementActif=AUCUN_EL_ACT;
            gestTexture(B_JOUEUR1,1);
            gestTexture(B_INFO,1);
            gestTexture(B_SON,1);
        }

    }
    else if(m_typeMenu==MenuSelectTypeJ)
    {
        if(collisionTS(m_sbMenu.getGlobalBounds()))
        {
            m_elementActif=MENU_ACTIF;
            gestTexture(B_MENU,2);
        }
        else if(collisionTS(m_sbType1.getGlobalBounds()))
        {
            m_elementActif=TYPE1_ACTIF;
            gestTexture(B_TYPE1,2);
        }
        else if(collisionTS(m_sbType2.getGlobalBounds()))
        {
            m_elementActif=TYPE2_ACTIF;
            gestTexture(B_TYPE2,2);
        }
        else if(collisionTS(m_sbType3.getGlobalBounds()))
        {
            m_elementActif=TYPE3_ACTIF;
            gestTexture(B_TYPE3,2);
        }
        else if(collisionTS(m_sbType4.getGlobalBounds()))
        {
            m_elementActif=TYPE4_ACTIF;
            gestTexture(B_TYPE4,2);
        }
        else if(collisionTS(m_sbNiveau1.getGlobalBounds()))
        {
            m_elementActif=NIVEAU1_ACTIF;
            gestTexture(B_NIVEAU1,2);
        }
        else if(collisionTS(m_sbNiveau2.getGlobalBounds()))
        {
            m_elementActif=NIVEAU2_ACTIF;
            gestTexture(B_NIVEAU2,2);
        }
        else if(collisionTS(m_sbNiveau3.getGlobalBounds()))
        {
            m_elementActif=NIVEAU3_ACTIF;
            gestTexture(B_NIVEAU3,2);
        }
        else
        {
            m_elementActif=AUCUN_EL_ACT;
            gestTexture(B_MENU,1);
            gestTexture(B_TYPE1,1);
            gestTexture(B_TYPE2,1);
            gestTexture(B_TYPE3,1);
            gestTexture(B_TYPE4,1);
            gestTexture(B_NIVEAU1,1);
            gestTexture(B_NIVEAU2,1);
            gestTexture(B_NIVEAU3,1);
        }
    }
    else if(m_typeMenu==MenuInstructions)
    {
        if(collisionTS(m_sbOk.getGlobalBounds()))
        {
            m_elementActif=OK_ACTIF;
            gestTexture(B_OK,2);
        }
        else
        {
            m_elementActif=AUCUN_EL_ACT;
            gestTexture(B_OK,1);
        }
    }
    else if(m_typeMenu==MenuPause)
    {
        if(collisionTS(m_sbResume.getGlobalBounds()))
        {
            m_elementActif=PAUSER_ACTIF;
            gestTexture(B_PAUSER,2);
        }
        else if(collisionTS(m_sbRejouer.getGlobalBounds()))
        {
            m_elementActif=PAUSEREJ_ACTIF;
            gestTexture(B_PAUSEREJ,2);
        }
        else if(collisionTS(m_sbInstructions.getGlobalBounds()))
        {
            m_elementActif=PAUSEI_ACTIF;
            gestTexture(B_PAUSEI,2);
        }
        else if(collisionTS(m_sbQuitter.getGlobalBounds()))
        {
            m_elementActif=PAUSEQ_ACTIF;
            gestTexture(B_PAUSEQ,2);
        }
        else
        {
            m_elementActif=AUCUN_EL_ACT;
            gestTexture(B_PAUSER,1);
            gestTexture(B_PAUSEREJ,1);
            gestTexture(B_PAUSEI,1);
            gestTexture(B_PAUSEQ,1);
        }

    }
    else if(m_typeMenu==MenuFinPartie)
    {
        if(collisionTS(m_sbMenuFP.getGlobalBounds()))
        {
            m_elementActif=FINPQ_ACTIF;
            gestTexture(B_FINPQ,2);
        }
        else if(collisionTS(m_sbRejouerFP.getGlobalBounds()))
        {
            m_elementActif=FINPR_ACTIF;
            gestTexture(B_FINPR,2);
        }
        else
        {
            m_elementActif=AUCUN_EL_ACT;
            gestTexture(B_FINPQ,1);
            gestTexture(B_FINPR,1);
        }

    }
    else
    {

    }

}

void Menu::selectionElActif()
{
    if(m_typeMenu==MenuPrincipal)
    {
        if(m_elementActif==JOUEUR1_ACTIF)
        {
            m_boutonPress=B_JOUEUR1;
            boutonPresse=true;
            m_typeMenu=MenuSelectTypeJ;

        }
        else if(m_elementActif==INSTRUCTIONS_ACTIF)
        {
            m_boutonPress=B_INFO;
            boutonPresse=true;
            m_typeMenu=MenuInstructions;
        }
        else if(m_elementActif==SON_ACTIF)
        {
            m_boutonPress=B_SON;
            boutonPresse=true;
        }
        else
        {

        }

    }
    else if(m_typeMenu==MenuSelectTypeJ)
    {
        if(m_elementActif==MENU_ACTIF)
        {
            m_typeMenu=MenuPrincipal;
            m_boutonPress=B_MENU;
            boutonPresse=true;
        }
        else if(m_elementActif==TYPE1_ACTIF)
        {
            m_boutonPress=B_TYPE1;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==TYPE2_ACTIF)
        {
            m_boutonPress=B_TYPE2;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==TYPE3_ACTIF)
        {
            m_boutonPress=B_TYPE3;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==TYPE4_ACTIF)
        {
            m_boutonPress=B_TYPE4;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==NIVEAU1_ACTIF)
        {
            m_boutonPress=B_NIVEAU1;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==NIVEAU2_ACTIF)
        {
            m_boutonPress=B_NIVEAU2;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==NIVEAU3_ACTIF)
        {
            m_boutonPress=B_NIVEAU3;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else
        {

        }
    }
    else if(m_typeMenu==MenuInstructions)
    {
        if(m_elementActif==OK_ACTIF)
        {
            if(!jeuEnCours)
            {
                m_typeMenu=MenuPrincipal;
                m_boutonPress=B_OK;
                boutonPresse=true;
            }
            else
            {
                m_typeMenu=MenuPause;
                m_boutonPress=B_OK;
                boutonPresse=true;
            }
        }
        else
        {

        }
    }
    else if(m_typeMenu==MenuPause)
    {
        if(m_elementActif==PAUSER_ACTIF)
        {
            jeuPause=false;
            m_boutonPress=B_PAUSER;
            boutonPresse=true;

        }
        if(m_elementActif==PAUSEREJ_ACTIF)
        {
            jeuPause=false;
            m_boutonPress=B_PAUSEREJ;
            boutonPresse=true;

        }
        else if(m_elementActif==PAUSEI_ACTIF)
        {
            m_typeMenu=MenuInstructions;
            m_boutonPress=B_PAUSEI;
            boutonPresse=true;
        }
        else if(m_elementActif==PAUSEQ_ACTIF)
        {
            jeuPause=false;
            jeuEnCours=false;
            jeuDebut=false;
            m_typeMenu=MenuPrincipal;
            m_boutonPress=B_PAUSEQ;
            boutonPresse=true;
        }
        else
        {

        }
    }
    else if(m_typeMenu==MenuFinPartie)
    {
        if(m_elementActif==FINPQ_ACTIF)
        {
            m_boutonPress=B_FINPQ;
            boutonPresse=true;
        }
        else if(m_elementActif==FINPR_ACTIF)
        {
            jeuPause=false;
            jeuRejouer=true;
            m_typeMenu=MenuPrincipal;
            m_boutonPress=B_FINPR;
            boutonPresse=true;
        }
        else
        {

        }
    }
    else
    {

    }

    m_elementActif=AUCUN_EL_ACT;

}

bool Menu::collisionTS(sf::FloatRect elem)
{
    bool collision=false;
    if((elem.left<sourisX && elem.left+elem.width>sourisX) &&
       (elem.top<sourisY && elem.top+elem.height>sourisY))
    {
        collision=true;
    }
    return collision;
}

int Menu::getBoutonPress()
{
    return m_boutonPress;
}

void Menu::resetBoutonPress()
{
    m_boutonPress=AUCUN_B_PRESSE;
}

void Menu::quitterJeu()
{
    m_fenetre->close();
}

void Menu::gestTexture(int bouton, int type)
{
    if(bouton==B_INFO)
    {
        if(type==1)
        {
            m_sbInfo.setTextureRect(sf::IntRect(1*20,1*20,5*20,5*20));
        }
        else
        {
            m_sbInfo.setTextureRect(sf::IntRect(8*20,1*20,5*20,5*20));
        }
    }
    else if(bouton==B_SON)
    {
        if(type==1)
        {
            m_sbSon.setTextureRect(sf::IntRect(1*20,8*20,5*20,5*20));
        }
        else
        {
            m_sbSon.setTextureRect(sf::IntRect(8*20,8*20,5*20,5*20));
        }
    }
    else if(bouton==B_JOUEUR1)
    {
        if(type==1)
        {
            m_sbJoueur1.setTextureRect(sf::IntRect(1*20,16*20,16*20,4*20));
        }
        else
        {
            m_sbJoueur1.setTextureRect(sf::IntRect(1*20,22*20,16*20,4*20));
        }
    }
    else if(bouton==B_OK)
    {
        if(type==1)
        {
            m_sbOk.setTextureRect(sf::IntRect(1*20,23*20,4*20,4*20));
        }
        else
        {
            m_sbOk.setTextureRect(sf::IntRect(1*20,6*20,4*20,4*20));
        }
    }
    else if(bouton==B_MENU)
    {
        if(type==1)
        {
            m_sbMenu.setTextureRect(sf::IntRect(1*20,23*20,5*20,5*20));
        }
        else
        {
            m_sbMenu.setTextureRect(sf::IntRect(7*20,23*20,5*20,5*20));
        }
    }
    else if(bouton==B_TYPE1)
    {
        if(type==1)
        {
            m_sbType1.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbType1.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_TYPE2)
    {
        if(type==1)
        {
            m_sbType2.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbType2.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_TYPE3)
    {
        if(type==1)
        {
            m_sbType3.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbType3.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_TYPE4)
    {
        if(type==1)
        {
            m_sbType4.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbType4.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_NIVEAU1)
    {
        if(type==1)
        {
            m_sbNiveau1.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbNiveau1.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_NIVEAU2)
    {
        if(type==1)
        {
            m_sbNiveau2.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbNiveau2.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_NIVEAU3)
    {
        if(type==1)
        {
            m_sbNiveau3.setTextureRect(sf::IntRect(2*20,20*20,2*20,2*20));
        }
        else
        {
            m_sbNiveau3.setTextureRect(sf::IntRect(6*20,20*20,2*20,2*20));
        }
    }
    else if(bouton==B_PAUSER)
    {
        if(type==1)
        {
            m_sbResume.setTextureRect(sf::IntRect(0,0,12*20,3*20));
        }
        else
        {
            m_sbResume.setTextureRect(sf::IntRect(0,16*20,12*20,3*20));
        }
    }
    else if(bouton==B_PAUSEREJ)
    {
        if(type==1)
        {
            m_sbRejouer.setTextureRect(sf::IntRect(0,4*20,12*20,3*20));
        }
        else
        {
            m_sbRejouer.setTextureRect(sf::IntRect(0,20*20,12*20,3*20));
        }
    }
    else if(bouton==B_PAUSEI)
    {
        if(type==1)
        {
            m_sbInstructions.setTextureRect(sf::IntRect(0,8*20,12*20,3*20));
        }
        else
        {
            m_sbInstructions.setTextureRect(sf::IntRect(0,24*20,12*20,3*20));
        }
    }
    else if(bouton==B_PAUSEQ)
    {
        if(type==1)
        {
            m_sbQuitter.setTextureRect(sf::IntRect(0,12*20,12*20,3*20));
        }
        else
        {
            m_sbQuitter.setTextureRect(sf::IntRect(0,28*20,12*20,3*20));
        }
    }
    else if(bouton==B_FINPQ)
    {
        if(type==1)
        {
            m_sbMenuFP.setTextureRect(sf::IntRect(1*20,10*20,2.5*20,2.5*20));
        }
        else
        {
            m_sbMenuFP.setTextureRect(sf::IntRect(6*20,10*20,2.5*20,2.5*20));
        }
    }
    else if(bouton==B_FINPR)
    {
        if(type==1)
        {
            m_sbRejouerFP.setTextureRect(sf::IntRect(1*20,14*20,2.5*20,2.5*20));
        }
        else
        {
            m_sbRejouerFP.setTextureRect(sf::IntRect(6*20,14*20,2.5*20,2.5*20));
        }
    }
    else
    {

    }
}

void Menu::afficheMenuP()
{
    m_fenetre->draw(m_sbInfo);
    m_fenetre->draw(m_sbSon);
    m_fenetre->draw(m_sbJoueur1);
}

void Menu::afficheMenuSelectP()
{
    m_fenetre->draw(m_sTypeJeu);
    m_fenetre->draw(m_sbMenu);
    m_fenetre->draw(m_sbType1);
    m_fenetre->draw(m_sbType2);
    m_fenetre->draw(m_sbType3);
    m_fenetre->draw(m_sbType4);
    m_fenetre->draw(m_sbNiveau1);
    m_fenetre->draw(m_sbNiveau2);
    m_fenetre->draw(m_sbNiveau3);

}

void Menu::afficheMenuI()
{
    m_fenetre->draw(m_sMenuI);
    m_fenetre->draw(m_sbOk);
}

void Menu::afficheMenuPause()
{
    m_fenetre->draw(m_sMenuPause);
    m_fenetre->draw(m_sbResume);
    m_fenetre->draw(m_sbRejouer);
    m_fenetre->draw(m_sbInstructions);
    m_fenetre->draw(m_sbQuitter);
}
void Menu::afficheMenuFinPart()
{
    m_fenetre->draw(m_sMenuFinP);
    m_fenetre->draw(m_sbMenuFP);
    m_fenetre->draw(m_sbRejouerFP);
}

void Menu::afficheMenu()
{
    if(m_typeMenu==MenuPrincipal)
    {
        afficheMenuP();
    }
    else if(m_typeMenu==MenuInstructions)
    {
        afficheMenuI();
    }
    else if(m_typeMenu==MenuSelectTypeJ)
    {
        afficheMenuSelectP();
    }
    else if(m_typeMenu==MenuPause)
    {
        afficheMenuPause();
    }
    else if(m_typeMenu==MenuFinPartie)
    {
        afficheMenuFinPart();
    }
    else
    {

    }
}

Menu::~Menu()
{

}
