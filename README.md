# Buszjáratok

Programozás alapjai1 Nagyházifeladat

# Specifikáció

A program segítségével buszjáratokat lehet elmenteni és ezek állomásai között útvonalakat tervezni parancssorban.

## Structok

### Ido

Egy idő formátum, ami órát és percet tud tárolni.

- ora: Óra
- perc: Perc

### Megallo

Egy megálló nevét és az innen gyalog elérhető megállókat tárolja. Ezekre lehet ebből a megállóból átszállni.

- nev: Megálló neve
- megallok: Innen elérhető megállók

### Jarat

A fő sturct, ami tartalmazza a járatok adatait.

- nev: Buszjárat neve
- elso_indulas: Napi legelső indulás
- utolso_indulas: Napi legutolsó indulás
- tovabbi_indulasok: Hány percenként indul a járat egy busza a nap folyamán
- megallok: Milyen megállókban áll meg a járat
- idopontok: Melyik megállóba mikor ér el a busz 00:00-s kezdéssel

## A program használata

### Menüvezérlés

A program menüvezérléssel működik.

- A felhasználó a felsorolt menüpontok közül a parancs beírásával tud választani.
- Ezután írhatók az egyes parancsok paraméterei.
- 8 parancs közül lehet választani:
    - segitseg (parancsok felsorolása)
    - mbeolvas (megállók beolvasása)
    - beolvas (járatok beolvasása)
    - kiir (járat kiírása)
    - mentes (járatok mentése)
    - megallo (megálló kiírása)
    - atszallas (hova lehet átszállni)
    - utvonal (útvonaltervezés)
    - kilep (kilépes a programból)

### Parancsok indítása, paraméterezése

Parancsot indítani a konzolon való futtatásával lehet, ezután kell a kötelező, illetve opcionális paramétereket szóközzel elválasztva megadni. Egy paraméteren belül nem lehet szóköz.

### Parancsok felsorolása (segitseg)

Felsorolja a parancsokat.

### Megállók beolvasása (mbeolvas)

Paraméterek:
- fajl : fájl neve

A megadott fájl alapján beolvassa a megállókat, illetve melyik megállóból hova lehet átszállni.
Egy szöveges fájlt kell megadni (.txt kiterjesztés), ami a következőképpen épül fel:

megálló neve, további megállók

```
megallo1,megallo2,megallo3,megallo4
megallo3,megallo1,megallo4,megallo5
```

Ahol minden megálló vesszővel van elválasztva egymástól, így a megállók nevében lehet szóközt használni.

### Járatok beolvasása (beolvas)

Paraméterek:
- fajl : fájl neve
- megallok : a megállók tömb, az adott megálló beolvasására

A megadott fájl alapján beolvassa a megadott járatokat és elmenti további használatra. Ezeket a járatok minden nap fognak közlekedni.
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

### Járatok mentése (mentes)

Paraméterek:
nincs

A program indulásakor a fájljának mappájában megkeresi a **jaratok.txt** szöveges fájlt és ha létezik beolvassa belőle a járatokat, ezek rögtön indítás után elérhetőek lesznek. Ez a mentés nem történik meg a programból való kilépéskor, ezt a felhasználónak kell megtennie a **Járatok mentése** paranccsal. Ez is azonos formátumú a beolvasásnál leírt fájlokkal.

### Járatok kiírása (kiiras)

Paraméterek:
- jaratok : a lista, ahonnan a járatot ki kell keresni
- nev : kiírandó járat neve

Az adott járat adatait írja ki.

### Megállók kiírása (megallo)

Paraméterek:
- megallok : a lista, ahonnan a megállót ki kell keresni
- nev : kiírandó megálló neve

Az adott megálló menetrendjét írja ki.

### Útvonaltervezés (utvonal)

Paraméterek:
- start : induló megálló neve
- cel : célmegálló neve
- fajl : fájl neve

Megadunk a programnak egy kezdő és egy cél megállót nevekkel, opcionális paraméterként pedig egy fájlnevet. Eredményként kapunk egy útvonaltervet átszállásokkal, időpontokkal kiírva a konzolra, illetve ha meg volt adva fájl, ennek a végére kiírja az útvonaltervet, szükség esetén létrehozza a fájlt.

### Kilépés (kilep)

A program kilép.
