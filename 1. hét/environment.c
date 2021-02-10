/*
A #include egy előfeldolgozó utasitás/direktiva amivel lényegében más fileokban található kódokat tudunk felhasználni a sajátunkban.
Ezek lehetnek rendszer által meghatározottak, mint pl. az stdio.h, ezeket mind kacsacsőr közé rakjuk.
És lehetnek felhasználó által definiált header fileok is, azokat macskakörömmel körbevonva szoktuk inkludálni.
Ha az általunk létrehozott header file nem a munkakönyvtárunkban található, akkor elérési út megadásával is be tudjuk inkludálni.
*/
#include <stdio.h> // rendszer által definiált
#include <stdlib.h>
#include <string.h>
#include "operator.h" // felhasználó által definiált
#include "../include/header.h" // relativ include

/*
A #define is egy előfeldolgozó utasitás amivel úgynevezett makrókat tudunk megfogalmazni.
Ezeknek a makróknak a segitségével könnyen tudunk konstansokat definiálni a programunk használatához.
Ezknek a makróknak a formája a következő: #define <név> <érték>.
Értéknek a következőket használhatjuk: konstans érték (sztring, szám stb.), kifejezés.
*/
#define NoArg 1 //konstans
#define NoString "Main String" //konstans
#define Addition (5 + 5) //kiértékelés
#define CircleArea(r) (3.14 * (r) * (r)) // függvényszerű kiértékelés
// float area = CircleArea(10);

