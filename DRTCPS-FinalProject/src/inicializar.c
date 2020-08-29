#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

extern USERDATA * mydata;

void inicializarRole(){
	/*We check the randomly generated number for the general.
	The generated number will be the general's id number.*/
	if (kilo_uid==generalNumber)
	{
		mydata->my_role=GENERAL;
		mydata->my_color=ORANGE;
		mydata->my_state=MOVING; //the general is the first to move
		set_color(ORANGE); // general will be orange
		printf("> Id=%d: I am the general !\n", kilo_uid);
	
	}else{
		mydata->my_role=LIEUTENANT;
		mydata->my_color=RED;
		mydata->my_state=STOPPED;
		set_color(RED); // The lieutenants will be red
		printf("> Id=%d: I am a lieutenant!\n", kilo_uid);
	}
}
void inicializarNumeroSiguienteMoviendose(){
	numberNextMoving=9;
	mydata->giro=0;
	mydata->game_state=RECTO_PHASE;
	terminatedKilobots=0;
}
void inicializarMensajes(){
	for (int i = 0; i < 4; i++)
	{
		mydata->distanced[i]=MAX_DISTANCE;
	}
	kilo_message_tx= message_sender;
	kilo_message_rx= message_receiver;
	mydata->messagesSent=0;
	mydata->generalMessage=NOTHING;
	mydata->lieutenantMessage=NOTHING;
	mydata->decision=NOTHING;
	setup_message(&mydata->outgoing_message, NOTHING);
}
void inicializarTraidor(){
	/*We check the random generated number. If the number is greater than or equal to 4, there is no traitor.
	Otherwise the generated number will be the number of the traitor's id*/
	if(traitorNumber >= 4){
		printf("------THERE WON'T BE TRAITOR------\n");
		mydata->be_traitor= NO_TRAITOR;

	}else{
		if (kilo_uid == traitorNumber)
		{
			mydata->be_traitor=TRAITOR;
			mydata->my_color=BLUE;
			set_color(BLUE);// the traitor will be blue
		}
	} 
}
void inicializarMatrices(){
	for (int i = 0; i < 4; i++)
	{
		mydata->matrix_analyzed[i]=NOTHING;
	}
}

void inicializarMatrizGeneral(){
	uint8_t j=0;
	uint8_t numero2;
	uint8_t numero3;
	if (mydata->my_role==GENERAL && mydata->be_traitor==TRAITOR)
	{
		numero=getRandomNumber(0,1);
		numero2=getRandomNumber(0,1);
		
		if (numero==numero2)
		{
			if (numero==0)
			{
				numero3=1;
			}else{
				numero3=0;
			}
		}else{
			numero3=getRandomNumber(0,1);
		}

		uint8_t matriz[3];

		matriz[0]=numero;
		matriz[1]=numero2;
		matriz[2]=numero3;

		for (int i = 0; i < 4; i++)
		{
			if (i==kilo_uid)
			{
				mydata->matrix_general[i]=NOTHING;
			}else{
				mydata->matrix_general[i]=matriz[j];
				j++;
			}
		}
	}
	if (mydata->my_role==GENERAL && mydata->be_traitor==NO_TRAITOR)
	{
		numero=getRandomNumber(0,1);
		for (int i = 0; i < 4; i++)
		{
			if (i==kilo_uid)
			{
				mydata->matrix_general[i]=NOTHING;
			}else{
				mydata->matrix_general[i]=numero;
			}
		}
	}
}

uint8_t getRandomNumber(uint8_t from,uint8_t to){
	// Create a random number 
  	uint8_t variable= from + rand() % (to+1-from);
  	return variable;
}

