# Checker Tema 1 - 2021
Checker-ul este o aplicație de testare automată a temelor. Este un produs open-source realizat de către și pentru studenții din Facultatea de Automatică și Calculatoare - UPB, și este menit atât să usureze munca asistenților de a corecta teme cât și sa ofere studenților o evaluare cât mai obiectivă.

## Rularea checker-ului
Pentru a verifica functionarea checker-ului va trebui sa descarcati tot depozitul de mai sus, dupa aceasta deschideti un terminal in folderul in care se afla depozitul descarcat si scrieti urmatoarea comanda:
```shell
./checker.sh
````
Am folosit structuri la inceputul programului pentru a declara toate datele de care am avut nevoie pentru a rezolva exercitiile(Ex: Jucator, Echipa etc.). Dupa care, in ordine am realizat urmatoarele: am eliminat spatiile de la sfarsit daca era cazul, am aflat maximul de echipe pt cerinta 2, o functie care gaseste minimul dintr-o lista si il sterge, o functie pt crearea cozii, pentru inserarea in coada, o functie de tip MeciNode(structura definita anterior) pentru a scoate din coada, urmand sa se realizele meciurile. Dupa functia care realizeaza meciurile, am creat o functie pt inserarea in stiva, una care insereaza un nod in lista cu echipele si doua pentru exercitiul cu arbori, una care insereaza in arbore si una care printeaza arborele efectiv. Functiile print_lista si print_campionat care printeaza lista cu echipe si campionatul. In primele 30 de linii din main, am citit argumentele functiei(d.in, c.in, r.out), cerintele si datele. Dupa am alocat memorie pt liste si am verificat cum se executa cerintele pe rand. Am inceput cerinta 3 unde am initializat nodurile cu NULL pt a incepe campionatul si rundele efective, am scos din stiva de invinsi conform cerintei si am printat castigatorii, dupa care am reorganizat campionatul cu noii castigatori. Am inceput cerinta 4 unde am inserat echipele si am printat arborele.