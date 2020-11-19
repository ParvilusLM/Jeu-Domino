#ifndef DEF_ANIMATIONS
#define DEF_ANIMATIONS

#include "decor.h"

class Animations
{
public:
    Animations(Decor& decor);
    void gestionAnimation();

    void debuterAnim(int typeAnim);
    void gestMaJ();

    ~Animations();


private:
    Decor* m_pDecor;
    bool m_animDistrib,m_animJoueur1C,m_animJoueur1V,m_animJoueur2C,m_animJoueur2V,m_animPiocheC,m_animPiocheV;
    sf::Clock m_horlorge;
    float m_timer;
    float m_delai;


};

#endif // DEF_ANIMATIONS
