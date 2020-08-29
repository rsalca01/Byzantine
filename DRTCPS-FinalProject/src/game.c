#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

extern USERDATA * mydata;

void gamePhase(game_state_t game_state){
	switch(game_state){
		case RECTO_PHASE:
            
			if (mydata->my_state==TERMINATED){
				rectoPhase(3);
			}else{
				if (mydata->giro==0 )
				{
					rectoPhase(1);
				}else{
					rectoPhase(2);
				}
			}
		break;
		case GIRO_PHASE:
			giroPhase();
		break;
		case STOP_PHASE:
			funcionStop();
		break;
	}
}

//This function is used to check in wich state of the game is each kilobot
void comprobarPhase(){
	if(mydata->my_state==MOVING || mydata->my_state==TERMINATED){
		if (mydata->game_state==GIRO_PHASE)
		{
			gamePhase(GIRO_PHASE);
		}
		if (mydata->game_state == RECTO_PHASE)
		{
			gamePhase(RECTO_PHASE);
		}
		if (mydata->game_state==STOP_PHASE)
		{
			gamePhase(STOP_PHASE);
		}
		
	}else{
		setMotion(STOP);
	}
}
