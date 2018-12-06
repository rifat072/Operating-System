#include "include/screen.h"
#include "include/kb.h"
#include "include/string.h"

int kmain()
{
   clearScreen();
   print("Welcome\n");
   while (1)
   {
            print("\nuser:~$ ");
            
            string ch = readStr();

            if(strEql(ch,"cmd"))
            {
                print("\nAlready in cmd\n");
            }
            else if(strEql(ch,"clear"))
            {
                clearScreen();
            }
            else if(ch[0] == 'p' && ch[1] == 'r' && ch[2] == 'i' && ch[3] == 'n' && ch[4] == 't' && ch[5] == ' '){
            	print(ch+6);
            }
            else if(ch[0] =='s' && ch[1] == 'u' && ch[2] == 'b' && ch[3] == 's' && ch[4] == 't' && ch[5] == 'r' && ch[6] ==' '){
            	screen_substr(ch+7);
            }
            else if(ch[0] =='s' && ch[1] == 'u' && ch[2] == 'b' && ch[3] == 's' && ch[4] == 't' && ch[5] == 'r' && ch[6] == 'p' && ch[7] == 'r' && ch[8] == 'e' && ch[9] == 'v' && ch[10] ==' '){
            	screen_substrprev(ch+11);
            }
            else
            {
                print("\nBad command!\n");
            }

            
            print("\n");        
   }
    
}
