#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1000000
/*
A számitógépek nem tudnak igazi véletlenszámokat előállitani, mivel deteminisztikus eszközök, tehát mindig előre kiszámitható, hogy mit fognak csinálni.
Nekünk programozóként csak pszeudo-random számok generálására van lehetőségünk, amik látszólagosan véletlenszerűek.
A véletlen számok generálásához általában egy úgynevezett seed-re vagy mag-ra van szükség.
Ha ugyanazzal a seed-del etetjük a programunkat, akkor ugyanazokat a véletlenszámokat fogja generálni.
Ne felejtsük el a szuper Minecraftos példámat, amit az órán mondtam el. :)
C-ben nagyon egyszerűen fel lehetne használni a time() által visszaadott értéket, mivel az másodpercenként mindig mást fog visszaadni.
A rand() függvényünk az általunk adott seed alapján fog létrehozni egy teljesen véletlenszerű számot. Ennek nagysága operációs rendszertől függ.
Egy maximum érték van meghatározva erre, ami egy nevesitett konstansként van eltárolva, amit RAND_MAX-ként fogtok majd látni.
A seed beállitását az srand() eljárással tudjuk megtenni, ha ezt nem tesszük meg a rand() mindig ugyanazt az értéket fogja visszaadni.
A program legelején ezért meg kell hivjuk az srand() eljárást majd paraméterkéntátadjuk 1970 óta eltelt másodpercek számát.
Persze ha nagyon gyorsan futtatjuk egymás utan a programunkat előfordulhat hogy ugyanazt a random értéket kapjuk.
*/
int main(){
  /*
  Lokális változók, fontos megjegyezni, hogy ilyen esetben az értékük meghatározhatatlan.
  Ha statikus változóként hoznánk őket létre (main-en kivül) akkor inicializálódnának egy 0 értékkel.
  */
  int    i;
  int    x;
  double y;
  /*
  Dobások számára, inicializált tömb.
  */
  int    a[6]={0,0,0,0,0,0};
  int    b[6]={0,0,0,0,0,0};

  srand(time(NULL));
  printf(" 0 <= %d <=%d\n",rand(),RAND_MAX);

  /*
  Matematikai transzformáció segitségével könnyen meghatározhatunk egy intervallumot, amelyen belül szeretnénk számokat kapni.
  A (B-A+1)-ggyel megkapjuk hogy hány értéket szeretnénk kapni generálás után.
  Jelen esetben ez 11, igy százalékosan elosztjuk a kapott számot ezzel az értékkel, ezzel bitositva, hogy 0 és 11 között fogunk számokat kapni.
  Ezek után hozzáadjuk a kapott érékhez az alső határunkat és meg is kaptuk a intervallumba eső számot.
  */
  printf("20 <= %d <=30\n",rand()%(30-20+1)+20); // pozitiv intervallum
  printf("-20 <= %d <=30\n", rand()%(30-(-20)+1)+(-20)); // negativ intervallum, 51 érték = [0, 50], ebből -20 => [-20, 30]
  /*
  Egyszerű normalizálás [0,1] intervallumra.
  */
  printf("0.000000 <= %f <=1.000000\n",(float)rand()/RAND_MAX);
  printf("6.200000 <= %f <=9.800000\n",(float)rand()/RAND_MAX*(9.8-6.2)+6.2);

  /*
  Dobókockás játék random számok segitségével.
  1 millió dobásunk lesz, és hogy biztositsuk, hogy minden számértéket egyenlő eloszlással kapjuk meg a következőt csináljuk:
  Addig dobigáljuk a kockát, amig egy RAND_MAX - y értéket kapunk ahol y = 1 vagy 2 vagy ... vagy 6
  Ha ez megtörtént, akkor ezt százalékosan elosztjuk 6-tal és kapunk egy számot 0 és 5 között.
  Ezt a számot felhasználva indexelésre inkrementáljuk az adott dobás számosságát.
  */
  printf("\nRegular dice (%d throw):\n",N);
  for(i=0;i<N;i++){
    do
      x=rand();
    while(x>=RAND_MAX-RAND_MAX%6);
    a[x%6]++;
    }
  for(i=0;i<6;i++)
    printf("%d:\t%.4f%%\n",i+1,(float)a[i]/N*100);

  /*
  Trükkös dobókocka esetén, úgy módositjuk a játékot, hogy nagyobb esélyeket adunk az egyik érték dobásának.
  A kapott számot normalizáljuk [0,1] intervallumra.
  Ezt az 1 nagyságú intervallumot úgy osztjuk fel 6 részre, hogy:
  1-es dobást [0,0.2] intervallumba eső szám esetén inkrementájuk
  2-6-ig vett dobást pedig 0.16-os inkrementálásonként kapunk.
  [0.2, 0.36] - 2-es dobás
  [0.36, 0.52] - 3-as dobás
  [0.52, 0.68] - 4-es dobás
  [0.68, 0.84] - 5-ös dobás
  [0.84, 1] - 6-os dobás
  Ezzel könnyen látható, hogy egyenletes eloszlást csak a 2-6 dobások között fogunk kapni.
  */
  printf("\nTricky dice (%d throw):\n",N);
  for(i=0;i<N;i++){
    y=(double)rand()/((unsigned)RAND_MAX+1); // 0.0 <= y < 1.0
    if(y<0.2) b[0]++;  //20%
    else      b[(int)((y-0.2)/((1.0-0.2)/5))+1]++;
    }
  for(i=0;i<6;i++)
    printf("%d:\t%.4f%%\n",i+1,(float)b[i]/N*100);

  return 0;
  }
