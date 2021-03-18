#include "map.h"

Map::Map(Node* root, PhysicEngine* physicEngine)
{
    QString path(SRCDIR);

    m_root = root;
    m_physicEngine = physicEngine;

    Material* m;
    geloest = false;
    PointLight* pL1 = creatLight(45.0, QVector3D(73.0, 30.0, 73.0), 0);
    PointLight* pL2 = creatLight(135.0, QVector3D(73.0, 30.0, -73.0), 0);
    PointLight* pL3 = creatLight(225.0, QVector3D(-73.0, 30.0, -73.0), 0);
    PointLight* pL4 = creatLight(325.0, QVector3D(-73.0, 30.0, 73.0), 0);

    PointLight* pLOutside = new PointLight(0.00001, 0.00001);
    pLOutside->getTransformation().translate(600.0, 300.0, 0.0);
    pLOutside->setDiffuse(1.0f, 1.0f, 0.5f);
    pLOutside->setSpecular(1.0f, 1.0f, 0.5f);
    pLOutside->setAmbient(1.0f, 1.0f, 0.5f);
    pLOutside->turnOn();
    m_root->addChild(new Node(pLOutside));


    //Dungeon
    Drawable* dungeon = new Drawable(new TriangleMesh(path+ QString("/modelstextures/dungeon.obj")));
    dungeon->getProperty<Texture>()->loadPicture(path + QString("/modelstextures/TextureVariation_02.png"));
    m = dungeon->getProperty<Material>();
    m->setDiffuse(0.3f, 0.3f, 0.3f, 0.3f);
    m->setAmbient(0.3f, 0.3f, 0.3f, 0.3f);
    m->setSpecular(0.3f, 0.3f, 0.3f, 0.3f);
    m->setShininess(3.0f);
    dungeon->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/texturePhongFragment.vert"), QString("://shaders/texturePhongFragment.frag")));
    dungeon->getProperty<ModelTransformation>()->translate(0.0, 0.0, 0.0);
    dungeon->getProperty<ModelTransformation>()->scale(5.0f, 5.0f, 5.0f);
    m_root->addChild(new Node(dungeon));

    // Planes
    Drawable* Plane0 = createPlane(QVector3D(0.0f, -140.0f, 0.0f), 3000.0f);
    Drawable* Plane1 = createPlane(QVector3D(0.0f, 0.0f, 0.0f), 90.0f);
    Drawable* Plane2 = createPlane(QVector3D(60.0f, 0.0f, 0.0f), 30.0f);
    Drawable* Plane3 = createPlane(QVector3D(0.0f, 0.0f, 60.0f), 30.0f);
    Drawable* Plane4 = createPlane(QVector3D(-60.0f, 0.0f, 0.0f), 30.0f);
    Drawable* Plane5 = createPlane(QVector3D(0.0f, 0.0f, -60.0f), 30.0f);
    Drawable* Plane6 = createPlane(QVector3D(132.5f, -0.1f, 0.0f), 110.0f);

    // Statues
    m_statueOrientation[0] = 3;
    m_statueOrientation[1] = 3;
    m_statueOrientation[2] = 3;
    m_statueOrientation[3] = 3;

    float f = 28.0;
    m_statuePos[0] = QVector3D(f, 0.0, f);
    m_statuePos[1] = QVector3D(-f, 0.0, f);
    m_statuePos[2] = QVector3D(-f, 0.0, -f);
    m_statuePos[3] = QVector3D(f, 0.0, -f);

    m_distanceToInteract = 20.0f;

    m_statueArray[0] = createStatue(QString("/modelstextures/statue1.obj"), QString("://shaders/rotation1.vert"), m_statuePos[0]);
    m_statueArray[1] = createStatue(QString("/modelstextures/statue2.obj"), QString("://shaders/rotation2.vert"), m_statuePos[1]);
    m_statueArray[2] = createStatue(QString("/modelstextures/statue3.obj"), QString("://shaders/rotation3.vert"), m_statuePos[2]);
    m_statueArray[3] = createStatue(QString("/modelstextures/statue4.obj"), QString("://shaders/rotation4.vert"), m_statuePos[3]);

    for(int i = 0; i<4; i++){
        float f = 5.0f;
        m_statueArray[i]->getProperty<ModelTransformation>()->scale(f, f, f);
    }

    // Gate
    Drawable* gate = new Drawable(new TriangleMesh(path + QString("/modelstextures/IronGate.obj")));
    Texture* tGate;
    tGate = gate->getProperty<Texture>();
    tGate->loadPicture(path + QString("/modelstextures/TextureVariation_02.png"));
    gate->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/gate.vert"), QString("://shaders/texturePhongFragment.frag")));
    gate->getProperty<ModelTransformation>()->scale(2.0, 2.0, 2.0);
    gate->getProperty<ModelTransformation>()->translate(40.5, 0.0, 0.0);
    gate->getProperty<ModelTransformation>()->rotate(90.f, QVector3D(0.f, 1.f, 0.f));
    m_root->addChild(new Node(gate));

    //Pedestal
    Drawable* pedestal = new Drawable(new TriangleMesh(path + QString("/modelstextures/pedestal.obj")));
    m = pedestal->getProperty<Material>();
    m->setDiffuse(0.3f, 0.3f, 0.3f, 0.3f);
    m->setAmbient(0.3f, 0.3f, 0.3f, 0.3f);
    m->setSpecular(0.3f, 0.3f, 0.3f, 0.3f);
    m->setShininess(4.f);
    pedestal->getProperty<Texture>()->loadPicture(path + QString("/modelstextures/TextureVariation_02.png"));
    pedestal->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/texturePhongFragment.vert"), QString("://shaders/texturePhongFragment.frag")));
    pedestal->getProperty<ModelTransformation>()->translate(0.0, 0.0, 0.0);
    pedestal->getProperty<ModelTransformation>()->scale(5.0f, 5.0f, 5.0f);
    pedestal->setStaticGeometry(true);
    PhysicObject* pedestalPhys = m_physicEngine->createNewPhysicObject(pedestal);
    PhysicObjectConstructionInfo* pedestalConstrinf = new PhysicObjectConstructionInfo();
    pedestalConstrinf->setCollisionHull(CollisionHull::BoxAABB);
    pedestalPhys->setConstructionInfo(pedestalConstrinf);
    pedestalPhys->registerPhysicObject();
    m_root->addChild(new Node(pedestal));

    //Crystal
    crystal = new Drawable(new TriangleMesh(path + QString("/modelstextures/crystal.obj")));
    crystal->getProperty<ModelTransformation>()->translate(0.0, 15.0, 0.0);
    crystal->getProperty<ModelTransformation>()->scale(2.0, 2.0, 2.0);
    m = crystal->getProperty<Material>();
    m->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    m->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
    m->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m->setShininess(4.f);
    crystal->getProperty<Texture>()->loadPicture(path + QString("/modelstextures/TextureVariation_02.png"));
    crystal->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/crystalRot.vert"), QString("://shaders/texturePhongFragment.frag")));
    m_root->addChild(new Node(crystal));
}

