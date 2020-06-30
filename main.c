#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "simulator.h"
#include "example.h"


int main( int argc, char * argv[] )
{
    sim_t *sim;

    // create the simulator
    if ((sim = simulator_init()) != NULL) {

        printf("Initialised simulator!\n");

        // run the example code
        example_run(&(sim->m_gui));

        // destroy the simulator
        simulator_deinit();

        return 0;
    } else {

        printf("Could not initialise!\n");

        return 1;

    }
}
