#include <stdio.h>

/*------MY_ROLE------*/
#define GENERAL 0
#define LIEUTENANT 1

/*------BE_TRAITOR------*/
#define TRAITOR 1
#define NO_TRAITOR 0 

/*------MY_COLOR------*/
#define OFF RGB(0,0,0)
#define BLUE RGB(0,0,3)
#define YELLOW RGB(2,2,0)
#define ORANGE RGB(2,1,0)
#define GREEN RGB(0,3,0)
#define RED RGB(3,0,0)
#define WHITE RGB(3,3,3)

/*------MY_STATE------*/
#define TERMINATED 2
#define MOVING 1
#define STOPPED 0

/*------MESSAGE TO BE TRANSMITTED, LAST MESSAGE TRANSMITTED and GENERAL MESSAGE------*/
#define ATTACK 1
#define NOATTACK 0
#define NOTHING 9

#define MAX_DISTANCE 255
#define DANGER 60

#define TRUE 1
#define FALSE 0

uint8_t traitorNumber;//variable that stores the traitor's id
uint8_t generalNumber; //variable that stores the general's id
uint8_t numero; //auxiliary for any function
uint8_t numberNextMoving; //id of the kilobot that will move after the currently moving kilobot
uint8_t terminatedKilobots; //variable that increases as the kilobots finish transmitting the messages

typedef enum
{
	STOP,
	FORWARD,
	LEFT,
	RIGHT
}motion_t;

typedef enum{
    RECTO_PHASE,
    GIRO_PHASE,
    STOP_PHASE,
} game_state_t;

typedef struct 
{
	uint8_t my_color;
	uint8_t matrix_analyzed[4];
	uint8_t matrix_general[4];
	uint8_t my_role;
	uint8_t my_state;
	uint8_t be_traitor;
	uint8_t distanced[4];
	uint8_t messagesSent;
	uint8_t generalMessage;
	uint8_t lieutenantMessage;
	uint8_t decision;
	uint8_t idSender;
	uint8_t collided_with;
    uint8_t giro;
	uint8_t clock;
    game_state_t game_state;
	message_t outgoing_message;

}USERDATA;

