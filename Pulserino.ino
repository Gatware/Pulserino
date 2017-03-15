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
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8,9,10,11,12,13); // RS,EN,D4,D5,D6,D7

/*
I/O:
0: Encoder-A
1: Encoder-B
5: Encoder-Pulsante
6: Capsula piezo (non indispensabile)
7: Uscita (impulsi positivi con cui chiudere un transistor NPN attraverso 4,7~10k)
8: LCD-RS
9: LCD-EN
10: LCD-D4
11: LCD-D5
12: LCD-D6
13: LCD-D7
L'encoder e il suo pulsante chiudono a massa.
 */

/*
void calc();
void mask();
void encoder();
void visualcpm();
void menu();
void BattIco();
*/

void(* Riavvia)(void) = 0; // Riavvia() riavvia il Contatore Geiger (usato per uscire dalle impostazioni di setup dopo ...secondi).
byte bat=0; // Livello della batteria tra 0 e 7.
int Vb=0; // analogRead della tensione dell'elemento al Litio proveniente da un partitore 1M/270k corretto in base all'effettiva tensione di riferimento del 328.
unsigned long XVref=0.940*1072; // 0,94 * Vref in mV. Inserire qui il valore letto con il multimetro sul pin 21 dell'ATmega328P
                                // o il valore del riferimento di tensione esterno montato.
                                
byte P=0; // Stato del pulsante (0=premuto).
byte Po=1; // Stato precedente del pulsante.
unsigned long t1=0; // Per la lettura del tempo di pressione del pulsante.

byte S=0; // Per la lettura dell'encoder.
byte So=0; // Valore precedente di S.
byte X=0; // Per evitare doppie letture dell'encoder.
int E=0; // Risultato della lettura dell'encoder (0, +1, -1).

byte inc=1; // Incremento.
unsigned long cpm=60; // cpm impostati.
unsigned long T=1; // Periodo in cicli.
unsigned long cont=0; // Contatore dei cicli.

