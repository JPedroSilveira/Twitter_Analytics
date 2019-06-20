#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Remove os acentos e o ç das strings
void StringUtils_removeStringAccents(char* s);

//Passa a string para minusculo
void StringUtils_toLowerCase(char* string);

//Teste básico da função StringUtils_toLowerCase
void StringUtils_toLowerCaseTest();

//Teste básico da função StringUtils_RemoveAccents
void StringUtils_removeAccentsTest();
