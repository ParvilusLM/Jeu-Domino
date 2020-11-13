#include "son.h"

Son::Son()
{
    m_bufBClic.loadFromFile("donnees/select-granted.wav");
    m_bufAutorise.loadFromFile("donnees/correct.wav");
    m_bufInterdit.loadFromFile("donnees/error.wav");

    m_sonBClic.setBuffer(m_bufBClic);
    m_sonAutorise.setBuffer(m_bufAutorise);
    m_sonInterdit.setBuffer(m_bufInterdit);
}

void Son::jouerSon(int type)
{
    if(type==SON_BCLIK)
    {
        m_sonBClic.play();
    }
    else if(type==SON_AUTORISE)
    {
        m_sonAutorise.play();
    }
    else if(type==SON_INTERDIT)
    {
        m_sonInterdit.play();
    }
    else
    {

    }
}

Son::~Son()
{

}
