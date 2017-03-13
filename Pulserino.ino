/*
***********************************************************************
*    *********************** Pulserino **************************     *
*  ******* Un calibratore per contatori Geiger con Arduino ********   *
*   ***********  Copyright Gianluca Giangreco 2017   *************    *
**************  https://github.com/Gatware/Pulserino  *****************                              
*                                                                     *
* Questo software è a puro scopo didattico, pertanto  non assumo res- *
* ponsabilità sulla precisione e veridicità  dei valori riportati. Mi *
* sono impegnato  nello scriverlo e ringrazio fin d'ora  chi  volesse *
* aiutarmi con correzioni, miglioramenti o suggerimenti.              *
*                                                                     *
* GEIGERINO is free software:you can redistribute it and/or modify it *
* under the terms of  the GNU General Public License, as published by *
* the  Free Software Foundation,  either version 3 of the License, or *
* (at your option) any later version.                                 *
*                                                                     *
* GEIGERINO  is distributed  to share  my work  and my experience and *
* to improve it together, but WITHOUT ANY WARRANTY relating to proper *
* working and accuracy. See the GNU General Public License  for  more * 
* details.                                                            *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                     *
*          See "a_commenti" tab for connections details.              *
*                                                                     *
*      Realizzato e collaudato con Arduino Uno (ATMEGA 328P).         *
*                                                                     *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define soglia1 0.1  // V

#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8,9,10,11,12,13); // RS,EN,D4,D5,D6,D7
void(* Riavvia)(void) = 0; // Riavvia() riavvia il Contatore Geiger (usato per uscire dalle impostazioni di setup dopo ...secondi).
byte bat=0;
int Vb=0;
unsigned long XVref=0.940*1072; // 0,94 * Vref in mV. Inserire qui il valore letto con il multimetro sul pin 21 dell'ATmega328P
                                // o il valore del riferimento di tensione esterno montato.
unsigned long t1=0; 
int E=0;
byte P=0;
byte Po=1;
byte inc=1; // Incremento.
unsigned long cpm=60; // cpm impostati.
unsigned long T=1; // Periodo in uS.
unsigned long cont=0;
byte S=0;
byte So=0;
byte X=0;
