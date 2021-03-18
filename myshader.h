#ifndef MYSHADER_H
#define MYSHADER_H

#include "shadertimed.h"


class MyShader : public ShaderTimed
{
public:
    MyShader();
    virtual void setShaderUniforms() override;
    void setAxis(int axis);
    void rotate(int rotate);
    void translate(int translate);

private:
    int m_Axis;
    int m_Rotate;
    int m_Translate;
};

#endif // MYSHADER_H
