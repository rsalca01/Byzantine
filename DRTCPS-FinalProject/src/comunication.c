#include <kilombo.h>
#include "includes/main.h"
#include "includes/inicializar.h"
#include "includes/movement.h"
#include "includes/comunication.h"
#include "includes/time.h"
#include "includes/game.h"
#include "includes/colors.h"

extern USERDATA * mydata;

//This function is used to decide wich message will be sent next
void decideMessage(){
	if (mydata->my_role==GENERAL)
	{
		uint8_t message= mydata->matrix_general[mydata->collided_with];
		printf("> My id is %d and the message I send to id %d is %d\n",kilo_uid, mydata->collided_with, message );
		setup_message(&mydata->outgoing_message, message);
	}else{
		if (mydata->be_traitor==TRAITOR)
		{
			if (mydata->generalMessage==ATTACK)
			{
				printf("> My id is %d and the message I send to id %d is %d\n",kilo_uid, mydata->collided_with, NOATTACK );
				setup_message(&mydata->outgoing_message, NOATTACK);
			}else{
				printf("> My id is %d and the message I send to id %d is %d\n",kilo_uid, mydata->collided_with, ATTACK );
				setup_message(&mydata->outgoing_message, ATTACK);
			}
		}else{
			if (mydata->generalMessage==ATTACK)
			{
				printf("> My id is %d and the message I send to id %d is %d\n",kilo_uid, mydata->collided_with,  ATTACK);
				setup_message(&mydata->outgoing_message, ATTACK);
			}else{
				printf("> My id is %d and the message I send to id %d is %d\n",kilo_uid, mydata->collided_with, NOATTACK );
				setup_message(&mydata->outgoing_message, NOATTACK);
			}
		}
	}
}

//Returns false when no kilobot has been found and true when a kilobot is found
uint8_t collisionDetected(){
	uint8_t ret = FALSE;
	for(int i=0; i<4; i++){
		if(mydata->distanced[i] <= DANGER){
		    mydata->collided_with = mydata->idSender;
		    decideMessage();
			ret = TRUE;
		}
	}
	return ret;
}

//Every time a kilobot receives a message it saves the content of that message in the matrix to analyze of that kilobot
void saveToMatrix(){
	uint8_t id=mydata->idSender;
	uint8_t payload=mydata->generalMessage;
	uint8_t payload2=mydata->lieutenantMessage;
	if (id==generalNumber)
	{
		if (mydata->matrix_analyzed[id]!=payload)
		{
			mydata->matrix_analyzed[id]=payload;
		}
	}else{
		if (mydata->matrix_analyzed[id]!=payload2)
		{
			mydata->matrix_analyzed[id]=payload2;
		}
	}
}

//Callback to send messages
message_t * message_sender(){
	return &mydata->outgoing_message;
}

//Callback to receive messages
void message_receiver(message_t *m, distance_measurement_t *d){
	uint8_t snd=SenderID(*m); //get sender id
	mydata->distanced[snd]=estimate_distance(d); //estimate the distance with the closest kilobot
	uint8_t payload=MessagePayload(*m);

	if (snd==generalNumber && mydata->my_state==STOPPED)
	{
		mydata->generalMessage=payload;
	}
	if (snd!=generalNumber && mydata->my_state==STOPPED)
	{
		mydata->lieutenantMessage=payload;
	}
	mydata->idSender=snd; //upload the id of the last sender from who the kilobopt receive the message
	saveToMatrix();
}

//Get sender ID
uint8_t SenderID(message_t m){
    uint8_t snd_id = m.data[0];// Raw message
    snd_id >>= 4;// Clear the payload data
    return snd_id;
}

// Get the message payload
uint8_t MessagePayload(message_t m){
    uint8_t payload = m.data[0];// Raw message
    payload <<= 4;// Clear the ID data
    payload >>= 4;// Make the message readable again
    return payload;
}

// Generate a message
void setup_message(message_t * msg, uint8_t payload){
    msg->type = NORMAL;// Message type
    uint8_t sender = kilo_uid << 4;// Add ID on the most significant 4 bits (on the left)
    msg->data[0] = sender + payload;// Payload
    msg->crc = message_crc(msg);// Checksum
}


