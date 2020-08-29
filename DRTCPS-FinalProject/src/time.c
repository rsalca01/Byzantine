#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

extern USERDATA * mydata;

void inicializarTiempo(){
	mydata->clock=kilo_ticks;
}

void upDateClock(){
	mydata->clock=0;
}

// Wait for a given time. Return TRUE when done, FALSE otherwise
uint8_t waitTime(uint8_t kiloTicks){
	if(mydata->clock && mydata->clock <= kiloTicks){
		isElapsed();
		if(mydata->clock)
			return FALSE;
		return TRUE;
	}else{																
		setTimer(kiloTicks);
		return FALSE;
	}
}
uint8_t isElapsed(){
	if(mydata->clock){
		mydata->clock -= 1;
		return FALSE;
	}else{
		return TRUE;
	}
}

uint8_t setTimer(uint8_t value){
	mydata->clock = value;
	return value;
}
