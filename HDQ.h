//.H CODE

#include "inttypes.h"

/** * Texas Instruments HDQ implementation for the Arduino API
* (cleft) Matthieu Lalonde 2008 (matth@mlalonde.net)
* Creative Commons BY-SA-NC

* * http://trac.mlalonde.net/cral/browser/HDQ/ * * Revision 1 *
**/

#ifndef HDQ_H
#define HDQ_H

//#define HDQ_DEBUG // Uncomment this to enable DEBUG

/**
 * Default pin to use if none is specified to the constructor
 **/
#define HDQ_DEFAULT_PIN 7       /* Arduino pin 7 */
#ifdef HDQ_DEBUG
#define HDQ_DEFAULT_DEBUG_PIN 6 /* Arduino pin 6 */
#endif

/**
 * Read/write command mask
 **/
#define HDQ_ADDR_MASK_READ 0x00
#define HDQ_ADDR_MASK_WRITE 0x80 /* B10000000 */

/**
 * This is the number of times the slave wait loop
 * will run before we time out.
 * As far as I can tell the loop uses ~6 instructions
 * thus giving about 200uS delay which is a full bit write
 **/
#define HDQ_DELAY_FAIL_TRIES 400

/**
 * HDQ Default NEW timings
 **/
#define HDQ_DELAY_THW1 41  // 32 - 66uS
#define HDQ_DELAY_THW0 112 // 70 - 145uS

#define HDQ_DELAY_TDW1 41   // 0.5 - 50us
#define HDQ_DELAY_TDW0 112  // 86 - 145uS
#define HDQ_DELAY_TCYCD 220 // 190 min

#define HDQ_DELAY_TB 220    /* Min: 190uS */
#define HDQ_DELAY_TBR 70    /* Min: 40uS */
#define HDQ_DELAY_TCYCH 220 /* Min: 190uS Max: 250uS*/

#define HDQ_DELAY_TRSPS_MAX 320 /* Max: 320uS */
#define HDQ_DELAY_BIT_TOTAL 200

class HDQ
{
public:
    /**
     * Constructor
     * @param pinArg: pin number to attach to
     **/
    // HDQ(uint8_t pinArg = HDQ_DEFAULT_PIN);
    HDQ(uint8_t pinArg);

    /**
     * sendBreak: writes a break to the HDQ line
     **/
    void doBreak(void);

    /**
     * write: send a payload to the device
     * @param reg: the address of the register to write to
     * @param payload: data to be sent
     * @return: false, unless if verif is set, then
     *          it will read back the register and
     *          return true if it matches the payload
     **/
    bool write(uint8_t reg, uint8_t payload, bool verif);
    bool write(uint8_t reg, uint8_t payload);

    /**
     * read: read from the device
     * @param register: address of the register to read
     * @return a uint8_t integer
     **/
    uint8_t read(uint8_t reg);

private:
    /**
     * Port variables definition
     **/
    uint8_t pin;
    uint8_t port;
    uint8_t bitmask;
    volatile uint8_t *outputReg;
    volatile uint8_t *inputReg;
    volatile uint8_t *modeReg;

#ifdef HDQ_DEBUG
    uint8_t debugPin;
    uint8_t debugPort;
    uint8_t debugBitmask;
    volatile uint8_t *debugOutputReg;
    volatile uint8_t *debugInputReg;
    volatile uint8_t *debugModeReg;
#endif

    /**
     * writeByte: write a raw byte of data to the bus
     * @param payload: the byte to send
     *
     **/
    void writeByte(uint8_t payload);
    // uint8_t _HDQ_readPin();
};
#endif
