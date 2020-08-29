#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

extern USERDATA * mydata;

void setMotion(motion_t new_motion){
	switch(new_motion){
		case STOP:
			set_motors(0,0);
		break;
		case FORWARD:
			set_motors(kilo_straight_left, kilo_straight_right);
		break;
		case LEFT:
			set_motors(kilo_straight_left, 0);
		break;
		case RIGHT:
			set_motors(0, kilo_straight_right);
		break;
	}
}

void rectoPhase(uint8_t option){
	switch(option){
		case 1:
			if (collisionDetected())
			{
				upDateClock();
				saveToMatrix();
				mydata->game_state=STOP_PHASE;
			}else{
				setMotion(FORWARD);
			}
		break;
		case 2:
			
			if (waitTime(130))
			{
				mydata->giro=0;
			}else{
				setMotion(FORWARD);
			}
		break;
		case 3:
			if (waitTime(230))
			{
				setMotion(STOP);
				mydata->my_state=STOPPED;
			}else{
				setMotion(FORWARD);
			}
		break;
	}
}
void giroPhase(){
	set_color(mydata->my_color);
	if(waitTime(72)){
			mydata->giro=1;
			mydata->game_state=RECTO_PHASE;
			
	}else{
		setMotion(LEFT);
	}
}
void funcionStop(){
	if(waitTime(20))
	{

		mydata->game_state=GIRO_PHASE;
		mydata->messagesSent=mydata->messagesSent+1;
		if (mydata->messagesSent==3)
		{
			terminatedKilobots=terminatedKilobots+1;
		}
	}else{
		setMotion(STOP);
		cambioColorSegunMensaje();
	}
}

//Check if the moving kilobot has already sent all its messages so that another kilobot starts moving
void calculateNextOne(){
	if (terminatedKilobots<=3)
	{
		if (mydata->messagesSent==3)
		{
			mydata->messagesSent=0;
			checkIdOfNextKilobot(kilo_uid);
			mydata->my_state=TERMINATED;//If it has sent all its messages it has finished
		}
	}else{
		if (mydata->messagesSent==3)
		{
			mydata->messagesSent=0;
			mydata->my_state=TERMINATED;//If it has sent all its messages it has finished
		}
		numberNextMoving=9;
	}
}

//Calculate the id of the next kilobot to move
void checkIdOfNextKilobot(uint8_t id){
		if (id==3)
		{
			numberNextMoving=0;	
		}else{
			numberNextMoving=kilo_uid+1;
		}
}

//Change the state of the next kilobot so that it starts moving
void nextKilobot(){
	if (terminatedKilobots<=3)//If all the kilobots have been in motion, no kilobot will change their state again to move
	{
		if (kilo_uid==numberNextMoving)
		{
			mydata->my_state=MOVING;
			numberNextMoving=9; 
		}
	}
}

//This function check wheter all the kilobots have sent their messages, if so it analysis the final matrix of the kilobots and ends the game
void checkTerminatedKilobots(){
	if (terminatedKilobots==4)
	{
		analyzedFinalMatrix();
		movimientoFinal();
	}
}

//This function is used to analyzed the matrix in wich the kilobots have been introducing the receive messages
void analyzedFinalMatrix(){
	uint8_t attack=0;
	uint8_t noattack=0;
	for (int i = 0; i < 4; i++)
	{
		if(mydata->matrix_analyzed[i]==ATTACK){
			attack=attack+1;
		}else if (mydata->matrix_analyzed[i]==NOATTACK)
		{
			noattack=noattack+1;
		}
	}
	if (attack < noattack)
	{
		mydata->decision=NOATTACK;
	}else{
		mydata->decision=ATTACK;
	}
}




