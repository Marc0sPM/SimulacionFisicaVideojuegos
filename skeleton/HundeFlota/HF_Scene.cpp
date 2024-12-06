#include "HF_Scene.h"
#include "../RenderUtils.hpp"
#include <iostream>



void HF_Scene::init()
{
	_camera->setDir(CAM_DIR);
	_camera->setEye(CAM_POS);

	_sys = new RBSystem(_physics, _scene);

	// Crear el sistema de flotación
	_water = new Water({ 0, 0, 0 }, { 50, 5, 50 }, { 0.0f, 0.0f, 1.0f, 1.0f });
	_water->setGravity(_scene->getGravity());
	_sys->addForce(_water);


	_boatsys = new BoatSystem(_physics, _scene, _sys, _water);

	_boatsys->generateBoat();
	_boatsys->generateBoat();
	_boatsys->generateBoat();
	_boatsys->generateBoat();
}

void HF_Scene::update(double t)
{
	_sys->update(t);
	_boatsys->update(t);
}

void HF_Scene::cleanup()
{
}

void HF_Scene::onKeyPress(unsigned char key) {
	switch (key)
	{
	case 'x':
		//crearProyectil
		break;
	default: 
		break;
	}
}

void HF_Scene::onMouseMove(int x, int y) {
	_mouseX = x;
	_mouseY = y;
	std::cout << "Posición del cursor: (" << x << ", " << y << ")\n";
}

void HF_Scene::onMouseClick(int button, int state, int x, int y) {
	_mouseX = x;
	_mouseY = y;

	if (button == 0 && state == 1) { // Botón izquierdo presionado
		std::cout << "Clic izquierdo en posición: (" << _mouseX << ", " << _mouseY << ")\n";
		// Aquí puedes disparar un proyectil o realizar otra acción
		std::cout << "Centro de la pantalla: (" << WINDOW_WIDTH / 2 << ", " << WINDOW_HEIGHT / 2 << ")\n";

		Vector3 dir = getDirectionWithCursor();
		std::cout << "Direccion proy: (" << dir.x << ", " << dir.y << ", " << dir.z << ")\n";
		

        shootBall();
	}
}

void HF_Scene::onCollision(PxRigidActor* actor1, PxRigidActor* actor2)
{
    auto boats = _boatsys->getBoats();
    for (auto boat : *boats) {
        // Compara los actores de la colisión con el rigid body de las bolas
        if (boat->getRB() == actor1 || boat->getRB() == actor2) {
            std::cout << "Colisión detectada con una bola!" << std::endl;

            // Ejemplo de lógica: cambia el color de la bola al colisionar
            boat->changeColor(Vector4(1, 0, 0, 1));  // Cambiar a rojo

            // Si necesitas eliminar la bola, asegúrate de manejar correctamente el iterador
            //_balls.remove(ball);  // Esto solo es válido si no estás iterando con `for(auto it = ...)`

            break;
        }
    }
    for (auto ball : _balls) {
        // Compara los actores de la colisión con el rigid body de las bolas
        if (ball->getRB() == actor1 || ball->getRB() == actor2) {
            std::cout << "Colisión detectada con una bola!" << std::endl;

            // Ejemplo de lógica: cambia el color de la bola al colisionar
            ball->changeColor(Vector4(1, 0, 0, 1));  // Cambiar a rojo

            // Si necesitas eliminar la bola, asegúrate de manejar correctamente el iterador
            //_balls.remove(ball);  // Esto solo es válido si no estás iterando con `for(auto it = ...)`

            break;
        }
    }


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

void HF_Scene::shootBall()
{
    Ball* ball;
    ball = new Ball(_physics, _scene, _camera->getEye(), BALL_RADIUS, GenerateRandomColor(), BALL_MASS); 
    ball->addForce(getDirectionWithCursor() * SHOOT_FORCE);
        // _ball->setLifeTime(BALL_LIFETIME);
    _balls.push_back(ball);
}