PointLight* Map::creatLight(float rot, QVector3D pos, int farbCode, float s1, float s2)
{
    QString path(SRCDIR);

    //Pointlight
    PointLight* pointLight1 = new PointLight(s1, s2);
    pointLight1->getTransformation().translate(pos.x(), pos.y(), pos.z());

    switch(farbCode){
        case 1:
            pointLight1->setDiffuse(0.984f, 0.628f, 0.093f);
            pointLight1->setSpecular(0.984f, 0.628f, 0.093f);
            pointLight1->setAmbient(0.984f, 0.628f, 0.093f);
        break;

        default:
            pointLight1->setDiffuse(1.0f, 1.0f, 1.0f);
            pointLight1->setSpecular(1.0f, 1.0f, 1.0f);
            pointLight1->setAmbient(1.0f, 1.0f, 1.0f);
        break;
    }
    pointLight1->turnOn();
    m_root->addChild(new Node(pointLight1));

    //Fire
    Drawable* fire = new Drawable(new TriangleMesh(path + QString("/modelstextures/fire.obj")));
    fire->getProperty<ModelTransformation>()->translate(pos.x(), pos.y(), pos.z());
    fire->getProperty<ModelTransformation>()->scale(2.0, 2.0, 2.0);
    fire->getProperty<ModelTransformation>()->rotate(rot, 0.0, 1.0, 0.0);
    Material* m = fire->getProperty<Material>();
    m->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    m->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
    m->setSpecular(0.1f, 0.1f, 0.1f, 0.1f);
    m->setShininess(1.f);
    fire->getProperty<Texture>()->loadPicture(path + QString("/modelstextures/TextureVariation_02.png"));
    fire->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/texturePhongFragment.vert"), QString("://shaders/texturePhongFragment.frag")));
    m_root->addChild(new Node(fire));

    return pointLight1;
}



