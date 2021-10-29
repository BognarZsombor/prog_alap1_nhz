# Buszjáratok

Programozás alapjai1 Nagyházifeladat

# Specifikáció

A program segítségével buszjáratokat tudunk elmenteni és ezek állomásai között útvonalakat tervezni parancssorban.

## A program használata

### Menüvezérlés

A program parancssoros vezérléssel fog működik.

- A menü a parancssoron belül jelenik meg.
- A felhasználó a felsorolt menüpontok közül a parancs beírásával tud választani.
- Ezután írhatók az egyes parancsok paraméterei.
- 6 parancs közül lehet választani:
    - beolvas (járatok beolvasása)
    - kiir (járatok kiírása)
    - mentes (járatok mentése)
    - megallo (megállók kiírása)
    - utvonal (útvonaltervezés)
    - kilep (kilépes a programból)

### Parancsok indítása, paraméterezése

Parancsot indítani a konzolon való futtatásával lehet, ezután kell a kötelező, illetve opcionális paramétereket szóközzel elválasztva megadni. Egy paraméteren belül nem lehet szóköz.

### Járat működése

Egy járathoz tartozik egy busz, az első indulás időpontja, az utolsó indulás időpontja, a további idulások ideje (a következő azonos járatok hány perc múlva indulnak az első indulási időpont után), a járat megállóinak listája és a megállókból való indulás időpontja. A megállók, illetve megállókból való indulások listája az oda és visszautat is tartalmaznia kell, tehát a második megállónak kell lennie az utolsónak is.

### Járatok beolvasása (beolvas)

Paraméterek:
- fajl_nev : fájl neve

A megadott fájl alapján a program beolvassa a megadott járatokat és elmenti további használatra. Ezeket a járatok minden nap fognak közlekedni.
A felhasználónak egy szöveges fájlba (.txt kiterjesztés) kell összegyűjtenie a járatok adatait. Egy rész a következőképpen áll össze:

járat száma, első indulás, utolsó indulás, további indulások
megállók
utazási időpontok (az egyes megállókból való indulás időpontja 00:00-val kedződően)

**Példa.txt:**

```
b72 08:25 22:10 00:10
megallo1,megallo 2,megallo3,...
00:00 00:38 1:03 ...

a36 09:45 20:50 00:25
megallo2,megallo3,megallo5,...
00:00 00:28 1:00 ...
```

Ahol minden fő adat szóközzel van elválasztva. (járat száma, első indulás, utolsó indulás, további indulások) Ezen belül:

- A járat száma bármilyen számokból vagy betűkből álló adat lehet. (b72)
- Az első indulás időpontja egy 0-24 óra közötti időpont, kettősponttal elválasztva. (HH:MM formátumban)
- Az utolsó indulás időpontja egy 0-24 óra közötti időpont, kettősponttal elválasztva. (HH:MM formátumban)
- A további indulások ideje egy 0-24 óra közötti időpont, kettősponttal elválasztva. (HH:MM formátumban)

Következő sor (megállók):

- A megállók egy felsorolás a járat megállóiról vesszővel elválasztva, így a megállók nevében a szóköz megengedett. (m1,m2,m3)

Következő sor (utazási időpontok):

- Az időpontok, ahogy az egyes megállókból elindul az aktuális járat. 00:00-val kezdődik, ami a garázsból, illetve végállomásról való indulást jelenti.

<div style="page-break-after: always;"></div>

### Járatok kiírása (kiiras)

Paraméterek:
- fajl_nev : fájl neve

Az eddig beolvasott és elmentett buszjáratokat kiírja a konzolra és paraméter megadásával egy fájlba, a beolvasással azonos formátumban. A programnak megadott fálj, ha nem található, létrehozásra kerül. Az adatok soronként a beolvasásnál leírt fájlal megegyező formátumú. Ezeket a fáljokat később lehet használni járatok beolvasására.

### Járatok mentése (mentes)

Nincs paramétere.
A program indulásakor a fájljának mappájában megkeresi a **jaratok.txt** szöveges fájlt és ha létezik beolvassa belőle a járatokat, ezek rögtön indítás után elérhetőek lesznek. Ez a mentés nem történik meg a programból való kilépéskor, ezt a felhasználónak kell megtennie a **Járatok mentése** paranccsal. Ez is azonos formátumú a beolvasásnál leírt fájlokkal.

### Megállók kiírása (megallo)

Paraméterek:
- nev : melyik megálló menetrendjét kell kiírni

Egy megálló menetrendjét írja ki az adott napon.

### Útvonaltervezés (utvonal)

Paraméterek:
- start : induló megálló neve
- cel : célmegálló neve
- fajl_nev : fájl neve

Megadunk a programnak egy kezdő és egy cél megállót nevekkel, opcionális paraméterként pedig egy fájlnevet. Eredményként kapunk egy útvonaltervet átszállásokkal, időpontokkal kiírva a konzolra, illetve ha meg volt adva fájl, ennek a végére kiírja az útvonaltervet, szükség esetén létrehozza a fájlt.

### Kilépés (kilep)

A program kilép.
