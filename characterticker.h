#ifndef CHARACTERTICKER_H
#define CHARACTERTICKER_H
#include "idleobserver.h"
#include "physics.h"
#include <QElapsedTimer>
#include "light.h"
#include "camera.h"
#include "map.h"

//Klasse um unsere beiden Charaktere zu steuern
class CharacterTicker : public IdleObserver
{
public:
    CharacterTicker(Map* map, DynamicCharacterWithCam* characterWithCam);
    void doIt();

private:
    Camera* m_characterCamera;
    DynamicCharacterWithCam* m_characterWithCam;
    //Timer für genaue Delta Zeitberechnung
    QElapsedTimer m_timer;
    QElapsedTimer m_landTimer;
    long long m_lastJumpTime;
    float m_rotationVector[2];
    float m_oldRotationVector[2];
    float m_mouseSensitivity;
    bool m_isInInventory;
    bool m_landed;
    int m_count;
    ICameraAccess* m_characterPhysicsCam;
    Map* m_map;
};

#endif // CHARACTERTICKER_H
