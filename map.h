#ifndef MAP_H
#define MAP_H

#include "node.h"
#include "shader.h"
#include "physicengine.h"
#include "drawable.h"
#include "simpleplane.h"
#include "modeltransformation.h"
#include "trianglemesh.h"
#include "texture.h"
#include "shadermanager.h"
#include "myshader.h"
#include "sunlight.h"
#include "material.h"
#include "simplesphere.h"
#include "simplecube.h"
#include "pointlight.h"

class Map : public IdleObserver
{
public:
    Map(Node* root, PhysicEngine* physicEngine);
    void interactQ(QVector3D playerPos);
    void interactE(QVector3D playerPos);
    void interactR(QVector3D playerPos);
    void interactF(QVector3D playerPos);
    void doIt();
    ~Map();

private:
    Node* m_root;
    Shader* m_shader;
    PhysicEngine* m_physicEngine;
    int m_statueOrientation[4];
    QVector3D m_statuePos[4];
    Drawable* m_statueArray[4];
    float m_distanceToInteract;
    QString m_statueTexture;
    QElapsedTimer m_rotationTimer;
    PointLight* creatLight(float rot, QVector3D pos, int farbCode = 0, float s1 = 0.0001f, float s2 = 0.0001f);
    Drawable* createStatue(QString triangleMesh, QString rotationShader, QVector3D pos);
    Drawable* createPlane(QVector3D pos, float scale);
    Drawable* crystal;
    bool geloest;

};

#endif // MAP_H
