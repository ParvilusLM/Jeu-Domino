#include "menu.h"

using namespace std;

Menu::Menu(sf::RenderWindow& fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;

    //textures pour les boutons
    m_tSelectMP.loadFromFile("donnees/bMenuP.png");
    m_tSelectInstr.loadFromFile("donnees/bInstructions.png");
    m_tSelectTypeJ.loadFromFile("donnees/bSelectTypeJ.png");
    m_tSelectMPause.loadFromFile("donnees/bMenuPause.png");
    m_tSelectMGO.loadFromFile("donnees/bFinPartie.png");

    //sprites pour les boutons
    m_sbInfo.setTexture(m_tSelectMP);
    m_sbInfo.setPosition(1.f*20.f,1.f*20.f);
    gestTexture(B_INFO,1);

    m_sbSon.setTexture(m_tSelectMP);
    m_sbSon.setPosition(39.f*20.f,1*20.f);
    gestTexture(B_SON,1);

    m_sbJoueur1.setTexture(m_tSelectMP);
    m_sbJoueur1.setPosition(14.5f*20.f,27.5f*20.f);
    gestTexture(B_JOUEUR1,1);

    m_sbJoueur2.setTexture(m_tSelectMP);
    m_sbJoueur2.setPosition(14.5f*20.f,31.5f*20.f);
    gestTexture(B_JOUEUR2,1);


    m_sbMenu.setTexture(m_tSelectTypeJ);
    m_sbMenu.setPosition(1.f*20.f,1.f*20.f);
    gestTexture(B_MENU,1);

    m_sbGrille1.setTexture(m_tSelectTypeJ);
    m_sbGrille1.setPosition(2.f*20.f,16.f*20.f);
    gestTexture(B_GRILLE1,1);

    m_sbGrille2.setTexture(m_tSelectTypeJ);
    m_sbGrille2.setPosition(16.5f*20.f,16.f*20.f);
    gestTexture(B_GRILLE2,1);

    m_sbGrille3.setTexture(m_tSelectTypeJ);
    m_sbGrille3.setPosition(31.f*20.f,16.f*20.f);
    gestTexture(B_GRILLE3,1);

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
    m_tMenuP.loadFromFile("donnees/menuP.png");
    m_tMenuI.loadFromFile("donnees/instructions.png");
    m_tMenuPause.loadFromFile("donnees/MenuPause.png");
    m_tMenuFinP.loadFromFile("donnees/FinPartie.png");
    m_tTypeJeu.loadFromFile("donnees/selectTypeJ.png");


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
    m_sMenuP.setTexture(m_tMenuP);
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
        else if(collisionTS(m_sbJoueur2.getGlobalBounds()))
        {
            m_elementActif=JOUEUR2_ACTIF;
            gestTexture(B_JOUEUR2,2);
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
            gestTexture(B_JOUEUR2,1);
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
        else if(collisionTS(m_sbGrille1.getGlobalBounds()))
        {
            m_elementActif=GRILLE1_ACTIF;
            gestTexture(B_GRILLE1,2);
        }
        else if(collisionTS(m_sbGrille2.getGlobalBounds()))
        {
            m_elementActif=GRILLE2_ACTIF;
            gestTexture(B_GRILLE2,2);
        }
        else if(collisionTS(m_sbGrille3.getGlobalBounds()))
        {
            m_elementActif=GRILLE3_ACTIF;
            gestTexture(B_GRILLE3,2);
        }
        else
        {
            m_elementActif=AUCUN_EL_ACT;
            gestTexture(B_MENU,1);
            gestTexture(B_GRILLE1,1);
            gestTexture(B_GRILLE2,1);
            gestTexture(B_GRILLE3,1);
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
        else if(m_elementActif==JOUEUR2_ACTIF)
        {
            m_boutonPress=B_JOUEUR2;
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
        else if(m_elementActif==GRILLE1_ACTIF)
        {
            m_boutonPress=B_GRILLE1;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==GRILLE2_ACTIF)
        {
            m_boutonPress=B_GRILLE2;
            jeuEnCours=true;
            boutonPresse=true;
        }
        else if(m_elementActif==GRILLE3_ACTIF)
        {
            m_boutonPress=B_GRILLE3;
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
            m_sbInfo.setTextureRect(sf::IntRect(0,18*20,5*20,5*20));
        }
        else
        {
            m_sbInfo.setTextureRect(sf::IntRect(0,24*20,5*20,5*20));
        }
    }
    else if(bouton==B_SON)
    {
        if(type==1)
        {
            m_sbSon.setTextureRect(sf::IntRect(6*20,18*20,5*20,5*20));
        }
        else
        {
            m_sbSon.setTextureRect(sf::IntRect(6*20,24*20,5*20,5*20));
        }
    }
    else if(bouton==B_JOUEUR1)
    {
        if(type==1)
        {
            m_sbJoueur1.setTextureRect(sf::IntRect(0,0,16*20,3*20));
        }
        else
        {
            m_sbJoueur1.setTextureRect(sf::IntRect(0,8*20,16*20,3*20));
        }
    }
    else if(bouton==B_JOUEUR2)
    {
        if(type==1)
        {
            m_sbJoueur2.setTextureRect(sf::IntRect(0,4*20,16*20,3*20));
        }
        else
        {
            m_sbJoueur2.setTextureRect(sf::IntRect(0,12*20,16*20,3*20));
        }
    }
    else if(bouton==B_OK)
    {
        if(type==1)
        {
            m_sbOk.setTextureRect(sf::IntRect(1*20,1*20,4*20,4*20));
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
            m_sbMenu.setTextureRect(sf::IntRect(1*20,1*20,4*20,4*20));
        }
        else
        {
            m_sbMenu.setTextureRect(sf::IntRect(1*20,6*20,4*20,4*20));
        }
    }
    else if(bouton==B_GRILLE1)
    {
        if(type==1)
        {
            m_sbGrille1.setTextureRect(sf::IntRect(20*20,2*20,12*20,16*20));
        }
        else
        {
            m_sbGrille1.setTextureRect(sf::IntRect(2*20,16*20,12*20,16*20));
        }
    }
    else if(bouton==B_GRILLE2)
    {
        if(type==1)
        {
            m_sbGrille2.setTextureRect(sf::IntRect(20*20,2*20,12*20,12*20));
        }
        else
        {
            m_sbGrille2.setTextureRect(sf::IntRect(16.5f*20,16*20,12*20,16*20));
        }
    }
    else if(bouton==B_GRILLE3)
    {
        if(type==1)
        {
            m_sbGrille3.setTextureRect(sf::IntRect(20*20,2*20,12*20,12*20));
        }
        else
        {
            m_sbGrille3.setTextureRect(sf::IntRect(31*20,16*20,12*20,16*20));
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
    m_fenetre->draw(m_sMenuP);
    m_fenetre->draw(m_sbInfo);
    m_fenetre->draw(m_sbSon);
    m_fenetre->draw(m_sbJoueur1);
    m_fenetre->draw(m_sbJoueur2);
}

void Menu::afficheMenuSelectP()
{
    m_fenetre->draw(m_sTypeJeu);
    m_fenetre->draw(m_sbMenu);
    m_fenetre->draw(m_sbGrille1);
    m_fenetre->draw(m_sbGrille2);
    m_fenetre->draw(m_sbGrille3);

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
