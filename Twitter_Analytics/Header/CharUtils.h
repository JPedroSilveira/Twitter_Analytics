#ifndef _CHARUTILSH_
#define _CHARUTILSH_

#include <ctype.h>
#include "./Boolean.h"

//Remove o achando do char
char CharUtils_removeCharAccent(char l);

//Passa o char para minusculo
char CharUtils_toLowerCase(char l);

//Remove acento e converte para min�sculo
char CharUtils_removeCharAccentToLowerCase(char l);

//Verifica se um char � um separador
int isSeparator(char l);

#endif _CHARUTILSH_