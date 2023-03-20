#ifndef ORCSPRITE_H
#define ORCSPRITE_H
#include "ReinerSprite.h"
class OrcSprite :
    public ReinerSprite
{
public:
    OrcSprite();
    void SetNewAction(int new_action);
};
#endif
