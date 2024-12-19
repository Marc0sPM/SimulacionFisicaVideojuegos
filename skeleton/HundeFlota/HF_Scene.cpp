#include "HF_Scene.h"
#include "../RenderUtils.hpp"
#include "../Render/Render.h"
#include <iostream>



void HF_Scene::init()
{
	_camera->setDir(CAM_DIR);
	_camera->setEye(CAM_POS);

	_sysRB = new RBSystem(_physics, _scene);
    _psys = new ParticleSystem(); 

    auto frag = _psys->addFragmentsGenerator(
        { 0,0,0 },
        { 0,5,0 },
        5.f,
        BOAT_SIZE.y,
        10,
        2.f,
        spawn_position_distribution::NORMAL_SP,
        50.f
    );

    auto splash = _psys->addSplashGenerator(
        { 0,0,0 },
        { 0,15,0 },
        5.f,
        1.f,
        30,
        1.f,
        spawn_position_distribution::NORMAL_SP,
        50.f,
        4.f,
        WATER_COLOR
    );

    auto grav = _psys->addForce(new GravityGenerator(Vector3(0, -9.8, 0)));
    _psys->addLink(grav, frag);
    _psys->addLink(grav, splash);

	// Crear el sistema de flotación
	_water = new Water({ 0, 0, 0 }, WATER_SIZE, WATER_COLOR);
	_water->setGravity(_scene->getGravity());
	_sysRB->addForce(_water);


	_boatsys = new BoatSystem(this, _physics, _scene, _sysRB, _water);
    auto wind = new RWindGenerator(WIND_VEL, 0.25);
    _sysRB->addForce(wind);
    _boatsys->setWindDown(wind);
    _boatsys->init();

    drawText(POINTS_TEXT + to_string(_points), POINTS_POS.x, POINTS_POS.y);
}

void HF_Scene::update(double t)
{
    checkBallLimits();
    if (!_canShoot) {
        _shootTime -= t;
        if (_shootTime < 0) {
            _canShoot = true;
            _shootTime = TIME_TO_SHOOT;
        }
    }

    _psys->update(t);
	_sysRB->update(t);
	_boatsys->update(t);


    for (auto& ball : _balls_remove) {
        _balls.remove(ball);
        _sysRB->removeObject(ball);
        delete ball;
    }

    _balls_remove.clear();
}

void HF_Scene::cleanup()
{

    delete _sysRB;
    delete _boatsys; 
    _balls.clear();
    _balls_remove.clear();
    std::cout << "[-] HF_Scene\n";
}

void HF_Scene::onKeyPress(unsigned char key) {
	switch (key)
	{
	case 'x':

		break;
	default: 
		break;
	}
}

void HF_Scene::onMouseMove(int x, int y) {
	_mouseX = x;
	_mouseY = y;
}

void HF_Scene::onMouseClick(int button, int state, int x, int y) {
	_mouseX = x;
	_mouseY = y;

	if (button == 0 && state == 1) { // Botón izquierdo presionado
		
		Vector3 dir = getDirectionWithCursor();
		std::cout << "Direccion proy: (" << dir.x << ", " << dir.y << ", " << dir.z << ")\n";
		
        if (_canShoot) {
            shootBall();
            _canShoot = false;
        }
	}
}

void HF_Scene::onCollision(PxRigidActor* actor1, PxRigidActor* actor2)
{
    auto boats = _boatsys->getBoats();
    for (auto boat : *boats) {
        
        if (boat->getRB() == actor1 || boat->getRB() == actor2) {
            _boatsys->removeBoat(boat);
            _points += POINTS_BOAT;
            updatePoints();
            break;
        }
    }
    for (auto ball : _balls) {
        
        if (ball->getRB() == actor1 || ball->getRB() == actor2) {
           
            if (std::find(_balls_remove.begin(), _balls_remove.end(), ball) == _balls_remove.end()) {
                _balls_remove.push_back(ball);
            }

            break;
        }
    }


}

void HF_Scene::spawnFrags(Boat* b)
{
    _psys->getFrag()->activateFragments(b->getRB()->getGlobalPose().p + Vector3(0, 1, 0), b->getColor());
}

