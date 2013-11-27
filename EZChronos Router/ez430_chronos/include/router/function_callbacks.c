
#include "function_callbacks.h"

/**
 * The general callback function to send a message.
 */
void rx_function_callback_router(linkID_t ID){

	linkID_t rx_id = ID;
	u8* rx_packet;
	u8 rx_packet_len = 255;

	/* Radio must be in Rx state to get reply. Then back to
	 * IDLE to conserve power.
	 */
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
	NWK_REPLY_DELAY();
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);

	/* Get received reply */
	SMPL_Receive(rx_id, &rx_packet, &rx_packet_len);

	/* Set the rx packet struct */
	rx_buffer.rx_packet = &rx_packet;
	rx_buffer.id = rx_id;
	rx_buffer.rx_packet_len = rx_packet_len;


	/* radio off */
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
}

/**
 * The general callback function to receive a message.
 */
void tx_function_callback_router(linkID_t ID, void* packet, u8 size){

	/* wake up radio */
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);

	/* Send message */
	SMPL_Send(ID, &packet, size);

	/* Radio must be in Rx state to get reply. Then back to
	 * IDLE to conserve power.
	 */
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
	NWK_REPLY_DELAY();
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);

	return;
}
