/*
 * MIT License, see root folder for full license.
 */
#ifndef UI_H
#define UI_H

#include "os.h"
#include "cx.h"
#include <stdbool.h>
#include "os_io_seproxyhal.h"
#include "bagl.h"

/** length of the APDU (application protocol data unit) header. */
#define APDU_HEADER_LENGTH 5

/** offset in the APDU header which says the length of the body. */
#define APDU_BODY_LENGTH_OFFSET 4

/** for signing, indicates this is the last part of the transaction. */
#define P1_LAST 0x80

/** for signing, indicates this is not the last part of the transaction, there are more parts coming. */
#define P1_MORE 0x00

/**
 * Nano S has 320 KB flash, 10 KB RAM, uses a ST31H320 chip.
 * This effectively limits the max size
 * So we can only display 10 screens of data, and can only sign transactions up to 1kb in size.
 * max size of a transaction, binary will not compile if we try to allow transactions over 1kb.
 */
#define MAX_TX_RAW_LENGTH 1024

/** max width of a single line of text. */
#define MAX_TX_TEXT_WIDTH 18

/** max lines of text to display. */
#define MAX_TX_TEXT_LINES 3

/** max number of screens to display. */
#define MAX_TX_TEXT_SCREENS 10

/** max number of hex bytes that can be displayed (2 hex characters for 1 byte of data) */
#define MAX_HEX_BUFFER_LEN (MAX_TX_TEXT_WIDTH / 2)

/** max number of bytes for one line of text. */
#define CURR_TX_DESC_LEN (MAX_TX_TEXT_LINES * MAX_TX_TEXT_WIDTH)

/** max number of bytes for all text screens. */
#define MAX_TX_DESC_LEN (MAX_TX_TEXT_SCREENS * CURR_TX_DESC_LEN)

/** UI currently displayed */
enum UI_STATE {
	UI_IDLE, UI_TOP_SIGN, UI_TX_DESC, UI_SIGN, UI_DENY
};

/** UI state enum */
extern enum UI_STATE uiState;

/** UI state flag */
extern ux_state_t ux;

/** private key in flash. const and N_ variable name are mandatory here */
extern const cx_ecfp_private_key_t N_privateKey;

/** initialization marker in flash. const and N_ variable name are mandatory here */
extern const unsigned char N_initialized;

/** notification to restart the hash */
extern unsigned char hashTainted;

/** the hash. */
extern cx_sha256_t hash;

/** index of the current screen. */
extern unsigned int curr_scr_ix;

/** max index for all screens. */
extern unsigned int max_scr_ix;

/** raw transaction data. */
extern unsigned char raw_tx[MAX_TX_RAW_LENGTH];

/** current index into raw transaction. */
extern unsigned int raw_tx_ix;

/** current length of raw transaction. */
extern unsigned int raw_tx_len;

/** all text descriptions. */
extern char tx_desc[MAX_TX_TEXT_SCREENS][MAX_TX_TEXT_LINES][MAX_TX_TEXT_WIDTH];

/** currently displayed text description. */
extern char curr_tx_desc[MAX_TX_TEXT_LINES][MAX_TX_TEXT_WIDTH];

/** process a partial transaction */
const bagl_element_t * io_seproxyhal_touch_approve(const bagl_element_t *e);

/** show the idle UI */
void ui_idle(void);

/** show the "Sign TX" ui, starting at the top of the Tx display */
void ui_top_sign(void);

/** return the length of the communication buffer */
unsigned int get_apdu_buffer_length();

#endif // UI_H
