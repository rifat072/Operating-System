#ifndef SCREEN_H
#define SCREEN_H
#include "types.h"
#include "system.h"
#include "string.h"
int cursorX = 0, cursorY = 0;
const uint8 sw = 80,sh = 25,sd = 2;                                                     
void clearLine(uint8 from,uint8 to)
{
        uint16 i = sw * from * sd;
        string vidmem=(string)0xb8000;
        for(i;i<(sw*to*sd);i+=2)
        {
                vidmem[i] = 0x0;
                vidmem[i+1] = 0x0F;
        }
}
void updateCursor()
{
    unsigned temp;

    temp = cursorY * sw + cursorX;         
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);   
    outportb(0x3D4, 15); 
    outportb(0x3D5, temp);
}
void clearScreen()
{
        clearLine(0,sh-1);
        cursorX = 0;
        cursorY = 0;
        updateCursor();
}

void scrollUp(uint8 lineNumber)
{
        string vidmem = (string)0xb8000;
        uint16 i = 0;
        clearLine(0,lineNumber-1);    
        for (i;i<sw*(sh-1)*sd;i+=2)
        {
                vidmem[i] = vidmem[i+sw*sd*lineNumber];
                vidmem[i+1] = vidmem[i+sw*sd*lineNumber + 1];
        }
        clearLine(sh-1-lineNumber,sh-1);
        if((cursorY - lineNumber) < 0 ) 
        {
                cursorY = 0;
                cursorX = 0;
        } 
        else 
        {
                cursorY -= lineNumber;
        }
        updateCursor();
}


void newLineCheck()
{
        if(cursorY >=sh-1)
        {
                scrollUp(1);
        }
}

void printch(char c)
{
    string vidmem = (string) 0xb8000;     
    switch(c)
    {
        case (0x08):
                if(cursorX > 0) 
                {
	                cursorX--;									
                        vidmem[(cursorY * sw + cursorX)*sd]=0x00;	                              
	        	}
	        break;
       /* case (0x09):
                cursorX = (cursorX + 8) & ~(8 - 1); 
                break;*/
        case ('\r'):
                cursorX = 0;
                break;
        case ('\n'):
                cursorX = 0;
                cursorY++;
                break;
        default:
                vidmem [((cursorY * sw + cursorX))*sd] = c;
                vidmem [((cursorY * sw + cursorX))*sd+1] = 0x0F;
                cursorX++; 
                break;
	
    }
    if(cursorX >= sw)                                                                   
    {
        cursorX = 0;                                                                
        cursorY++;                                                                    
    }
    updateCursor();
    newLineCheck();
}

void print (string ch)
{
        uint16 i = 0;
        uint8 length = strlength(ch);   
        for(i;i<length;i++)
        {
                printch(ch[i]);
        }
}

void printnum (int32 num) {
	int32 rmdr;
	if (num < 0) {
		rmdr = -num;
        printch('-');
	}
	else
		rmdr = num;
	int32 rm10;
	int32 dvsr;
	int32 quot;
    rm10 = rmdr/10;
    dvsr = 1;
    while(dvsr <= rm10)
        dvsr *= 10;
    while(dvsr){
        quot = rmdr / dvsr;
        printch((char)quot + '0');
        rmdr %= dvsr;
        dvsr /= 10;
    }
}

void screen_substr(string str) {
    string vidmem = (string) 0xb8000;
	uint8 len = strlength(str);
	uint32 i, j;
	
	for (i=0; i<(cursorY-1)*sw*2-len*2; i+=2) {
		int found = 1;
		for (j=0; j<len; j++) {
			if (vidmem[i+j*2] != str[j]) {
				found = 0;
				break;
			}
		}
		if (found) {
			for (j=0; j<len*2; j+=2) {
				vidmem[i+j+1] = 0xF0;
			}
		}
	}
	
}

void screen_substrprev(string str) {
    string vidmem = (string) 0xb8000;
	uint8 len = strlength(str);
	uint32 i, j;
	
	for (i=cursorY-1; i<(cursorY-1)*sw*2-len*2; i+=2) {
		int found = 1;
		for (j=0; j<len; j++) {
			if (vidmem[i+j*2] != str[j]) {
				found = 0;
				break;
			}
		}
		if (found) {
			for (j=0; j<len*2; j+=2) {
				vidmem[i+j+1] = 0xF0;
			}
		}
	}
	
}


#endif