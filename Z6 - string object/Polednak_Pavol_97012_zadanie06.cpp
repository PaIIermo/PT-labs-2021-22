/*
Meno a priezvisko: Pavol Polednák

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (dopleny o riesenia).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Do deklaracie funkcie doplnte implicitne hodnoty parametrov.
    Pre parameter 'a' nech je implicitna hodnota 10,
    pre parameter 'b' nech je implicitna hodnota 20.
*/
int sucet(int a=10, int b=20) {
    return a + b;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (3.6 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Trieda 'String' reprezentuje textovy retazec. Doplnte jej implementaciu podla zadania nizsie.

    Trieda implementuje textovy retazec, polom prvkov typu 'char', zakoncenym hodnotou '\0' (ako v jazyku C).
    Adresa tohto pola je ulozena v atribute 'data'.
    Atribut 'data' musi byt sukromny (v casti 'private').
    Ak do implementacie triedy budete pridavat dalsie atributy, tak atribut 'data' musi zostat ako prvy atribut
    (pridanie dalsich atributov nie je nutne).

    Vytvorte verejne konstruktory, destruktory a metody (v casti public). Kazda poduloha je za 0.4 bodu:

    a)  Vytvorte konstruktor bez parametrov.
        Tento konstruktor vytvori objekt reprezentujuci prazdny textovy retazec.

    b)  Vytvorte konstruktor s parametrom typu 'const char *'.
        Tento konstruktor vytvori objekt reprezentujuci textovy retazec, ktory je kopiou vstupneho parametra.
        Ak je vstupny smernik nulovy, tak vytvoreny objekt reprezentuje prazdny textovy retazec.

    c)  Vytvorte kopirovaci konstruktor. Tento konstruktor vytvori hlboku kopiu.

    d)  Vytvorte metodu 'getLength()', ktora vrati pocet znakov v textovom retazci (bez '\0').
        Typ navratovej hodnoty je 'size_t'.
        V deklaracii metody zapiste, ze metoda nemeni stav objektu (pocas vykonavania metody je (*this) konstantne).

    e)  Vytvorte metodu 'char getChar(size_t index) const'.
        Vstupny parameter je indexom znaku v textovom retazci (prvy znak je na pozicii s indexom nula).
        Metoda vratich znak, ktory sa nachadza na mieste urcenom indexom.
        Ak je 'index' mimo rozsahu (alebo textovy retazec neobsahuje ziadne znaky), tak metoda vrati '\0'.

    f)  Vytvorte metodu 'const char * toCString() const'.
        Metoda vrati smernik na C-ckovsku reprezentaciu textoveho retazca.
        Implementacia je jednoducha, metoda vrati adresu v atribute 'data' (kopiu adresy).
        Poznamka: Kedze (konstantny) typ navratvej hodnoty zabranuje zmene obsahu textoveho retazca, nevytvarajte kopiu textu (aj ked existuje moznost pretypovat na nekonstantny typ).

    g)  Vytvorte metodu 'void set(const char *text)',
        ktora nastavi novu hodnotu textoveho retazca podla vstupneho parametra (kopiruje obsah 'text').
        Nezabudnite dealokovat nepotrebnu pamat.

    h)  Vytvorte metodu 'void append(const char *text)', ktora prida na koniec 'text', ktory je vstupnym parametrom.
        Nezabudnite dealokovat nepotrebnu pamat.

    i)  Vytvorte destruktor, ktory v pripade potreby dealokuje pamat.

    Pre alokaciu a dealokaciu poli pouzite new[] a delete[].

    Funkcia 'basicTestString' je urcena na test spravnej deklaracie konstruktorov, metod a destruktora.
    Postupne v nej odkomentuj jednotlive riadky. Tieto musia byt po dokonceni vypracovania kompilovatelne.
    Funkcia testuje spravnost funkcnosti len ciastocne. Vytvorte dalsie testy pre overenenie funkcnosti.
*/

// Prve tri riadky deklaracie triedy musia zostat nezmenene
class String {
private:
    char *data; // obsah textoveho retazca (ak pridate dalsie atributy, tak tento musi zostat prvym atributom)

public:
    String(): data(nullptr){
        std::cout << "default" << endl;
    }

    explicit String(const char *data) {
        std::cout << "param" << endl;
        if (data != nullptr) {
            this->data = new char[strlen(data)+1];
            strcpy(this->data, data);
        }
        else this->data = nullptr;
    }

    String(const String& string) {
        std::cout << "copy" << endl;
        if (string.data != nullptr) {
            this->data = new char[strlen(string.data)+1];
            strcpy(this->data, string.data);
        }
        else this->data = nullptr;
    }

    size_t getLength() const {
        if (this->data == nullptr)
            return 0;
        return strlen(this->data);
    }

    char getChar(size_t index) const {
        if (this->data == nullptr || index >= strlen(this->data) || index < 0) {
            return '\0';
        }
        else return (this->data[index]);
    }

    const char * toCString() const {
        std::cout << "toCString" << endl;
        std::cout << this->data << endl;
        return this->data;
    }

    void set(const char *text) {
        if (this->data != nullptr)
            delete[] this->data;
        this->data = new char[strlen(text)+1];
        strcpy(this->data, text);
    }

    void append(const char *text) {
        int len = strlen(text);
        if (this->data != nullptr) {
            len += strlen(this->data);
        }
        char *c = new char[len];
        if (this->data != nullptr) strcpy(c, this->data);
        if (text != nullptr)
            strcpy(c + (len-strlen(text)) * sizeof(char), text);
        delete[] this->data;
        this->data = new char[len+1];
        strcpy(this->data, c);
    }

    ~String() {
        delete[] this->data;
    }
    // TODO (tu pridajte kod implementujuci triedu)

};

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

void basicTestString() {
    // a)
    //const String str1;

    //b)
    //const String str2("hello world");
    String str3("hello world");
    // String str4("");
    // String str5(nullptr);

    // c)
    // String str6(str2);

    // d)
    // size_t length1 = str1.getLength();
    // assert(length1 == 0);
    // size_t length2 = str2.getLength();
    // assert(length2 == 11);

    // e)
    // char letter1 = str1.getChar(0);
    // assert(letter1 == '\0');
    // char letter2 = str2.getChar(0);
    // assert(letter2 == 'h');
    // char letter3 = str2.getChar(1000);
    // assert(letter3 == '\0');

    // f)
    // const char *cstr1 = str1.toCString();
    // assert(cstr1[0] == '\0');
    // const char *cstr2 = str2.toCString();
    // assert(std::strcmp(cstr2, "hello world") == 0);

    // g)
    str3.set("HELLO WORLD AGAIN");
    assert(std::strcmp(str3.toCString(), "HELLO WORLD AGAIN") == 0);

    // h)
    //str3.append("dalsi text");
    //assert(std::strcmp(str3.toCString(), "HELLO WORLD AGAINdalsi text") == 0);

    // assert(std::strcmp(str6.toCString(), "hello world") == 0);
}

// tu mozete doplnit pomocne testovacie funkcie a datove typy

int main() {

    basicTestString();

    // tu mozete doplnit testovaci kod

    return 0;
}
