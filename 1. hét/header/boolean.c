/*** gcc -o boolean boolean.c BoolFunc.c ***/
/*
Újrafelhasználás érdekében érdemes sokszor pár olyan alprogramot kiszerveznünk egy header állomanyba, amit esetleg sokat használunk a program más területein.
Ezeket egyszerűen egy .h állomanyba át is tudjuk vinni, ami után könnyen inkludálni tudjuk a főprogramunkba.
Hibalehetőségként ilyenkor fellép az a probléma, hogy dolgokat felüldefiniálunk.
Ilyenkor érdemes használni az előzőleg tanult #if #elif #endif direktivákat, hogy ezekre kivételeket tudjunk megfogalmazni.
Ha több forrásból álló programot szeretnénk leforditani, akkor ezt a gcc-vel meg tudjuk tenni.
Arra ügyeljünk, hogy csak egy fő programegységünk legyen. (main)
A forditó .o kiterjesztésű fájllá alakitja a két .c féjlunkat majd ezeket a linker program fogja egyesiteni.
*/

#include <stdio.h>
// a boolean.h inkludálása felesleges hiszen az operator.h-ban már inkludátuk.
//#include "boolean.h"
#include "operator.h"

int main(){
   boolean x,y,z;
   x=true;
   y=not IsEqual(3, 2.4);
   z=(x or y) and IsEven(321);
   boolprint(" x=%b.\n",x);
   boolprint("The value of y is %b, as it is expected.\n",y);
   boolprint("A %b value is stored in z.\n",z);
   return 0;
   }