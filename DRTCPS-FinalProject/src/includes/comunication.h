message_t * message_sender();
void message_receiver(message_t *m, distance_measurement_t *d);
uint8_t SenderID(message_t m);
uint8_t MessagePayload(message_t m);
void setup_message(message_t * msg, uint8_t payload);
uint8_t collisionDetected();
void saveToMatrix();
void decideMessage();


