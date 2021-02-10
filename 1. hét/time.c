#include<stdio.h>
#include<time.h>
#include<unistd.h>

/*
Két statikus sztring tömböt definiálunk, ezeket fogjuk használni a későbbiekben.
*/
char *Months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char *Days[]   = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};


int main(){

    /*
    A time.h header definiál egy speciális time_t tipust az idő kezelésére.
    Ennek a tipusnak a felhasználásával rengeteg információt meg tudunk jeleniteni az aktuális dátummal kapcsolatosan.
    Az act_time2 és act_time3 másodpercek tárolására lesz felhasználva
    */
    time_t act_time1;
    int act_time2, act_time3;
    /*
    A struct tm * segitségével az aktuális dátumot nagyon részletesen el tudjuk tárolni.
    Azért használunk struktúra mutatót, hiszen a függvény, amivel majd fel szeretnénk tölteni egy struktúrára mutatóval tér vissza.
    Ennek a rekordnak több mezője van:
    struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday; 1-31
    int tm_mon;  0-11 hónapok
    int tm_year; 1900-tól számol éveket
    int tm_wday; 0-6
    int tm_yday; 0-365
    int tm_isdst;
    }
    */
    struct tm *act_time4;
    /*
    Az aktuális időt a time() függvénnyel tudjuk lekérni, ami vissza fogja adni 1970 január 1 óta eltelt másodpercek számát.
    Ez 32 biten van tárolva szóval csak 2038-ig tudjuk az időt ilyen módon tárolni.
    */
    act_time2 = time(&act_time1);
    printf("The actual time is: %d\n",act_time2);
    /*
    A ctime az ember számára olvasható sztringet tud létrehozni egy time_t tipusból.
    */
    printf("This means: %s",ctime(&act_time1));
    /*
    A localtime lesz az a függvény, ami szétbontja a struktúra mezőire a kapott time_t tipusunkat.
    struct tm* localtime(const time_t *timer);
    */
    act_time4 = localtime(&act_time1);
    printf("So the local time is: %d %s %d  ",(*act_time4).tm_year+1900,Months[(*act_time4).tm_mon],(*act_time4).tm_mday);
    printf("%d:%d:%d\n",(*act_time4).tm_hour,(*act_time4).tm_min,(*act_time4).tm_sec);
    printf(" It is the %dth day of the year.\n",(*act_time4).tm_yday);
    printf(" It is %s.\n",Days[(*act_time4).tm_wday]);

    /*
    Maga a program futása és maga a szál amin fut felfüggeszthető egy adott időre a sleep utasitás segitségével.
    Paraméterként a másodpercek számát várja tőlünk.
    A usleep hasonló a sleephez de ez mikroszekundumokba várja az időt.
    */
    sleep(2);
    usleep(1500000);

    /*
    Lekértjük újra a másodpercek számát 1970 jan 1 óta, majd ebből kivonjuk az előzőleg lekérdezett értékünket.
    Ezzel könnyen meg tudjuk kapni, hogy hány másodpercig futott a program.
    */
    act_time3 = time(&act_time1);
    printf("It took: %ds\n",act_time3-act_time2);
    return 0;
    }