Vector3 HF_Scene::getDirectionWithCursor() {
    // Centro de la pantalla (en este caso 350, 350 para una ventana de 700x700)
    float centerX = WINDOW_WIDTH / 2;
    float centerY = WINDOW_HEIGHT / 2;

    // Obtén la posición del cursor
    float dx = _mouseX - centerX;  // X positivo si el cursor está a la derecha, negativo si está a la izquierda
    float dy = centerY - _mouseY;  // Y positivo si el cursor está por encima, negativo si está por debajo

    // Calcula la distancia del cursor al centro de la pantalla
    float distance = std::sqrt(dx * dx + dy * dy);

    // Normaliza la distancia para obtener el ángulo máximo de 45 grados
    float maxDistance = std::fmin(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.0f;  // La distancia máxima al centro
    float rotationAmount = std::fmin(distance / maxDistance, 1.0f) * 25.0f;  // Ángulo máximo de 45 grados

    // Convierte el ángulo a radianes
    float angleInRadians = physx::PxPi * rotationAmount / 180.0f;

    // Obtén la dirección de la cámara
    physx::PxVec3 cameraDir = _camera->getDir();

    // Inicializamos el vector de dirección rotado igual al de la cámara
    physx::PxVec3 rotatedDir = cameraDir;

    // Calculamos la rotación sobre el eje X (basada en dx)
    float horizontalRotationAmount = std::fmin(std::abs(dx) / maxDistance, 1.0f) * 45.0f;  // Limite a 45 grados
    if (dx > 0) {  // Si está a la derecha del centro
        rotatedDir.x = std::sin(physx::PxPi * horizontalRotationAmount / 180.0f);
    }
    else {  // Si está a la izquierda del centro
        rotatedDir.x = -std::sin(physx::PxPi * horizontalRotationAmount / 180.0f);
    }

    // Calculamos la rotación sobre el eje Y (basada en dy)
    float verticalRotationAmount = std::fmin(std::abs(dy) / maxDistance, 1.0f) * 45.0f;  // Limite a 45 grados
    if (dy > 0) {  // Si está por encima del centro
        rotatedDir.y = std::sin(physx::PxPi * verticalRotationAmount / 180.0f);
    }
    else {  // Si está por debajo del centro
        rotatedDir.y = -std::sin(physx::PxPi * verticalRotationAmount / 180.0f);
    }

    // Normalizamos el vector para que sea unitario
    rotatedDir.normalize();

    // Mantener el valor de z de la dirección de la cámara
    rotatedDir.z = -1.f;

    return rotatedDir;
}

void HF_Scene::updatePoints()
{
    _text = POINTS_TEXT + to_string(_points);
}

void HF_Scene::shootBall()
{
    Ball* ball;
    ball = new Ball(_physics, _scene, _camera->getEye(), BALL_RADIUS, GenerateRandomColor(), BALL_MASS);
    _sysRB->addDynamic(ball);
    ball->addForce(getDirectionWithCursor() * SHOOT_FORCE, PxForceMode::eIMPULSE);
        // _ball->setLifeTime(BALL_LIFETIME);
    _balls.push_back(ball);
}

void HF_Scene::checkBallLimits()
{
    for (auto& b : _balls) {
        Vector3 p = b->getRB()->getGlobalPose().p;
        //Salpica si esta en la superficie del agua
        if (p.y <= _water->getLiquidPos().y + _water->getLiquidSize().y * 2 / 3 && 
            p.y >= _water->getLiquidPos().y + _water->getLiquidSize().y * 2 / 3 - 3.f) {

            if (isBallInWater(p)) {
                _psys->getSplash()->spawnSplash(p - Vector3(0,b->getRatius(),0));
            }
        }
        //Se elimina al llegar al fondo del liquido
        if (p.y < _water->getLiquidPos().y - _water->getLiquidSize().y / 2) {
            _balls_remove.push_back(b);
        }
    }
}
bool HF_Scene::isBallInWater(Vector3 ballPos) {
    // Calculamos los límites de la superficie del agua en X y Z
    auto waterPos = _water->getLiquidPos();
    auto waterSize = _water->getLiquidSize();
    float minX = waterPos.x - waterSize.x / 2.0f;
    float maxX = waterPos.x + waterSize.x / 2.0f;
    float minZ = waterPos.z - waterSize.z / 2.0f;
    float maxZ = waterPos.z + waterSize.z / 2.0f;

    // Comprobamos si la posición de la bola está dentro de los límites X y Z
    return (ballPos.x >= minX && ballPos.x <= maxX &&
        ballPos.z >= minZ && ballPos.z <= maxZ);
}