Drawable* Map::createPlane(QVector3D pos, float scale)
{
    // Plane
    Drawable* Plane = new Drawable(new SimplePlane(scale));
    Plane->getProperty<ModelTransformation>()->translate(pos.x(), pos.y(), pos.z());
    Plane->getProperty<ModelTransformation>()->rotate(90, 1.f, 0.f, 0.f);
    Material* m;
    m = Plane->getProperty<Material>();
    m->setDiffuse(0.3f, 0.3f, 0.3f, 0.3f);
    m->setAmbient(0.3f, 0.3f, 0.3f, 0.3f);
    m->setSpecular(0.3f, 0.3f, 0.3f, 0.3f);
    m->setShininess(3.0f);
    Plane->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/PhongFragment.vert"), QString("://shaders/PhongFragment.frag")));
    Plane->setStaticGeometry(true); // Der Oberfläche ein statisches Verhalten zuweisen
    PhysicObject* PlanePhys = m_physicEngine->createNewPhysicObject(Plane);
    PhysicObjectConstructionInfo* Constrinf = new PhysicObjectConstructionInfo();
    Constrinf->setCollisionHull(CollisionHull::BoxAABB); // Automatische Generierung einer Box
    PlanePhys->setConstructionInfo(Constrinf);
    PlanePhys->registerPhysicObject();
    m_root->addChild(new Node(Plane));
    return Plane;
}

Drawable* Map::createStatue(QString triangleMesh, QString rotationShader, QVector3D pos)
{
    QString path(SRCDIR);
    Drawable *statue = new Drawable(new TriangleMesh(path+triangleMesh));
    statue->getProperty<Texture>()->loadPicture(path + QString("/modelstextures/TextureVariation_02.png"));
    statue->setShader(ShaderManager::getShader<MyShader>(rotationShader, QString("://shaders/texturePhongFragment.frag")));
    statue->getProperty<ModelTransformation>()->translate(pos.x(), pos.y(), pos.z());
    Material* m;
    m = statue->getProperty<Material>();
    m->setDiffuse(0.3f, 0.3f, 0.3f, 0.3f);
    m->setAmbient(0.3f, 0.3f, 0.3f, 0.3f);
    m->setSpecular(0.3f, 0.3f, 0.3f, 0.3f);
    m->setShininess(3.f);

    statue->setStaticGeometry(true);
    PhysicObject* statue1Phys = m_physicEngine->createNewPhysicObject(statue);
    PhysicObjectConstructionInfo* statue1Constrinf = new PhysicObjectConstructionInfo();
    statue1Constrinf->setCollisionHull(CollisionHull::BoxAABB);
    statue1Phys->setConstructionInfo(statue1Constrinf);
    statue1Phys->registerPhysicObject();
    m_root->addChild(new Node(statue));
    return statue;
}

