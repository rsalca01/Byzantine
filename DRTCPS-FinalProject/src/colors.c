#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

extern USERDATA * mydata;

//This function changes the color of the kilobot depending on the message it sends 
void cambioColorSegunMensaje(){
	if (mydata->my_role==GENERAL)
	{
		ponerColor(mydata->matrix_general[mydata->collided_with]);
	}else{
		ponerColor(mydata->generalMessage);
	}
}

void ponerColor(uint8_t men){
	if (mydata->my_role==GENERAL)
	{
		if (men==ATTACK)
		{
			set_color(GREEN);
		}else{
			set_color(YELLOW);
		}
	}else{
		if (mydata->collided_with!=generalNumber)
		{
			if (mydata->be_traitor==TRAITOR)
			{
				if (men==ATTACK)
				{
					set_color(YELLOW);
				}else{
					set_color(GREEN);
				}
			}else{
				if (men==ATTACK)
				{
					set_color(GREEN);
				}else{
					set_color(YELLOW);
				}
			}
		}else{
			set_color(mydata->my_color);
		}
	}
}

//This function change the color of the kilobots depending on its final decision 
void movimientoFinal(){
	if (mydata->be_traitor!=TRAITOR)
	{
		if (mydata->decision==ATTACK)
		{
			printf("> My id is %d and my final decision is %d\n", kilo_uid, mydata->decision);
			set_color(WHITE);
		}else{
			printf("> My id is %d and my final decision is %d\n", kilo_uid, mydata->decision);
			set_color(OFF);
		}
	}else{
		printf("> My id is %d and I am the traitor so I am not going to take any decision.\n", kilo_uid);
		set_color(mydata->my_color); //the traitor doesn't change its color
	}
}