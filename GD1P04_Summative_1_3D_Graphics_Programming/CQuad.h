#pragma once
#include "CShape.h"
class CQuad :
    public CShape
{
public:
    CQuad();
    ~CQuad();

    void Update();
    void Render();
private:

};