/*
Fontos hogy a programunk tudjon közvetlen kommunikálni az operációs rendszerrel, ezért használni fogunk paranccsori argumentumokat.
Az operácios rendszerünk a main függvényt fogja hivni programfuttatáskor.
Az argc egy int tipusú változó ami a paranccsori argumentumok számát tartalmazza. Ide beletartozik a program neve, tehát argc >= 1
Az argv egy char * okat tartalmazó tömb, ez lényegen azt jelenti hogy a tömb egyes elemei mutatók az argumentum sztringek kezdőcimeire.
A parancssori argumentumokat a programunk sztringként fogja kezelni, még akkor is ha számot adunk át a parancsértelmezőnek.
Tehat maga az argv[1] egy mutató lesz a második parancssori argumentum kezdőcimére.
Érdemes argumentumok vizsgálatánál az argc értéket használni viszonyitási alapként.
Pl. az if(argv[2] == NULL) helytelen, hiszen ha a harmadik argumentumunk tényleg nem lézetezne, akkor index hibát kapnánk.
*/
int main(int argc, char *argv[]){
   /*
   char* változók deklarálása, ilyen esetben ezeknek az értéke jelenleg (null).
   */
   char *var, *value;
   /*
   Sztringek kezelésénél sokszor felvetődhet a következő:
   Miben különbözik a következő kettő:
   */
   char* usingPointer = "Vakáció";
   char usingArray[] = "Vakáció";
   /*
   Mindkettő adatot generál a memóriába, abban különböznek, hogy hogy lépünk vele interakcióba.
   A char* az egy pointer ami változó C-ben.
   A tömb az nem egy változó hanem egy adatszerkezet.
   A char[] egy specifikus hely a memóriában, ami mindig ugyanazon a kezdőcimen lesz megtalálható, csak indexelhetünk, kezdőcimet nem módosithatunk.
   A mutató értékét viszont könnyen el tudjuk tolni, ezzel megváltoztatva a szting kezdőcimét.
   Ezzel lényegében a memóriaművelet O(1) konstans idejű lesz, mig a tömbös megoldással O(n) lineáris.
   */
   usingPointer++;

   for (int i = 0; i < strlen(usingArray)-1; i++){
     usingArray[i] = usingArray[i+1];
   }
   usingArray[strlen(usingArray)-1] = '\0';

   printf("%s - pointer\n%s - array\n", usingPointer, usingArray);

   if(argc == 1){
     /*
     Az fprintf egy C sztringet formázott formában egy stream-re, vagy úgymond adatfolyamra helyezi.
     Ilyenek lehetnek a standard bemenet, vagy kimenet. (stdin, stdout)
     Az stderr az egy error stream ahova általában hibaüzeneteket szoktunk kiküldeni.
     Ezek a kimenetek persze operációs rendszer szinten átiranyithatóak pl: fájlokba.
     Sőt azt is el tudjuk érni hogy az egyik program kimenete a másiknak a "bemenete" legyen.
     Ezekre mind van példa a jegyzetben.
     */
      fprintf(stderr," %s: I need an argument.\n",argv[0]);
      return NoArg;
      }

   if(argc == 2) {
      // A var változónk az második parancssori argumentum kezdőcimére fog mutatni.
      var   = argv[1];
      /*
      A getenv függvény segitségével környezeti változók értékét tudjuk lekérdezni.
      stdlib.h-ban talalhato meg ez a függvény.
      Egy string kezdőcimét kell neki átadni, majd annak megfelelően fogja visszaadni a környezeti változó értékét.
      NULL pointer ad vissza ha a környezeti változó nem létezik, vagy csak szimplán nem társul hozzá érték.
      A környezeti változók lényegében szöveges formában tartalmaznak információt a rendszerről.
      Példaul egy elég közismert környezeti változó a PATH.
      lényegében ez a környezeti változó fogja tárolni azon könyvtárak listáját, ahol a parancsértelmező keresni fogja a neki kiadott parancsokat.
      A putenv nevű függvény segitségével egy környezeti változó értékét módosithatjuk vagy állithatjuk be.
      Az általunk létrehozott változók csak lokálisan maradnak meg, igy azok csak a programon futása alatt érhetőek el.
      A környezeti változók listája a jegyzetben megtalálhatóak.
      */
      value = getenv(var);
      if(value!=NULL)
         printf("$%s=%s\n", var, value);
      else
         printf("$%s has no value\n", var);
      }

   if(argc == 3) {
      char *string;
      var    = argv[1];
      value  = argv[2];
      /*
      A malloc lefoglal egy memóriaterületet es visszaadja annek a lefoglalt területnek a cimét.
      Ezt egy void* formában adja vissza igy ahhoz, hogy a számunkra megfelelő adatot el tudjuk tárolni ott, kasztolásra lesz szükségünk.
      Ha a foglalási igény nem sikerül egy NULL pointert kapunk vissza.
      A calloc ugyanúgy void*-ot ad vissza de az adott memóriaterületet kinullázza.
      Tippként, ha a az egész meghatározott memóriaterületet ki akarjátok tölteni, akkor mallocot használjatok, ha pedig nem, akkor calloc-ot.
      Ez azért jó nekünk, mivel nem szeretjük az inicializálatlan memóriaterületeket.
       +2-őt maga a '/0' lezáró karakterekért szoktuk odatenni.
      */
      string = (char*)malloc(strlen(var)+strlen(value)+2);

      /*
      Bemasáljuk a első paraméterben adott memóriahelyre a második paraméterben kapott cimen lévő sztringet. A lezáró karaktert is másolja.
      Ezek után csak konkatenálunk a bemásolt sztinghez.
      Ez azért kell, mert egy környezeti változó az alábbi formában fordul elő a rendszerünkben: <változó>=<érték>
      */
      strcpy(string,var);
      strcat(string,"=");
      strcat(string,value);
      printf("Calling putenv with: %s\n",string);
      putenv(string);
      /*
      Felszabaditjuk az adott memóriahelyet, amire a kezdőcim mutat.
      Felmerülhet a kérdés hogy honnan tudja a program, hogy hol van ennek a memóriablokknak a vége.
      Igazából a malloc függvényünk kicsit csal, mivel kicsivel több helyet foglal le, mint amit mi átadtunk neki, és eltárol magának más információkat a lefoglalt helyről.
      */
      free(string);
      }

   /*
   EXIT_FAILURE, EXIT_SUCCESS nevesitett konstansok.
   EXIT_SUCCESS általában a 0 értéket veszi fel, tehát egyenértékű a return 0-val.
   Ezek az stdlib.h-ban vannak definiálva, tehát ha 0 helyett ezt szeretnéd használni feltétlenül be kell inkludálni.
   Azert szokták pár esetben ezt használni, mert programozásból van egy elterjedt fogalom, hogy magic number/string.
   Ezeket úgymond hardcode-olt konstansoknak vesszük, amiket annyira nem szeretünk és annyira nem is beszédesek.
   Az EXIT_SUCCESS első olvasásra egyértelmű és lényegre törő, a 0 egy hozzá nem értőnek jelenthet akármit.
   EXIT_FAILURE 0-tól eltérő érték.
   */
   return EXIT_SUCCESS;
   }