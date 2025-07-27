#ifndef PHYSICS_H
#define PHYSICS_H

// PARTICLE-SIM.c
#define NUM_PARTICLES 1

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float mass;
} Particle;

void printParticles(void);
void initParticles(void);
Vector2 ComputeForce(Particle *particle);
void RunSimulation(void);


// RIGID-BODY-SIM.c
#define NUM_RIGID_BODIES 1

typedef struct {
    float width;
    float height;
    float mass;
    float momentOfInertia;
} BoxShape;

typedef struct {
    Vector2 position;
    Vector2 linearVelocity;
    float angle;
    float angularVelocity;
    Vector2 force;
    float torque;
    BoxShape shape;
} RigidBody;

void CalculateBoxInertia(BoxShape *boxShape);
void PrintRigidBodies();
void InitializeRigidBodies();
void ComputeForceAndTorque(RigidBody *rigidBody);
void RunRigidBodySimulation();



#endif // PHYSICS_H
