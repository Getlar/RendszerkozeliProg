#include<stdio.h>
/*
Számunkra elérhetőek lesznek bizonyos előre definiált azonositók, amelyek egyértelműen árulkodnak az adott operációs rendszerről amin fut a kódunk.
Definiáltnak nevezzük pl. az strcpy-t is, ha string.h header állomány inkludálva van a kódunkban. Hasonlóan működnek a lenti azonositók is.
Forditási direktivák segitségével ugy tudunk létrehozni rendszerfüggő nevesitett konstansokat is.
Ezek segitségével az adott operációs rendszerhez illeszkedő utasitásokat tudunk végrehajtani.
Az #if, #elif direktivák használatakor mindig le kell zárjuk az elágazást egy #endif direktivával.
*/
#if defined(linux) || defined(_linux) || defined(__linux__) || defined(__unix__)
  #define OSTYPE 1
#elif defined(_WIN32) || defined(_WINDOWS) || defined(__WINDOWS__)
  #define OSTYPE 2
#elif defined(MSDOS) || defined(_MSDOS) || defined(__MSDOS__)
  #define OSTYPE 3
#elif (defined(__MACH__) && defined(__APPLE__))
  #define OSTYPE 4
#else
  #define OSTYPE 0
#endif

/*
Egyszerű switch-case rendszer, OSTYPE amit viszonyitunk, a case-ek pedig, hogy mihez.
Ha egyezést találunk mindig zárjuk a case blokkot egy break utasitással.
Ha ezt nem tesszük meg a switch szerkezet végig fog menni az összes case-en szükségtelenül.
*/
int main(){
   switch(OSTYPE){
     case 1:
       printf("This is a Unix/Linux system.\n");
       break;
     case 2:
       printf("This is a Windows system.\n");
       break;
     case 3:
       printf("This is a MS-DOS system.\n");
       break;
     case 4:
       printf("This is an Apple/Machintos system.\n");
       break;
     default:
       printf("I don't know what kind of operating system is this.\n");
     }
   return 0;
   }