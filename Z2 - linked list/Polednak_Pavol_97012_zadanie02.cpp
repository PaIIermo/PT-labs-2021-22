/*
Meno a priezvisko:
POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_zadanie02.cpp (pouzite vase udaje bez diakritiky).
*/

#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node *next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node *first; // adresa prveho uzla zoznamu
};

// Pomocna struktura pre ulohu 2
struct ListData {
    int *data; // pole hodnot uzlov
    size_t len; // dlzka pola 'data'
};

Node *createNode(const int value){
    return new Node{value, nullptr};
}
//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zretazeneho zoznamu 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr') a moze
           mat lubovolny pocet uzlov (0 a viac).

    PARAMETRE:
        [in/out] list   - adresa zretazeneho zoznamu, do ktoreho ideme pridavat uzol
        [in] val        - hodnota uzla, ktory sa ma pridat na koniec zoznamu 'list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        {prazdny zoznam},5 ---> {5}
        {1},1 ---> {1,1}
        {8,2,6,6},14 ---> {8,2,6,6,14}
        {6,100,33},-85 ---> {6,100,33,-85}
        {1,2,3,4,5},3 ---> {1,2,3,4,5,3}
*/

void appendNode(List *list, const int val) {
    Node *new_node = createNode(val);
    if (list->first == nullptr) {
        list->first = new_node;
    }
    else {
        Node *tmp = list->first;
        while(tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
}


//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam, ktory bude skonstruovany pomocou udajov vo vstupnej
    strukture 'list_data'. Struktura 'list_data' obsahuje polozku 'data', ktora reprezentuje pole
    hodnot pre jednotlive uzly zoznamu. Struktura 'list_data' taktiez obsahuje polozku 'len', ktora
    hovori aku ma dlzku pole 'data'. Vytvoreny zoznam musi obsahovat uzly, ktore zodpovedaju
    svojimi hodnotami a poradim prvkom ulozenym v poli 'data' (dlzka zoznamu bude 'len').
    Funkcia nakoniec vrati adresu takto vytvoreneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list_data' vzdy existuje (t.j. 'list_data' je rozny od 'nullptr').
        2) Pre polozku 'len' plati, ze 'len' >= 0 a nikdy nebude mat vacsiu hodnotu ako je
           realny pocet prvkov v poli 'data'.
        3) Ak je polozka 'len' rovna 0, vtedy sa vytvori a vrati prazdny zretazeny zoznam
           (t.j. platny zoznam, ktory ma 0 uzlov).

    PARAMETRE:
        [in] list_data - struktura, pomocou ktorej sa vytvori zoznam

    NAVRATOVA HODNOTA:
        Adresa zretazeneho zoznamu, ktory bol vytvoreny pomocou struktury 'list_data'.
        Vid pokyny vyssie.

    PRIKLADY:
        polozka 'data' = [1,2,3]
        polozka 'len' = 0
        vystupny zoznam bude mat 0 uzlov, t.j. {}

        polozka 'data' = [1,2,3]
        polozka 'len' = 2
        vystupny zoznam bude {1,2}

        polozka 'data' = [1,2,3]
        polozka 'len' = 3
        vystupny zoznam bude {1,2,3}

        polozka 'data' = [-9,412,64,72,100,100,6]
        polozka 'len' = 4
        vystupny zoznam bude {-9,412,64,72}

*/

