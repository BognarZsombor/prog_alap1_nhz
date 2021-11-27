# Buszjáratok felhasználói dokumentáció

A **buszjaratok** program arra való, hogy megállók illetve buszjáratok fájlból történő beolvasása után a megállók között útvonalakat keressünk. A járatoknak meg van adva mikor melyik megállóban vannak, igy percre pontosan meg lehet tervezni az mikor hova érkezünk. Az egyes megállók, ha elég közel vannak egymáshoz meg lehet adni, hogy gyalog is át lehessen jutni, ezalatt nem telik el idő. Az útvonaltervezés eredménye a konzolon jelenik meg. A legalsó sorban van az első utasitás, e fölött sorrendben az ezt követők.

### A program inditása után:

Egy menülista jelenik meg, amik közül tudunk parancsot választani. 9 parancs közül lehet választani.
A **segitseg**-gel kiirjuk az elérhető parancsokat.
A **mbeolvas**-sal új megállókat olvashatunk be az eddigiek mellé. Ehhez meg kell adnunk a fájl nevét, amiből be akarunk olvasni. Ennek a fájlnak a kövezkezőképpen kell kinéznie. Az első sorban a megállókat kell felsorolni vesszővel elválasztva (lehet a névben szóköz). Az ezutáni sorokat a főmegállóval kell kezdeni, majd azokat kell felsorolni ahova innen át lehet gyalog szállni, ezeket is vesszővel (itt is lehet szóköz).
```
megallo1,megallo 2,megall o 3
megallo1,megallo 2
megallo 2, megallo1, megall o 3
megall o 3,megallo 2
```
A **beolvas** hasonlóan működik csak további járatokat lehet vele beolvasni, a következő formátumban. Itt is minden szóközzel elválasztva, kivéve az időpontok, azok mindig hh:mm formátumban vannak. Először a járat neve, első indulás, utolsó indulás, első indulás utáni további indulások, megállók felsorolva, közöttük az adott megállóba érkezés időpontja. Az első megállónak 00:00 az érkezése.
```
b72,08:25,22:10,00:10,megallo1,00:00,megallo2,00:38,megallo3,01:03,megallo4,01:42,megallo3,2:15,megallo2,2:55,megallo1,3:10
a36,09:45,20:50,00:25,megallo5,00:00,megallo6,00:28,megallo4,01:00,megallo2,01:25,megallo4,1:55,megallo6,2:22,megallo5,2:49
```

A program minden indulásakor keres egy **jaratok.txt**, illetve egy **megallok.txt** fájlt a mappájában, hogyha léteznek, ezekből beolvas egy alap megállók illetve járatok listát.

A **jarat**-tal kiirathatjuk egy járat adatait. A járat nevét kell paraméterben megadni hozzá.
A **megallo**-val kiirathatjuk egy megálló adatait. A megálló nevét kell paraméterben megadni hozzá.
A **mentes**-sel elmenthetjük az eddig bevitt járatok listáját egy fájlba. A járat nevét kell megadni paraméterként hozzá.
A **mmentes**-sel elmenthetjük az eddig bevitt megállók listáját egy fájlba. A megálló nevét kell paraméterként megadni hozzá.
Az **utvonal**-lal a leirtak alapján tudunk egy útvonalat tervezni a két megadott megálló között.
A **kilep**-pel kilépünk a programból.











