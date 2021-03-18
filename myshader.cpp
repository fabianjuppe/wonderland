#include "myshader.h"

MyShader::MyShader()
{

}

void MyShader::setShaderUniforms()
{
    ShaderTimed::setShaderUniforms();
    this->shaderProgram()->setUniformValue("color", QVector3D(1.0, 0.0, 0.0));
    this->shaderProgram()->setUniformValue("axis", m_Axis);
    this->shaderProgram()->setUniformValue("rotate", m_Rotate);
    this->shaderProgram()->setUniformValue("translate", m_Translate);
}

void MyShader::setAxis(int axis)
{
    m_Axis = axis;
}

void MyShader::rotate(int rotate)
{
    m_Rotate = rotate;
}

void MyShader::translate(int translate)
{
    m_Translate = translate;
}
