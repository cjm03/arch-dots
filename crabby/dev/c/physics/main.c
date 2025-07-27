#include "physics.h"
#include <stdio.h>

int main(void)
{
    printf("Particle\n\n");
    RunSimulation();
    printf("\n\nRigidBody\n\n");
    RunRigidBodySimulation();
}
