/*
enum azaz felsorolásban az adott értékekhez számok kerülnek hozzárendelésre.
Itt az indexelés 0-tól indul igy a false 0 értéket a true 1 értéket fog kapni.
Az alábbi kód megegyezeik a kövezkezővel:
typedef enum bool {false=0, true=1} boolean;
Lényegében neveket tudunk konstansokhoz hozzárendelni.
*/

/*
A typedef tipusdefinicókra szokták használni.
Ezekkel tipusok neveit felülirhatjuk.
Itt a bool tipust irjuk felül boolean-ra.
*/
typedef enum bool {false, true} boolean;

/*
Ha példáúl az int tipust szeretnénk felülirni, akkor a következő kóddal meg is tehetjük.
*/
typedef int INTECSKE;
INTECSKE a = 5;