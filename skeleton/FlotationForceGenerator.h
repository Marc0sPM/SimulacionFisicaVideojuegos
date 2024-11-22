#include "ForceGenerator.h"
#include "GameObject.h"

class FlotationForceGenerator : public ForceGenerator {
public:
    /**
     * @param liquidLevel Altura del nivel del líquido.
     * @param objectSize Tamaño del objeto sumergido (Vector3: ancho, alto, profundo).
     * @param liquidDensity Densidad del líquido.
     */
    FlotationForceGenerator(float liquidLevel, Vector3 objectSize, float liquidDensity);

    ~FlotationForceGenerator();

    Vector3 calculateForce(Particle* p) override;

    void update(double t) override {}


private:
    float _liquidLevel;     // Altura del nivel del líquido.
    float _objectHeight;    // Altura del objeto sumergido.
    float _objectVolume;    // Volumen del objeto sumergido.
    float _liquidDensity;   // Densidad del líquido.
    const float _gravity = 9.8f; // Gravedad
    
    GameObject* surface = nullptr;
};