void Map::interactQ(QVector3D playerPos)
{
    QString path(SRCDIR);

    QVector3D statueDistance0 = m_statuePos[0] - playerPos;
    if(statueDistance0.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation1.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(0);
    m_statueOrientation[0] = 0;
    }

    QVector3D statueDistance1 = m_statuePos[1] - playerPos;
    if(statueDistance1.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation2.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(0);
    m_statueOrientation[1] = 0;
    }

    QVector3D statueDistance2 = m_statuePos[2] - playerPos;
    if(statueDistance2.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation3.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(0);
    m_statueOrientation[2] = 0;
    }

    QVector3D statueDistance3 = m_statuePos[3] - playerPos;
    if(statueDistance3.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation4.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(0);
    m_statueOrientation[3] = 0;
    }
}

void Map::interactE(QVector3D playerPos)
{
    QString path(SRCDIR);

    QVector3D statueDistance0 = m_statuePos[0] - playerPos;
    if(statueDistance0.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation1.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(1);
    m_statueOrientation[0] = 1;
    }

    QVector3D statueDistance1 = m_statuePos[1] - playerPos;
    if(statueDistance1.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation2.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(1);
    m_statueOrientation[1] = 1;
    }

    QVector3D statueDistance2 = m_statuePos[2] - playerPos;
    if(statueDistance2.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation3.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(1);
    m_statueOrientation[2] = 1;
    }

    QVector3D statueDistance3 = m_statuePos[3] - playerPos;
    if(statueDistance3.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation4.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(1);
    m_statueOrientation[3] = 1;
    }
}

void Map::interactR(QVector3D playerPos)
{
    QString path(SRCDIR);

    QVector3D statueDistance0 = m_statuePos[0] - playerPos;
    if(statueDistance0.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation1.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(2);
    m_statueOrientation[0] = 2;
    }

    QVector3D statueDistance1 = m_statuePos[1] - playerPos;
    if(statueDistance1.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation2.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(2);
    m_statueOrientation[1] = 2;
    }

    QVector3D statueDistance2 = m_statuePos[2] - playerPos;
    if(statueDistance2.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation3.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(2);
    m_statueOrientation[2] = 2;
    }

    QVector3D statueDistance3 = m_statuePos[3] - playerPos;
    if(statueDistance3.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation4.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(2);
    m_statueOrientation[3] = 2;
    }
}

void Map::interactF(QVector3D playerPos)
{
    QString path(SRCDIR);

    QVector3D statueDistance0 = m_statuePos[0] - playerPos;
    if(statueDistance0.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation1.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(3);
    m_statueOrientation[0] = 3;
    }

    QVector3D statueDistance1 = m_statuePos[1] - playerPos;
    if(statueDistance1.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation2.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(3);
    m_statueOrientation[1] = 3;
    }

    QVector3D statueDistance2 = m_statuePos[2] - playerPos;
    if(statueDistance2.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation3.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(3);
    m_statueOrientation[2] = 3;
    }

    QVector3D statueDistance3 = m_statuePos[3] - playerPos;
    if(statueDistance3.length() <= m_distanceToInteract)
    {
    MyShader* rotShader = ShaderManager::getShader<MyShader>(QString("://shaders/rotation4.vert"), QString("://shaders/texturePhongFragment.frag"));
    rotShader->rotate(3);
    m_statueOrientation[3] = 3;
    }
}

void Map::doIt()
{
    QString path(SRCDIR);
    if(m_statueOrientation[0] == 2 && m_statueOrientation[1] == 1 && m_statueOrientation[2] == 0 && m_statueOrientation[3] == 3 && !geloest)
    {
        MyShader* translateShader = ShaderManager::getShader<MyShader>(QString("://shaders/gate.vert"), QString("://shaders/texturePhongFragment.frag"));
        translateShader->translate(0);
        crystal->getProperty<Texture>()->loadPicture(path + QString("/modelstextures/TextureVariation_03.png"));
        crystal->setShader(ShaderManager::getShader<MyShader>(QString("://shaders/crystalRot.vert"), QString("://shaders/texturePhongFragment.frag")));
        geloest = true;
    }
}
