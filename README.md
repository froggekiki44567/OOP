# OOP

## FAILŲ TYRIMŲ REZULTATAI SU 03 vėliavėlę:

|        FAILAS          |              VEKTOR             |
|------------------------|---------------------------------|
| Gstudentai1000.txt     |       ![alt text](image.png)    |    
| Gstudentai10000.txt    |       ![alt text](image-2.png)  |  
| Gstudentai100000.txt   |       ![alt text](image-1.png)  |   
| Gstudentai1000000.txt  |       ![alt text](image-3.png)  |   
| Gstudentai10000000.txt |       ![alt text](image-4.png)  |    


|        FAILAS          |               LIST              |
|------------------------|---------------------------------|
| Gstudentai1000.txt     |     ![alt text](image-5.png)    |   
| Gstudentai10000.txt    |     ![alt text](image-6.png)    |   
| Gstudentai100000.txt   |     ![alt text](image-7.png)    |   
| Gstudentai1000000.txt  |     ![alt text](image-8.png)    |   
| Gstudentai10000000.txt |     ![alt text](image-9.png)    |

|        FAILAS          |              DEQUE              |
|------------------------|---------------------------------|
| Gstudentai1000.txt     |    ![alt text](image-10.png)    |   
| Gstudentai10000.txt    |    ![alt text](image-11.png)    |   
| Gstudentai100000.txt   |    ![alt text](image-12.png)    |   
| Gstudentai1000000.txt  |    ![alt text](image-13.png)    |   
| Gstudentai10000000.txt |    ![alt text](image-14.png)    |


|        FAILAS          |       OPTIMIZUOTAS VECTOR       |
|------------------------|---------------------------------|
| Gstudentai1000.txt     |   ![alt text](image-15.png)     |   
| Gstudentai10000.txt    |   ![alt text](image-16.png)     |   
| Gstudentai100000.txt   |   ![alt text](image-17.png)     |   
| Gstudentai1000000.txt  |   ![alt text](image-18.png)     |   
| Gstudentai10000000.txt |   ![alt text](image-19.png)     |


## Testavimo aplinka

- **Procesorius**: Apple M3
- **RAM**: 8GB
- **SSD**: 256GB

## Naudojimosi instrukcija

1. **Failų generavimas**:
   - Paleiskite programą ir pasirinkite failų generavimo funkciją.
   - Po failų generavimo reikės pasirinkti testai su failais.

2. **Failų darbai**:
   - Pasirinkite norimą failą iš pateikto sąrašo.
   - Pasirinkite norimą rušiavimą
   - Pasirinkite  norimą skirstymo strategiją:
   - Programa išrūšiuos studentus į „vargšiukus“ ir „kietiakus“ bei išsaugos juos atskiruose failuose.

3. **Rezultatų analizė**:
   - Peržiūrėkite sugeneruotus failus ir programos išvestį, kurioje pateikiamas veikimo laikas.

## Įdiegimo instrukcija

1. **Reikalavimai**:
   - GCC arba kitas C++ kompiliatorius su `C++17` ar naujesne versija.
   - `make` įrankis (Unix sistemose įdiegtas pagal nutylėjimą).

2. **Įdiegimas**:
   - Atsisiųskite projektą:
     git clone <https://github.com/frogg-kek/OOP>

   - Paleiskite `make` komandą:
      make

   - Sukurtas vykdomasis failas bus pavadintas `kursiokai`.

3. **Paleidimas**:
   - Paleiskite programą:
     ./kursiokai

4. **Valymas**:
     make clean