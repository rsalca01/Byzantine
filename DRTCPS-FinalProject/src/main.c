#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

#include <stdlib.h>
#include <time.h>
#ifdef SIMULATOR
#include <stdio.h> // for printf
#else
#include <avr/io.h>  // for microcontroller register defs
//  #define DEBUG          // for printf to serial port
//  #include "debug.h"
#endif

REGISTER_USERDATA(USERDATA)

void loop(){
	comprobarPhase();
	calculateNextOne();
	nextKilobot();
	checkTerminatedKilobots();
}

void setup(){
	inicializarMensajes();
	inicializarRole();
	inicializarTiempo();
	inicializarTraidor();
	inicializarMatrizGeneral();
	inicializarMatrices();
	inicializarNumeroSiguienteMoviendose();
}

int main()
{
	srand(time(NULL));
	/*We generate the random numbers to know who is the general and who will be the traitor*/
	traitorNumber=getRandomNumber(0,7);
	generalNumber=getRandomNumber(0,3);
	printf("-----> %d Is the random number generated to know the id of the GENERAL\n",generalNumber );
	printf("-----> %d Is the random number generated for the TRAITOR\n",traitorNumber);
	kilo_init();
	kilo_start(setup, loop);
	return 0;
}
