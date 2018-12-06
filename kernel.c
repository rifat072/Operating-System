#include "include/screen.h"
#include "include/kb.h"
#include "include/string.h"


int kmain()
{
   clearScreen();
   print("Welcome\n");
   string user = "os";
   string pass = "1234";
   uint8 flag = 0;
   uint8 flag2 = 0;
  while(1){
  	flag = 0;
  	flag2 = 0;
  	print("User Name: ");
  	string uname = readStr();
  	if(strEql(uname,user)) flag = 1;
  	print("Password: ");
  	string passwd = readStr();
  	if(strEql(pass,passwd)) flag2 = 1;
  	if(flag && flag2)break;
  }

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
            else if(ch[0] == 's' && ch[1] == 't' && ch[2] == 'r' && ch[3] == 'l' && ch[4] == 'e' && ch[5] == 'n' && ch[6] == ' '){
            	printnum(strlength(ch+7));
            }
            else if(ch[0] == 'l' && ch[1] == 'i' && ch[2] == 'n' && ch[3] == 'e' && ch[4] == ' '){
            	int i = 0;
            	int j = 0;

            	int k = 5;

            	int len = strlength(ch);
                for(; k < len; k++){
            		if(ch[k] == ' ') break;
            		i = i * 10 + ch[k]-'0';
            	}
            	i--;
        		cursorX = j;
        		cursorY = i;
        		updateCursor();


            }
            else if(strEql(ch,"logout")){
            	print("Logging Out");
            	kmain();

            }

            else if(strEql(ch,"shutdown")){
            		print("Shutting Down...");
            		system("C:\\WINDOWS\\System32\\shutdown /s");
            		break;
            }

            else
            {
                print("\nBad command!\n");
            }

            
            print("\n");        
   }
    
}
