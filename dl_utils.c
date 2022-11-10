
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void dl_ascii_to_binary(unsigned char *dest, unsigned char *src, int length);
void hex2asc(unsigned char *outp, unsigned char *inp, int length);

int dl_hex2bin(const char *pcInBuffer, char *pcOutBuffer, int iLen)
{
	int 	c;
	char	*p;
	int 	iBytes=0;
	const char *hextable = "0123456789ABCDEF";
	int nibble = 0;
	int nibble_val;

	while(iBytes < iLen){
		c = *pcInBuffer++;
		if (c == 0)
			break;

		c = toupper(c);

		p = strchr(hextable, c);
		if (p)
		{
			if (nibble & 1)
			{
				iBytes++;
				*pcOutBuffer = (nibble_val << 4 | (p - hextable));
				pcOutBuffer++;
			}//if
			else
			{
				nibble_val = (p - hextable);
			}//else
			nibble++;
		}//if
		else
		{
			nibble = 0;
		}//else
	}//while
	
	return iBytes;
}//hex2bin

int dl_bin2hex(unsigned char *pcInBuffer, char *pcOutBuffer, int iLen){

    /*int                     iCount;
	char	                *pcBuffer;
    unsigned char           *pcTemp;
	unsigned char	        ucCh;

    memset(pcOutBuffer, 0, sizeof (pcOutBuffer));
    pcTemp = pcInBuffer;
    pcBuffer = pcOutBuffer;
    for (iCount = 0; iCount < iLen; iCount++) {
            ucCh = *pcTemp;
            pcBuffer += sprintf(pcBuffer, "%02X", (int) ucCh);
            pcTemp++;
    }//while*/

	//bin2ascii(const void *data, size_t len ,char *dest);

	hex2asc(pcOutBuffer, pcInBuffer, iLen);

	return 0;
}

int bin2hex(unsigned char *pcInBuffer, char *pcOutBuffer, int iLen){

	int                     iCount;
	char	                *pcBuffer;
	unsigned char           *pcTemp;
	unsigned char	        ucCh;

	memset(pcOutBuffer, 0, sizeof (pcOutBuffer));
	pcTemp = pcInBuffer;
	pcBuffer = pcOutBuffer;
	for (iCount = 0; iCount < iLen; iCount++) {
		ucCh = *pcTemp;
		pcBuffer += sprintf(pcBuffer, "%02X", (int) ucCh);
		pcTemp++;
	}//while*/

	//bin2ascii(const void *data, size_t len ,char *dest);

	//hex2asc(pcOutBuffer, pcInBuffer, iLen);

	return 0;
}

void toUpperCase(unsigned char *pszString)
{
    if ((pszString == NULL))
    {
        return;
    }

    while( *pszString )
    {
        *pszString = toupper((char)*pszString);
        pszString++;
    }
}


void dl_ascii_to_binary(unsigned char *dest, unsigned char *src, int length)
{	
	/* length = length of source */
	short   i=0;
	unsigned char    digit_val;

	if (length & 0x0001)
	{	// length is odd, so do some adjustment to put a zero at the start
        if ((src[0] - '0') > 9)
		{
            if ((src[0] - 'A') > 5)
                digit_val = (src[0] - 'a' + 10);
            else
                digit_val = (src[0] - 'A' + 10);
		}
		else
            digit_val = (src[0] - '0');

        dest[0] = 0;
        dest[0] |= (digit_val & 0x0F);
        dest++;
        src++;
        length--;
	}

    while(i < length)
	{
        if ((src[i] - '0') > 9)
		{
            if ((src[0] - 'A') > 5)
                digit_val = (src[i] - 'a' + 10);
            else
                digit_val = (src[i] - 'A' + 10);
		}
        else
            digit_val = (src[i] - '0');

        if (i & 0x0001)
            dest[i/2] |= (digit_val & 0x0F);
        else
		{
            dest[i/2] = 0;
            dest[i/2] |= ((digit_val << 4) & 0xF0);
		}

        i++;
	}

    return;
}

/*--------------------------------------------------------------------------
    Function:		hex2asc
    Description:
    Parameters:		BYTE *, BYTE *, int
    Returns:
	Notes:
--------------------------------------------------------------------------*/
void hex2asc(unsigned char *outp, unsigned char *inp, int length)
{
	short i = 0;

	for(i=0;i<length;i++)
	{
		if((inp[i] >> 4) > 9)
			outp[i*2] = (unsigned char) ((inp[i]>>4) + 'A' - 10);
		else
			outp[i*2] = (unsigned char) ((inp[i]>>4) + '0');

		if((inp[i] & 0x0f) > 9)
			outp[i*2+1] = (unsigned char) ((inp[i] & 0x0f) + 'A' - 10);
		else
			outp[i*2+1] = (unsigned char) ((inp[i] & 0x0f) + '0');
	}
	outp[i*2] = 0;

	return;
}