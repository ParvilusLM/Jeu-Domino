#include "controleur.h"

Controleur::Controleur(sf::RenderWindow& fenetre):m_decor(0)
{
    m_fenetre=&fenetre;

    m_decor=new Decor(*m_fenetre);
}

void Controleur::debutJeu()
{

}

void Controleur::gestionDplSouris()
{
    m_decor->getMenu().elementActif();
}

void Controleur::gestionSelecSouris()
{
    m_decor->getMenu().selectionElActif();
}

void Controleur::gestionMaJ()
{
    //gestions boutons presses pour les menus
    if(boutonPresse)
    {
        //pour le son quand on clic sur un bouton
        if(m_decor->getMenu().getBoutonPress()!= AUCUN_EL_ACT)
        {
            m_decor->getSon().jouerSon(SON_BCLIK);
        }

        if(m_decor->getMenu().getBoutonPress()==B_INFO)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_SON)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_JOUEUR1)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_OK)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_PREC)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_SUIV)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_MENU)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_TYPE1)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_TYPE2)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_TYPE3)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_TYPE4)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_NIVEAU1)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_NIVEAU2)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_NIVEAU3)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_JOUER)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_PAUSER)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_PAUSEREJ)
        {
            debutJeu();
        }
        else if(m_decor->getMenu().getBoutonPress()==B_PAUSEI)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_PAUSEQ)
        {

        }
        else if(m_decor->getMenu().getBoutonPress()==B_FINPQ)
        {
            jeuPause=false;
            jeuEnCours=false;
            jeuDebut=false;
            jeuFinPartie=false;
            m_decor->getMenu().setTypeMenu(MenuPrincipal);
        }
        else if(m_decor->getMenu().getBoutonPress()==B_FINPR)
        {
            debutJeu();
        }
        else
        {

        }

        m_decor->getMenu().resetBoutonPress();
        boutonPresse=false;
    }

}

void Controleur::afficheMenu()
{
    m_decor->getMenu().afficheMenu();
}

void Controleur::afficheFondEc()
{
    m_decor->afficheFondEc();
}

void Controleur::afficheJeu()
{

}

void Controleur::afficheInfo()
{

}

Controleur::~Controleur()
{
    delete m_decor;
}

