#include "ForceGenerator.h"

class FlotationForceGenerator : public ForceGenerator {
public:
    /**
     * @param liquidLevel Altura del nivel del l�quido.
     * @param objectSize Tama�o del objeto sumergido (Vector3: ancho, alto, profundo).
     * @param liquidDensity Densidad del l�quido.
     */
    FlotationForceGenerator(float liquidLevel, Vector3 objectSize, float liquidDensity);

    ~FlotationForceGenerator();

    Vector3 calculateForce(Particle* p) override;

    /**
     * Actualiza la posici�n del nivel del l�quido (opcional para din�micas).
     * @param newLevel Nueva altura del nivel del l�quido.
     */
    void updateLiquidLevel(float newLevel);

    void update(double t) override {}

private:
    float _liquidLevel;     // Altura del nivel del l�quido.
    float _objectHeight;    // Altura del objeto sumergido.
    float _objectVolume;    // Volumen del objeto sumergido.
    float _liquidDensity;   // Densidad del l�quido.
    const float _gravity = 9.8f; // Gravedad
};