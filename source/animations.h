#ifndef DEF_ANIMATIONS
#define DEF_ANIMATIONS

#include "decor.h"

class Animations
{
public:
    Animations(Decor& decor);
    void gestionAnimation();
    void debuterAnim(int typeAnim);
    void miseEnArretAnim();
    void gestMaJ();

    ~Animations();


private:
    Decor* m_pDecor;
    bool m_animDistrib,m_animJoueur1C,m_animJoueur1V,m_animJoueur2C,m_animJoueur2V,m_animPiocheC,
    m_animPiocheV,m_animJoueur2Coup,m_animJoueur1P,m_animJoueur2P,m_animJoueur1P2,m_animJoueur2P2;
    sf::Clock m_horlorge;
    float m_timer;
    float m_delai;


};

#endif // DEF_ANIMATIONS
