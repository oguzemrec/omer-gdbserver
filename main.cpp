#include <iostream>
#include <thread>
#include <chrono>

#define EUSART1_TX_BUFFER_SIZE (16) //buffer size should be 2^n
#define EUSART1_TX_BUFFER_MASK (EUSART1_TX_BUFFER_SIZE - 1)


#define EUSART1_RX_BUFFER_SIZE (16) //buffer size should be 2^n
#define EUSART1_RX_BUFFER_MASK (EUSART1_RX_BUFFER_SIZE - 1)

static volatile uint8_t eusart1TxHead = 0;
static volatile uint8_t eusart1TxTail = 0;
static volatile uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];
volatile uint8_t eusart1TxBufferRemaining;


static volatile uint8_t eusart1RxHead = 0;
static volatile uint8_t eusart1RxTail = 0;
static volatile uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
static volatile eusart1_status_t eusart1RxStatusBuffer[EUSART1_RX_BUFFER_SIZE];
volatile uint8_t eusart1RxCount;


volatile eusart1_status_t eusart1RxLastError;

void write_packet(uint8_t* txData, int packet_size)
{
    PO_DE = 0; //TX Enable

    uint8_t tempTxHead;
    
    for ( int i=1; i < packet_size; ++i ){
      eusart1TxBuffer[i-1] = txData + i;
       tempTxHead = (eusart1TxHead + 1) & EUSART1_TX_BUFFER_MASK;
       
       eusart1TxHead = tempTxHead;
       PIE1bits.TX1IE = 0; //Critical value decrement
       eusart1TxBufferRemaining--; // one less byte remaining in TX buffer
    }


/// Old Code
    if(0 == PIE1bits.TX1IE)
    {
        TXREG1 = txData;
    }
    else if(eusart1TxBufferRemaining) // check if at least one byte place is available in TX buffer
    {
       eusart1TxBuffer[eusart1TxHead] = txData;
       tempTxHead = (eusart1TxHead + 1) & EUSART1_TX_BUFFER_MASK;
       
       eusart1TxHead = tempTxHead;
       PIE1bits.TX1IE = 0; //Critical value decrement
       eusart1TxBufferRemaining--; // one less byte remaining in TX buffer
    }
    else
    {
        //overflow condition; eusart1TxBufferRemaining is 0 means TX buffer is full
    }
    PIE1bits.TX1IE = 1;
    
}

void EUSART1_TransmitISR(void)
{
    uint8_t tempTxTail;
    // use this default transmit interrupt handler code
    if(sizeof(eusart1TxBuffer) > eusart1TxBufferRemaining) // check if all data is transmitted
    {
       TXREG1 = eusart1TxBuffer[eusart1TxTail];
       tempTxTail = (eusart1TxTail + 1) & EUSART1_TX_BUFFER_MASK;
       
       eusart1TxTail = tempTxTail;
       eusart1TxBufferRemaining++; // one byte sent, so 1 more byte place is available in TX buffer
    }
    else
    {
        PIE1bits.TX1IE = 0;
        PO_DE = 1; //RX Enable
    }
    
}
int main()
{


}



