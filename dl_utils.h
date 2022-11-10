#include <stdio.h>
#include <stdlib.h>


int dl_hex2bin(const char *pcInBuffer, char *pcOutBuffer, int iLen);
int dl_bin2hex(unsigned char *pcInBuffer, char *pcOutBuffer, int iLen);
int bin2hex(unsigned char *pcInBuffer, char *pcOutBuffer, int iLen);
void toUpperCase(unsigned char *pszString);