List *createList(const ListData *list_data) {
    List *list = new List;
    list->first = nullptr;
    for (size_t i=0; i<list_data->len; i++) {
        appendNode(list,*(list_data->data+i));
    }
    return list; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' do vzostupne zotriedeneho zoznamu 'sorted_list'.
    Pridanie musi prebehnut takym sposobom, aby bol zoznam 'sorted_list' po pridani noveho uzla
    stale vzostupne zotriedeny.

    POZNAMKA: Na poradi duplikatov v zozname 'sorted_list' nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'sorted_list' vzdy existuje (t.j. 'sorted_list' je rozny od 'nullptr').
        2) Vstupny zoznam 'sorted_list' moze mat lubovolny pocet uzlov (0 a viac).
        3) Vstupny zoznam 'sorted_list' je vzostupne zotriedeny.

    PARAMETRE:
        [in/out] sorted_list    - adresa vstupneho zretazeneho zoznamu, ktory je zotriedeny
                                  vzostupne (z angl. ascending)
        [in] val                - hodnota uzla, ktory sa ma pridat do zoznamu 'sorted_list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        {},0 ---> {0}
        {},156 ---> {156}
        {8},4 ---> {4,8}
        {7},10 ---> {7,10}
        {55},55 ---> {55,55} ... poznamka: na poradi duplikatov nezalezi
        {1,8,236,888},70 ---> {1,8,70,236,888}
        {6,6,14,82,82,100},6 ---> {6,6,6,14,82,82,100}

*/

void insertNode(List *sorted_list, const int val) {
    Node *tmp = sorted_list->first;
    Node *nn = createNode(val);
    if (tmp == nullptr) {
        sorted_list->first = nn;
        return;
    }
    if (tmp->data > val) {
        nn->next = sorted_list->first;
        sorted_list->first = nn;
    }
    else {
        while (tmp->next != nullptr && tmp->next->data < val) {
            tmp = tmp->next;
        }
        if (tmp->next != nullptr) {
            nn->next = tmp->next;
        }
        tmp->next = nn;  //Good now I think
    }
}


//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zoznam spojenim zoznamov 'list1' a 'list2'. Funkcia vrati adresu
    novo vytvoreneho zoznamu. V spojenom zozname idu najprv uzly zoznamu 'list1' (v nezmenenom poradi)
    a potom nasleduju uzly zoznamu 'list2' (v nezmenenom poradi). Pri vytvarani noveho zoznamu mozete
    pouzit hlboku alebo plytku kopiu existujucich uzlov (obe riesenia budu akceptovane).

    POZNAMKA:
        Prazdny zoznam je taky zoznam, ktory je platny, ale obsahuje 0 uzlov
        (t.j. polozka 'first' je nastavena na 'nullptr').

    VSTUPNE PODMIENKY:
        1) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).

    PARAMETRE:
        [in/out] list1 - adresa prveho zoznamu
        [in/out] list2 - adresa druheho zoznamu

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol spojenim zoznamov 'list1' a 'list2'.

    PRIKLADY:
        {} + {} ---> {}
        {5,9} + {} ---> {5,9}
        {} + {2,2,2} ---> {2,2,2}
        {1} + {2} ---> {1,2}
        {7} + {3,9,16} ---> {7,3,9,16}
        {50,-47,23,1} + {0,0,9,-8} ---> {50,-47,23,1,0,0,9,-8}
*/

void appendList(List *list, Node *n) {
    if (list->first == nullptr) {
        list->first = n;
    } else {
        Node *tmp = list->first;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = n;
    }
}

List *joinLists(List *list1, List *list2) {
    List *l = new List;
    l->first = nullptr;
    if (list1->first != nullptr){
        appendList(l, list1->first);
    }
    if (list2->first != nullptr){
        appendList(l, list2->first);
    }
    return l; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani posledny uzol zo zoznamu 'list'. Ak je zoznam 'list' prazdny, funkcia nic
    nevykona. Pamat uzla, ktory funkcia vymaze musi byt korektne dealokovana.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in/out] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        {} ---> {}
        {1} ---> {}
        {1,2} ---> {1}
        {1,2,3} ---> {1,2}
*/

void removeLastNode(List *list) {
    Node *tmp;
    if (list->first != nullptr) {
        if (list->first->next == nullptr) {
            delete(list->first);
            list->first = nullptr;
        }
        else {
            tmp = list->first;
            while (tmp->next->next != nullptr) {
                tmp = tmp->next;
            }
            delete(tmp->next);
            tmp->next = nullptr;
        }
    }
}


