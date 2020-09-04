# RG4-nuclear-balkan-zombies
Nuclear Balkan Zombies

## Pokretanje
Neophodne biblioteke preuzeti preko `sudo apt-get install binutils-gold freeglut3 freeglut3-dev `

Pozicionirati se u koren direktorijuma i nakon komande `make` pokrenuti dobijeni izvršivi fajl.

U slučaju problema uraditi isto sa `cmake`.

U slučaju daljih problema pokrenuti sa `g++ -std=c++14 main.cpp Player.cpp ControlMatrix.cpp Bomb.cpp Box.cpp Map.cpp  -lGL -lglut -lm -lGLU`.

## Kontrole

### Igrač 1
>* WSAD - kretanje 
>* Q - postavljanje bombe

### Igrač 2
>* IKJL - kretanje 
>* U - postavljanje bombe

## Poznati problemi
Kretanje nije glatko

Igra i ako je predviđena za dva igrača ne prima paralelno inpute za kretanje tako da se istovremeno kretanje dva igrača može dobiti repetativnim kliktanjem tastera za kretanje
