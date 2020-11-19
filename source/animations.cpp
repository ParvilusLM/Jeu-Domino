#include "animations.h"

Animations::Animations(Decor& decor):m_pDecor(0)
{
    m_pDecor=&decor;
    m_animDistrib=false;
    m_animJoueur1C=false;
    m_animJoueur1V=false;
    m_animJoueur2V=false;
    m_animJoueur2V=false;
    m_animPiocheC=false;
    m_animPiocheV=false;

    m_timer=0.f;
    m_delai=0.1f;


}

void Animations::gestionAnimation()
{
    if(m_animDistrib)
    {
        int compt=0;
        while(compt<2)
        {
            int compt2=0;
            while(compt2<7)
            {
                if(compt==0)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(2.f,2.f);
                }
                else
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(2.f,-2.f);
                }
                compt2++;
            }
            compt++;
        }
    }

    if(m_animJoueur1C)
    {

    }

    if(m_animJoueur1V)
    {

    }

    if(m_animJoueur2C)
    {

    }

    if(m_animJoueur2V)
    {

    }

    if(m_animPiocheC)
    {

    }

    if(m_animPiocheV)
    {

    }
}

void Animations::debuterAnim(int typeAnim)
{
    if(typeAnim==ANIM_DISTRIBUTION)
    {
        m_animDistrib=true;
    }
    else if(typeAnim==ANIM_JOUEUR1_C)
    {
        m_animJoueur1C=true;
    }
    else if(typeAnim==ANIM_JOUEUR1_V)
    {
        m_animJoueur1V=true;
    }
    else if(typeAnim==ANIM_JOUEUR2_C)
    {
        m_animJoueur2C=true;
    }
    else if(typeAnim==ANIM_JOUEUR2_V)
    {
        m_animJoueur2V=true;
    }
    else if(typeAnim==ANIM_PIOCHE_C)
    {
        m_animPiocheC=true;
    }
    else if(typeAnim==ANIM_PIOCHE_V)
    {
        m_animPiocheV=true;
    }
    else
    {

    }
}

void Animations::gestMaJ()
{
    float tempsEcoule =m_horlorge.getElapsedTime().asSeconds();
    m_horlorge.restart();
    m_timer+=tempsEcoule;

    if(m_animDistrib || m_animJoueur1C || m_animJoueur1V || m_animJoueur2C || m_animJoueur2V || m_animPiocheC || m_animPiocheV)
    {
        if(m_timer>=m_delai)
        {
            gestionAnimation();
            m_timer=0.f;
        }
    }
}

Animations::~Animations()
{

}
