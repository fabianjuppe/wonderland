#include "characterticker.h"
#include "scenemanager.h"
#include "qdatetime.h"
#include "qaction.h"
#include "qcursor.h"
#include "physicaccessablecamera.h"
#include "openglwidget.h"
#include "inputregistry.h"
CharacterTicker::CharacterTicker(Map* map, DynamicCharacterWithCam* characterWithCam)
{
    OpenGLWidget::getInstance()->setCursor(QCursor(Qt::BlankCursor));
    m_landed = true;
    m_count = 0;
    m_lastJumpTime = 0.0;
    m_mouseSensitivity = 0.04f;
    m_rotationVector[0] = 0.0;
    m_rotationVector[1] = 0.0;
    m_oldRotationVector[0] = 0.0;
    m_oldRotationVector[1] = 0.0;

    m_characterCamera = SceneManager::instance()->getActiveContext()->getCamera();
    m_characterPhysicsCam = dynamic_cast<PhysicAccessableCamera*>(m_characterCamera);

    SceneManager::instance()->getActiveContext()->setCamera(m_characterCamera);
    m_characterCamera->setAperture(50);
    m_characterCamera->setFarPlane(20000.0f);

    m_characterWithCam = characterWithCam;
    m_map = map;

    m_characterWithCam->setAccelarationFactor(20.f/1000.f);
    m_characterWithCam->setBrakeFactor(1000.f);
    m_characterWithCam->setJumpMoveFactor(0.04f/1000.f);
    m_characterWithCam->setJumpSpeed(250.f);

    m_characterWithCam->setMaxBackwardNormalSpeed(20.f);
    m_characterWithCam->setMaxBackwardSlowSpeed(0.5f);
    m_characterWithCam->setMaxBackwardSprintSpeed(2.f);

    m_characterWithCam->setMaxForwardNormalSpeed(40.f);
    m_characterWithCam->setMaxForwardSlowSpeed(1.f);
    m_characterWithCam->setMaxForwardSprintSpeed(4.f);

    m_characterWithCam->setMaxStraveNormalSpeed(20.f);
    m_characterWithCam->setMaxStraveSlowSpeed(0.5f);
    m_characterWithCam->setMaxStraveSprintSpeed(2.f);

    m_characterWithCam->setMaxTurnNormalSpeed(1.0f);

    m_timer.restart();
}

void CharacterTicker::doIt()
{
    QString path(SRCDIR);
    KeyboardInput* keyIn = InputRegistry::getInstance().getKeyboardInput();
    QVector3D cameraOffset(0.0, 5.f, 0.0);

        m_rotationVector[0] += (QCursor::pos().y() - (OpenGLWidget::getInstance()->height() / 2)) * m_mouseSensitivity;
        m_rotationVector[1] += (QCursor::pos().x() - (OpenGLWidget::getInstance()->width() / 2)) * m_mouseSensitivity;

        QCursor::setPos(OpenGLWidget::getInstance()->width() / 2, OpenGLWidget::getInstance()->height() / 2);

        m_characterCamera->setPosition(m_characterWithCam->getPosition3DVector() + cameraOffset);
        if(m_rotationVector[0] < 80 && m_rotationVector[0] > -75)
        {
            m_characterPhysicsCam->setXAngleTripod(m_rotationVector[0]);
            m_characterPhysicsCam->setYAngleTripod(m_rotationVector[1]);
            m_oldRotationVector[0] = m_rotationVector[0];
            m_oldRotationVector[1] = m_rotationVector[1];
        }
        else
        {
            m_rotationVector[0]= m_oldRotationVector[0];
            m_characterPhysicsCam->setXAngleTripod(m_rotationVector[0]);
            m_characterPhysicsCam->setYAngleTripod(m_rotationVector[1]);
        }


        long long time = m_timer.restart();

        unsigned long long moveFlagsDynCh = 0;

        m_characterWithCam->setYRotation(-m_rotationVector[1]);

        if(keyIn->isKeyPressed('w'))
        {
            moveFlagsDynCh |= MovementFlag::Forward;
        }
        if(keyIn->isKeyPressed('a'))
        {
            moveFlagsDynCh |= MovementFlag::StraveLeft;
        }
        if(keyIn->isKeyPressed('s'))
        {
            moveFlagsDynCh |= MovementFlag::Backward;
        }
        if(keyIn->isKeyPressed('d'))
        {
            moveFlagsDynCh |= MovementFlag::StraveRight;
        }


        if(keyIn->isKeyPressed('q'))
        {
            m_map->interactQ(m_characterWithCam->getPosition3DVector());
        }
        if(keyIn->isKeyPressed('e'))
        {
            m_map->interactE(m_characterWithCam->getPosition3DVector());
        }
        if(keyIn->isKeyPressed('r'))
        {
            m_map->interactR(m_characterWithCam->getPosition3DVector());
        }
        if(keyIn->isKeyPressed('f'))
        {
            m_map->interactF(m_characterWithCam->getPosition3DVector());
        }

        m_characterWithCam->moveCharacter(time, moveFlagsDynCh);
}