//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci je vstupny zoznam 'list' palindrom. Prazdny zoznam budeme povazovat za
    palindrom.

    Poznamka: Palindrom predstavuje taku postupnost hodnot, ktora sa cita rovnako v oboch smeroch.
    URL: https://sk.wikipedia.org/wiki/Palindr%C3%B3m
    Priklad palindromu: {1212121} alebo {4953594}

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci vstupny zoznam je/nie je palindrom.

    PRIKLADY:
        {} ---> true
        {1} ---> true
        {2,2,2,2} ---> true
        {1,2,3,4,5} ---> false
        {1,2,2,1} ---> true
        {8,4,8,4,8} ---> true
        {9,842,613,2,613,842,9} ---> true
        {7,9,1,2} ---> false
        {0,0,0,7,0,0} ---> false

*/

bool isPalindrome(const List *list) {
    Node *tmp;
    int c=0;
    if (list->first != nullptr) {
        tmp = list->first;  c++;
        while (tmp->next != nullptr) {
            tmp = tmp->next; c++;
        }
    }
    else {return true;}
    int field[c]; c=0;
    tmp=list->first;
    while (tmp->next != nullptr) {
        field[c] = tmp->data; c++;
        tmp = tmp->next;
    } field[c] = tmp->data;
    int i = 0; int j = c;

    while (i!=(c/2+1)) {
        if(field[i] != field[j]) {
            return false;
        }
        i++; j--;
    }
    return true; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati sucet hodnot prvych 'n' uzlov v zozname 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).
        3) Parameter 'n' nebude zaporny a nebude mat nikdy vyssiu hodnotu ako je realny pocet
           uzlov v zozname.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] n - pocet uzlov od zaciatku zoznamu 'list', ktorych sucet sa vrati

    NAVRATOVA HODNOTA:
        Sucet hodnot prvych 'n' uzlov zoznamu 'list'. Ak 'n'=0, vtedy funkcia vrati hodnotu 0.

    PRIKLADY:
        {},0 ---> 0
        {1,2,3},0 ---> 0
        {6},1 ---> 6
        {5,6,7},2 ---> 11
        {4,4,4,4,4,4},6 ---> 24
        {-8,41,-314,21},3 ---> -281

*/

int sumNodes(const List *list, const int n) {
    int sum = 0;
    int i = 0;
    Node *tmp;
    if (n>0 && list->first != nullptr) {
        tmp = list->first;
        sum+=tmp->data;
        i++;
        while (tmp->next != nullptr && i<n) {
            tmp=tmp->next;
            sum+=tmp->data;
            i++;
        }
    }
    return sum; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci zoznam 'list1' obsahuje vsetky hodnoty uzlov zoznamu 'list2'.
    Na poradi nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list1' a 'list2' vzdy existuju (t.j. su rozne od 'nullptr').
        2) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).
        3) Zoznam 'list2' nebude obsahovat duplicitne uzly.

    PARAMETRE:
        [in] list1 - prvy zoznam
        [in] list2 - druhy zoznam

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci zoznam 'list1' obsahuje/neobsahuje
        vsetky hodnoty uzlov zoznamu 'list2'.

    PRIKLADY:
        {},{} ---> true
        {},{1,2,3} ---> false
        {1,2,3},{} ---> true
        {5,6,7},{5,6,8} ---> false
        {8,4,3},{3,8,4} ---> true
        {7,6,1,9,8},{1,6,8} ---> true
        {3,3,3,3,3},{2,3} ---> false
        {8,6,1,2,5,0,7,7},{7} ---> true
        {9,5,10},{41,10,5} ---> false

*/

