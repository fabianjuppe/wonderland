#include "opengl.h"
#include "scene.h"
#include "modeltransformation.h"
#include "keyboardtransformation.h"
#include "color.h"
#include "simplecube.h"
#include "simpleplane.h"
#include "simplesphere.h"
#include "trianglemesh.h"
#include "texture.h"
#include "characterticker.h"
#include "mainwindow.h"
#include "scenemanager.h"
#include "screenrenderer.h"
#include "physicaccessablecamera.h"
#include "shadermanager.h"
#include "map.h"
#include "sunlight.h"
#include "shader.h"

Node* initScene1();

void SceneManager::initScenes()
{
    PhysicAccessableCamera* cam = new PhysicAccessableCamera;
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer);

    // Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
}

Node* initScene1()
{
    //Objekte anlegen
    QString path(SRCDIR);

    //Main root der Szene
    Node* root = new Node;

    // Physic Engine Erzeugen und einen Pointer auf Instanz holen
    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);


    // Player der gesteuert werden kann und den eine Kamera verfolgt
    Drawable* v_BallFollow = new Drawable(new SimpleSphere(0.3f));
    ModelTransformation* v_Transformation = v_BallFollow->getProperty<ModelTransformation>();
    // Player etwas anheben, da man sonst durch den Boden fallen würde
    v_Transformation->translate(-15.f, 1.f, 0.f);
    root->addChild(new Node(v_BallFollow));

    // Character Objekt erzeugen mit einer Verfolgerkamera
    DynamicCharacterWithCam* v_CharacterWithCam = v_PhysicEngine->createNewDynamicCharacterWithCam(v_BallFollow);

    // Physic Object registrieren
    v_BallFollow->getPhysicObject()->registerPhysicObject();

    Map* map = new Map(root, v_PhysicEngine);

    // Character Ticker der für die Steuerung unser Charaktere veranwortlich ist
    new CharacterTicker(map, v_CharacterWithCam);

    return root;
}
