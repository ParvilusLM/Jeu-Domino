#include "controleur.h"

Controleur::Controleur(sf::RenderWindow& fenetre):m_decor(0),m_animations(0)
{
    m_fenetre=&fenetre;

    m_decor=new Decor(*m_fenetre);
    m_animations=new Animations(*m_decor);
}

void Controleur::debutJeu()
{
    laMain=true;
    laMainBot=false;
    //init plateauJeu de la classe Joueur
    m_decor->getJoueur().initPlateauJeu();
    m_decor->getJoueur().getPlateauJeu().typeJeu=m_decor->getMenu().getDonnees(0);
    m_decor->getJoueur().getPlateauJeu().niveauJeu=m_decor->getMenu().getDonnees(1);

    m_animations->debuterAnim(ANIM_DISTRIBUTION);
}

void Controleur::pauseJeu()
{
    jeuPause=true;
    m_decor->getMenu().setTypeMenu(MenuPause);
}

void Controleur::gestionDplSouris()
{
    m_decor->getMenu().elementActif();
}

void Controleur::gestionSelecSouris()
{
    m_decor->getMenu().selectionElActif();
}

void Controleur::gestBoutonsJeu()
{
    if(m_decor->getJoueur().boutonSelect())
    {
        pauseJeu();
    }
}

void Controleur::glisserDeposer(int action)
{
    if(action==GLISSER)
    {
        if(m_decor->getJoueur().selectionDomino(HUMAIN))
        {
            glisser=true;
        }
    }
    else
    {
        deposer=true;
    }
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
            if(m_decor->getMenu().getDonnees(0) != AUCUN_TJ  && m_decor->getMenu().getDonnees(1) != AUCUN_NIV)
            {
                jeuEnCours=true;
                jeuDebut=true;
            }

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

    if(jeuDebut)
    {
        debutJeu();
        jeuDebut=false;
    }

    m_decor->getJoueur().gestMaj();

    if(jeuEnCours)
    {
        m_animations->gestMaJ();
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
    m_decor->getJoueur().affichePartie();

    if(jeuPause)
    {
        m_decor->getMenu().afficheMenu();
    }
}

void Controleur::afficheInfo()
{

}

Controleur::~Controleur()
{
    delete m_decor;
    delete m_animations;
}