bool contains(const List *list1, const List *list2) {
    Node *tmp;
    int c=0;
    if (list2->first != nullptr) {
        tmp = list2->first;  c++;
        while (tmp->next != nullptr) {
            tmp = tmp->next; c++;
        }
    } else{return true;}
    int field[c]; c=0;
    tmp=list2->first;
    while (tmp->next != nullptr) {
        field[c] = tmp->data;
        tmp = tmp->next; c++;
    } field[c] = tmp->data;
    if (list1->first == nullptr)
        return false;
    for(int i =0; i<=c; i++){
        tmp = list1->first;
        while (tmp->data != field[i] && tmp->next != nullptr) {
            tmp = tmp->next;
        }
        if (tmp->data != field[i])
            return false;
    }

    return true; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati HLBOKU kopiu zoznamu 'list'. Vo vytvorenej kopii musia byt zachovane
    hodnoty a poradie uzlov z povodneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa zoznamu, ktoreho hlboku kopiu treba vytvorit

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol ako hlboka kopia vstupneho zoznamu 'list'. Kopiou
        prazdneho zoznamu je prazdny zoznam.

    PRIKLADY:
        Vstup = {}
        Vystup = {}

        Vstup = {1,2,3}
        Vystup = {1,2,3}
        Poznamka: adresy uzlov na rovnakych poziciach v oboch zoznamoch sa musia lisit
        (pretoze je to hlboka kopia)
*/

List* deepCopyList(const List *list) {
    Node *tmp1=list->first;
    List *l = new List;
    l->first = nullptr;
    if (tmp1 != nullptr) {
        while (tmp1->next != nullptr){
            appendNode(l, tmp1->data);
            tmp1=tmp1->next;
        } appendNode(l, tmp1->data);
    }
    return l; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}



//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde posledny vyskyt uzla s hodnotou 'val' v zozname 'list' a vrati jeho adresu.
    Ak sa v zozname 'list' takyto uzol nenachadza, funkcia vrati 'nullptr'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hladana hodnota uzla

    NAVRATOVA HODNOTA:
        Adresa posledneho vyskytu uzla s hodnotou 'val' v zozname 'list'.

    PRIKLADY (treba otestovat pomocou debuggera):
        {},2 ---> nullptr
        {5,4,3,2},1 ---> nullptr
        {-5,4,-9,66},4 ---> adresa 2. uzla
        {1,1,1,5,6,41},1 ---> adresa 3. uzla
        {8,6,7,3,2,6},6 ---> adresa 6. uzla
*/

Node *findLastNodeOccurrence(const List *list, const int val) {
    Node *tmp = list->first;
    Node *ret = nullptr;
    if (tmp != nullptr){
        if (tmp->data == val)
            ret = tmp;
        while (tmp->next!= nullptr) {
            tmp = tmp->next;
            if (tmp->data == val)
                ret = tmp;
        }
    }
    return ret; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    /*
    int c1[1] = {4};
    auto *d1 = new ListData;
    d1->data = c1;
    d1->len = 0;
    List *l1 = createList(d1);
    insertNode(l1,10);
     std::cout << findLastNodeOccurrence(l1,6) <<endl;
    */

    /*
    int z = sumNodes(l1,0);
    std::cout << z << endl;*/
    /*
     *
    int c1[3] = {5,9,5};
    int c2[4] = {5,9,3,4};
    auto *d1 = new ListData;
    d1->data = c1;
    d1->len = 3;
    auto *d2 = new ListData;
    d2->data = c2;
    d2->len = 4;
    List *l1 = createList(d1);
    List *l2 = createList(d2);
    List *l3 = joinLists(l1,l2);
    removeLastNode(l3);
    if (isPalindrome(l3))
        std::cout << "Hello baron"<<endl;
    std::cout << sumNodes(l3, 6) <<endl;
    if (contains(l1,l2))
        std::cout << "Hello baron"<<endl;
    List *l4 = deepCopyList(l3);
    List *l5 = new List;
    l5->first = nullptr;
    List *l6 = deepCopyList(l5);

     */

    /*Node* new_node = createNode(56);
    std::cout << new_node->data << endl;*/
    /*
    List *list = new List;
    list->first = nullptr;
    appendNode(list, 52);
    if (list->first != nullptr) {
        std::cout << "zbehlo" << endl;
    }*/

    return 0;
}

