/*
 * File:   main_2.c
 * Author: Omar Al-Bayati
 *
 * Created on January 9, 2018, 1:04 PM
 */
//Raenell was here!

#include "xc.h"
#include "configBits.h"
void remapSpiIO(void);
void delayFull();
void delay();
void spi_write(unsigned short put);
unsigned char spi_read(unsigned char v);

int main(void) {
    unsigned char tt;
    initSPI();
    remapSpiIO();
    while (1) {
        _LATB7 = 0X00;
        spi_write_long(0x222, 0x55);
     
        _LATB7 = 0XFF;
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
    }


    /* {
         tt = spi_read();
         delay();
         spi_write(tt);
         delay();
     }*/

    /*  while (1){
          unsigned char ab[10];
          unsigned short CNT = 0x1234;
          char *PT = (char*)(&CNT);
          ab[0] = (unsigned char)(*(PT+1));
          ab[1] = (unsigned char)(*(PT+0));
      }
     */
    return 0;
}

void initSPI(void) {
    IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
    IEC0bits.SPI1IE = 0; //disable the Interrupt

    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; //Internal Serial Clock is Enabled.
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1CON1bits.DISSDO = 0; //SDOx pin is controlled by the module.
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1CON1bits.MODE16 = 0; //Communication is byte-wide (8 bits).
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1CON1bits.SMP = 0; //Input Data is sampled at the middle of data output time.CHANGED
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1CON1bits.CKE = 1; //Serial output data changes on transition from
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    //Idle clock state to active clock state
    SPI1CON1bits.CKP =0; //Idle state for clock is a low level;
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    //active state is a high level
    SPI1CON1bits.MSTEN = 1; //Master Mode Enabled
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1STATbits.SPIEN = 1; //Enable SPI Module
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1CON1bits.PPRE = 0b00; //primary scealar 64:1
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    SPI1CON1bits.SPRE = 0b000; //secondary prscalar 8:1

    //Interrupt Controller Settings
    IFS0bits.SPI1EIF = 0;
    Nop();
    Nop();
    IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
    IEC0bits.SPI1IE = 0; //Enable the Interrupt
}

void spi_write(unsigned short put) {
    unsigned short b;
    IFS0bits.SPI1IF = 0;
    b = SPI1BUF;
    Nop();
    SPI1BUF = put;
    Nop();
    while (IFS0bits.SPI1IF == 0) {
    }
}

unsigned char spi_read(unsigned char v) {
    // spi_write(0x00);
    // while (SPI1STATbits.SPIRBF==0) {};

    return (SPI1BUF);

}

void delayFull(void) {
    unsigned int i;
    for (i = 0; i < 65535; i++);
    // 53ms delay
}

void delay(void) {
    unsigned int i;
    for (i = 0; i < 250; i++);

}

void remapSpiIO(void) {
    RPINR20bits.SCK1R = 0b01000; // Clock Input (Pin 17)
    RPINR20bits.SDI1R = 0b00110; // Slave Data IN (Pin 15)  

    _TRISB9 = 0; // B9 is output (Pin 18)
    _RP9R = 7; // Remap Data output to (Pin 18)

    _TRISB7 = 0; // B7 is output (Pin 16)
    _RP7R = 9; // Remap chip select to (Pin 16)

    _TRISB4 = 0; // B8 is output (Pin 11)
    _RP4R = 8; // Remap clock output select to (Pin 11)
}

void spi_write_long(unsigned short address, unsigned char data)
{
    unsigned char a;
    unsigned char d;
    address = address << 4;
    Nop();
    address = address | 0x8010;
    Nop();
    a = (unsigned char) address;
    spi_write(a);
    Nop();
    address= address >>8;
    a = (unsigned char) address;
    spi_write(a); 
    Nop();
    //data = data << 8;
    d = (unsigned char) data;
    spi_write (d);
    Nop();
       
    
}
