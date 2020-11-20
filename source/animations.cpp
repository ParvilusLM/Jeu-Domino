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
    m_delai=0.001f;


}

void Animations::gestionAnimation()
{
    if(m_animDistrib)
    {
        bool finAnim=false;
        sf::Vector2f posReferenceJ1,posReferenceJ2;
        posReferenceJ1.x=13*20;
        posReferenceJ1.y=33*20;

        posReferenceJ2.x=15*20;
        posReferenceJ2.y=2*20;

        int elementsEnPlace=0;

        int compt=0;
        while(compt<2)
        {
            int compt2=0;
            while(compt2<7)
            {
                bool xFinal=false,yFinal=false;
                if(compt==0)
                {
                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x != posReferenceJ1.x +(compt2*70) )
                    {
                        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x > posReferenceJ1.x +(compt2*70))
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(-1.f,0);
                        }
                        else
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(1.f,0);
                        }

                    }
                    else
                    {
                        xFinal=true;
                    }


                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().y != posReferenceJ1.y)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(0.f,1.f);
                    }
                    else
                    {
                        yFinal=true;
                    }

                    if(xFinal && yFinal)
                    {
                        elementsEnPlace++;
                    }

                }
                else
                {
                    bool xFinal=false,yFinal=false;

                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x != posReferenceJ2.x +(compt2*50) )
                    {
                        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x > posReferenceJ2.x +(compt2*50))
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(-1.f,0);
                        }
                        else
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(1.f,0);
                        }

                    }
                    else
                    {
                        xFinal=true;
                    }

                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().y != posReferenceJ2.y)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(0.f,-1.f);
                    }
                    else
                    {
                        yFinal=true;
                    }

                    if(xFinal && yFinal)
                    {
                        elementsEnPlace++;
                    }

                }
                compt2++;
            }
            compt++;
        }

        if(elementsEnPlace==14)
        {
            m_animDistrib=false;
            m_pDecor->getJoueur().retourneDominos(HUMAIN,true);
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
