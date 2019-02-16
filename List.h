#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nr_ghisee;

typedef struct ListNode
{
    struct ListNode *urmator;
    struct ListNode *anterior;
    int prioritate;
    char *nume;
} ListNode;

typedef struct List
{
    ListNode *primul;
    ListNode *ultimul;
} List;

// Verifica daca o lista este goala
int lista_goala (List *list)
{
    if (list == NULL)
        return 1;
    return 0;
}

// Verifica daca un ghiseu este gol
int ghiseu_gol (List **ghisee, int numar_ghiseu)
{
    if (ghisee[numar_ghiseu]->primul == NULL
        && ghisee[numar_ghiseu]->ultimul == NULL)
        return 1;
    return 0;
}

// Verifica daca vectorul de ghisee este gol
int vector_ghiseu_gol (List **ghisee)
{
    if (ghisee == NULL)
        return 1;
    return 0;
}

// Verifica daca o functie nu se apeleaza cu valori gresite
int date_invalide (int numar_ghiseu)
{
    if (numar_ghiseu >= nr_ghisee)
        return 1;
    return 0;
}

// Dezaloca memoria pentru o lista
void dezaloca_lista (List **list)
{
    if (lista_goala (*list))
        return;

    ListNode *node = (*list)->primul;
    while (node != (*list)->ultimul)
    {
        node = node->urmator;
        free (node->anterior);
    }

    free ((*list)->ultimul);
    free (*list);
}

void inchide_ghisee(List ***ghisee)
{
    if (vector_ghiseu_gol(*ghisee))
        return;

    int i;
    for (i=0; i<nr_ghisee; ++i)
        dezaloca_lista (&((*ghisee)[i]));
    free (*ghisee);
}

void adauga_persoana(List ***ghisee, char *nume, int prioritate,
        int numar_ghiseu)
{
    if (vector_ghiseu_gol (*ghisee))
        return;

    // Creare nod cu datele persoanei
    ListNode *node = (ListNode *) malloc (sizeof (ListNode));
    if (node == NULL)
    {
        inchide_ghisee (ghisee);
        free (node);
        fprintf (stderr, "Error! Not enough memory!\n");
        exit (EXIT_FAILURE);
    }
    node->prioritate = prioritate;
    node->nume = nume;
    node->urmator = NULL;
    node->anterior = NULL;

    // Cazul in care ghiseul nu are persoane
    if ((*ghisee)[numar_ghiseu]->primul == NULL)
    {
        (*ghisee)[numar_ghiseu]->primul = node;
        (*ghisee)[numar_ghiseu]->ultimul = node;
        return;
    }

    // Cazul in care ghiseul are doar 1 persoana
    if ((*ghisee)[numar_ghiseu]->primul == (*ghisee)[numar_ghiseu]->ultimul)
    {
        // Cazul cand persoana va fi prima
        if ((*ghisee)[numar_ghiseu]->primul->prioritate < prioritate)
        {
            node->urmator = (*ghisee)[numar_ghiseu]->primul;
            (*ghisee)[numar_ghiseu]->primul->anterior = node;
            (*ghisee)[numar_ghiseu]->primul = node;
            return;
        }

        // Cazul cand persoana va fi ultima
        if ((*ghisee)[numar_ghiseu]->primul->prioritate > prioritate)
        {
            (*ghisee)[numar_ghiseu]->primul->urmator = node;
            node->anterior = (*ghisee)[numar_ghiseu]->primul;
            (*ghisee)[numar_ghiseu]->ultimul = node;
            return;
        }

        // Cazul cand persoanele au aceeasi prioritate
        if ((*ghisee)[numar_ghiseu]->primul->prioritate == prioritate)
        {
            // Cazul cand persoana va fi prima
            if (strcmp ((*ghisee)[numar_ghiseu]->primul->nume, nume) > 0)
            {
                node->urmator = (*ghisee)[numar_ghiseu]->primul;
                (*ghisee)[numar_ghiseu]->primul->anterior = node;
                (*ghisee)[numar_ghiseu]->primul = node;
                return;
            }
            // Cazul cand persoana va fi ultima
            else
            {
                (*ghisee)[numar_ghiseu]->primul->urmator = node;
                node->anterior = (*ghisee)[numar_ghiseu]->primul;
                (*ghisee)[numar_ghiseu]->ultimul = node;
                return;
            }
        }
    }

    // Cazul in care ghiseul are mai mult de 1 persoana
    // Cazul cand persoana va fi prima
    if ((*ghisee)[numar_ghiseu]->primul->prioritate < prioritate)
    {
        node->urmator = (*ghisee)[numar_ghiseu]->primul;
        (*ghisee)[numar_ghiseu]->primul->anterior = node;
        (*ghisee)[numar_ghiseu]->primul = node;
        return;
    }

    // Cazul cand persoanele au aceeasi prioritate
    if ((*ghisee)[numar_ghiseu]->primul->prioritate == prioritate)
    {    
        // Cazul cand persoana va fi in fata
        if (strcmp ((*ghisee)[numar_ghiseu]->primul->nume, nume) > 0)
        {
            node->urmator = (*ghisee)[numar_ghiseu]->primul;
            (*ghisee)[numar_ghiseu]->primul->anterior = node;
            (*ghisee)[numar_ghiseu]->primul = node;
            return;
        }
        // Cazul cand persoana va fi in spate
        else
        {
            node->urmator = (*ghisee)[numar_ghiseu]->primul->urmator;
            node->anterior = (*ghisee)[numar_ghiseu]->primul;
            (*ghisee)[numar_ghiseu]->primul->urmator = node;
            node->urmator->anterior = node;
            return;
        }
    }

    // Cazul in care persoana nu este nici prima, nici ultima
    // Cautare loc pentru inserare
    ListNode *node_p = (*ghisee)[numar_ghiseu]->primul;
    while (node_p != NULL)
    {
        if (node_p->prioritate == prioritate)
            break;

        // Cazul cand persoana nu va fi ultima
        if (node_p->prioritate < prioritate)
        {
            node->urmator = node_p;
            node->anterior = node_p->anterior;
            node_p->anterior->urmator = node;
            node->urmator->anterior = node;
            return;
        }
        node_p = node_p->urmator;

    }

    // Cazul in care persoana va fi ultima
    if (node_p == NULL)
    {
        (*ghisee)[numar_ghiseu]->ultimul->urmator = node;
        node->anterior = (*ghisee)[numar_ghiseu]->ultimul;
        (*ghisee)[numar_ghiseu]->ultimul = node;
        return;
    }

    // Cazul cand persoana va fi prima cu prioritatea respectiva
    if (node_p->prioritate == prioritate && strcmp (node_p->nume, nume) > 0)
    {
        node->anterior = node_p->anterior;
        node->urmator = node_p;
        node->anterior->urmator = node;
        node_p->anterior = node;
        return;
    }

    while (node_p != NULL && node_p->prioritate == prioritate)
    {
        if (strcmp (node_p->nume, node->nume) < 0)
        {
            // Cazul cand persoana va fi ultima cu prioritatea respectiva
            if (node_p->urmator == NULL)
            {
                node->anterior = node_p;
                node_p->urmator = node;
                node->urmator = NULL;
                (*ghisee)[numar_ghiseu]->ultimul = node;
                return;
            }

            // Cazul cand persoana nu va fi ultima cu prioritatea respectiva
            node->anterior = node_p;
            node->urmator = node_p->urmator;
            node->anterior->urmator = node;
            node->urmator->anterior = node;
            return;
        }
        node_p = node_p->urmator;
    }
}

void deschide_ghisee(List ***ghisee, int N)
{
    if (vector_ghiseu_gol(*ghisee))
    {
        // Alocare memorie vector ghiseu
        *ghisee = (List**) malloc (N*sizeof(List*));
        if (*ghisee == NULL)
        {
            fprintf (stderr, "Error! Not enough memory\n");
            exit (EXIT_FAILURE);
        }

        // Initierea listelor ghiseelor cu liste vide
        for (int i=0; i<N; ++i)
        {    
            (*ghisee)[i] = (List *) malloc (sizeof (List));
            if ((*ghisee)[i] == NULL)
            {
                int j;
                for (j = 0; i<j; ++j)
                    free ((*ghisee)[j]);
                free (*ghisee);
                fprintf (stderr, "Error! Not enough memory\n");
                exit (EXIT_FAILURE);
            }

            (*ghisee)[i]->primul = NULL;
            (*ghisee)[i]->ultimul = NULL;
        }
        // Schimbarea valorii variabilei nr de ghisee deschise
        nr_ghisee = N;
        return;
    }
    else
    {
        // Crearea unei liste cu toate persoanele de la toate ghiseele
        int i,j;
        List *list = (List *) malloc (sizeof(List));
        if (lista_goala(list))
        {
            fprintf (stderr, "Error! Not enough memory!\n");
            inchide_ghisee (ghisee);
            exit (EXIT_FAILURE);
        }

        // Adaugarea tuturor persoanelor in lista
        list->primul = (*ghisee)[0]->primul;
        list->ultimul = (*ghisee)[nr_ghisee-1]->ultimul;
        for (i=1; i<nr_ghisee; ++i)
        {
            (*ghisee)[i-1]->ultimul->urmator = (*ghisee)[i]->primul;
            (*ghisee)[i]->primul->anterior = (*ghisee)[i-1]->ultimul;
        }

        // Aflarea numarului total de persoane
        int nr_persoane = 0;
        ListNode *node = list->primul;
        while (node != NULL)
        {
            ++nr_persoane;
            node = node->urmator;
        }

        // Sortarea elementelor din lista folosind metoda bulelor
        for (i=0; i<nr_persoane; ++i)
        {
            node = list->primul;
            for (j=0; j<(nr_persoane-1-i); ++j)
            {    
                if (node->prioritate < node->urmator->prioritate)
                {
                    int prioritate_aux;
                    char *nume_aux;
                    prioritate_aux = node->prioritate;
                    node->prioritate = node->urmator->prioritate;
                    node->urmator->prioritate = prioritate_aux;

                    nume_aux = node->nume;
                    node->nume = node->urmator->nume;
                    node->urmator->nume = nume_aux;
                }
                if (node->prioritate == node->urmator->prioritate)
                    if (strcmp (node->nume, node->urmator->nume) > 0)
                    {
                        int prioritate_aux;
                        char *nume_aux;
                        prioritate_aux = node->prioritate;
                        node->prioritate = node->urmator->prioritate;
                        node->urmator->prioritate = prioritate_aux;

                        nume_aux = node->nume;
                        node->nume = node->urmator->nume;
                        node->urmator->nume = nume_aux;
                    }
                node = node->urmator;
            }

        }

        // Alocare memorie vector nou de ghisee
        List **ghisee_noi = (List **) malloc (N*sizeof(List*));
        if (ghisee_noi == NULL)
        {
            fprintf (stderr, "Error! Not enough memory");
            inchide_ghisee(ghisee);
            dezaloca_lista (&list);
            exit (EXIT_FAILURE);
        }

        // Initierea listelor ghiseelor cu liste vide
        for (i=0; i<N; ++i)
        {    
            ghisee_noi[i] = (List *) malloc (sizeof (List));
            if (ghisee_noi[i] == NULL)
            {
                fprintf (stderr, "Error! Not enough memory\n");
                for (j = 0; i<j; ++j)
                    free (ghisee_noi[j]);
                free (*ghisee_noi);
                inchide_ghisee(ghisee);
                dezaloca_lista (&list);
                exit (EXIT_FAILURE);
            }

            ghisee_noi[i]->primul = NULL;
            ghisee_noi[i]->ultimul = NULL;
        }

        // Adaugare persoane la ghisee
        int count = 0;
        node = list->primul;
        while (node != NULL)
        {
            if (count == N)
                count = 0;
            adauga_persoana (&ghisee_noi, node->nume, node->prioritate, count);
            ++count;
            node = node->urmator;
        }

        //Eliberare memorie auxiliara
        free (list);
        inchide_ghisee (ghisee);

        // Schimbarea pointerului vectorului de ghisee
        *ghisee = ghisee_noi;

        // Schimbarea valorii variabilei nr de ghisee deschise
        nr_ghisee = N;
        return;
    }
}

void sterge_persoana(List ***ghisee, char *nume, int prioritate,
        int numar_ghiseu)
{
    if (vector_ghiseu_gol (*ghisee))
        return;

    if (date_invalide (numar_ghiseu))
        return;

    if (ghiseu_gol (*ghisee, numar_ghiseu))
        return;

    // Cazul in care la ghiseu este doar acea persoana
    if ((*ghisee)[numar_ghiseu]->primul == (*ghisee)[numar_ghiseu]->ultimul
        && (*ghisee)[numar_ghiseu]->primul->prioritate == prioritate
        && strcmp ((*ghisee)[numar_ghiseu]->primul->nume, nume) == 0)
    {
        free ((*ghisee)[numar_ghiseu]->primul);
        (*ghisee)[numar_ghiseu]->primul = NULL;
        (*ghisee)[numar_ghiseu]->ultimul = NULL;
        return;
    }

    // Cazul in care acea persoana este prima la ghiseu
    if ((*ghisee)[numar_ghiseu]->primul->prioritate == prioritate
        && strcmp ((*ghisee)[numar_ghiseu]->primul->nume, nume) == 0)
    {
        ListNode *node = (*ghisee)[numar_ghiseu]->primul->urmator;
        free ((*ghisee)[numar_ghiseu]->primul);
        node->anterior = NULL;
        (*ghisee)[numar_ghiseu]->primul = node;
        return;
    }

    // Cazul in care acea persoana este ultima la ghiseu
    if ((*ghisee)[numar_ghiseu]->ultimul->prioritate == prioritate
        && strcmp ((*ghisee)[numar_ghiseu]->ultimul->nume, nume) == 0)
    {
        ListNode *node = (*ghisee)[numar_ghiseu]->ultimul->anterior;
        free ((*ghisee)[numar_ghiseu]->ultimul);
        node->urmator = NULL;
        (*ghisee)[numar_ghiseu]->ultimul = node;
        return;
    }

    // Cauta persoana in lista
    int found = 0;
    ListNode *node = (*ghisee)[numar_ghiseu]->primul;
    while (node != NULL && node->prioritate >= prioritate)
    {
        if (node->prioritate == prioritate &&
            strcmp (node->nume, nume) == 0)
        {
            found = 1;
            break;
        }
        node = node->urmator;
    }
    
    if (found)
    {
        node->anterior->urmator = node->urmator;
        node->urmator->anterior = node->anterior;
        free (node);
        return;
    }
}

void sterge_primii_oameni(List ***ghisee)
{
    if (vector_ghiseu_gol (*ghisee))
        return;

    int i;
    for (i=0; i<nr_ghisee; ++i)
    {
        // Cazul cand ghiseul este gol
        if(ghiseu_gol (*ghisee,i))
            continue;

        // Cazul cand este doar 1 persoana la ghiseu
        if ((*ghisee)[i]->primul->urmator == NULL)
        {
            free ((*ghisee)[i]->primul);
            (*ghisee)[i]->primul = NULL;
            (*ghisee)[i]->ultimul = NULL;
            continue;
        }

        // Restul cazurilor
        ListNode *node = (*ghisee)[i]->primul->urmator;
        free ((*ghisee)[i]->primul);
        node->anterior = NULL;
        (*ghisee)[i]->primul = node;
    }
}

int calculeaza_numar_oameni_ghiseu(List **ghisee, int numar_ghiseu)
{
    if (vector_ghiseu_gol (ghisee))
        return 0;

    if (date_invalide (numar_ghiseu))
        return 0;

    if (ghiseu_gol (ghisee, numar_ghiseu))
        return 0;

    ListNode *node = ghisee[numar_ghiseu]->primul;
    int numar_oameni = 0;
    while (node != NULL)
    {
        node = node->urmator;
        ++numar_oameni;
    }
    return numar_oameni;
}

int calculeaza_numar_total_oameni(List **ghisee)
{
    if (vector_ghiseu_gol (ghisee))
        return 0;

    int i, numar_total = 0;

    for (i=0; i<nr_ghisee; ++i)
    {
        if (ghiseu_gol(ghisee,i) == 0)
        {
            ListNode *node = ghisee[i]->primul;
            while (node != NULL)
            {
                ++numar_total;
                node = node->urmator;
            }

        }
    }
    return numar_total;
}

int gaseste_pozitie_persoana (List **ghisee, char *nume, int prioritate,
        int numar_ghiseu)
{
    if (vector_ghiseu_gol (ghisee))
        return -1;

    if (date_invalide (numar_ghiseu))
        return -1;

    if (ghiseu_gol (ghisee, numar_ghiseu))
        return -1;

    // Cauta prioritatea persoanei
    int pozitie = 0;
    ListNode *node = ghisee[numar_ghiseu]->primul;
    while (node != NULL && node->prioritate > prioritate)
    {
        ++pozitie;
        node = node->urmator;
    }

    if (node == NULL || node->prioritate != prioritate)
        return -1;

    // Cauta numele persoanei
    while (node != NULL && node->prioritate == prioritate
        && strcmp (nume, node->nume) != 0)
    {
        ++pozitie;
        node = node->urmator;
    }

    if (node != NULL)
        if (node->prioritate == prioritate && strcmp (nume, node->nume) == 0)
            return pozitie;

    return -1;
}

char* gaseste_persoana_din_fata(List **ghisee, char *nume, int prioritate,
        int numar_ghiseu)
{
    if (vector_ghiseu_gol (ghisee))
        return "Nu exista.";

    if (date_invalide (numar_ghiseu))
        return "Nu exista";

    if (ghiseu_gol (ghisee, numar_ghiseu))
        return "Nu exista.";

    // Cauta prioritate persoanei
    ListNode *node = ghisee[numar_ghiseu]->primul;
    while (node != NULL && node->prioritate > prioritate)
        node = node->urmator;

    if (node == NULL || node->prioritate != prioritate)
        return "Nu exista.";

    // Cauta numele persoanei
    while (node != NULL && node->prioritate == prioritate 
        && strcmp (nume, node->nume) != 0)
        node = node->urmator;

    if (node->anterior != NULL)
        if (node->prioritate == prioritate && strcmp (nume, node->nume) == 0)
            return node->anterior->nume;

    return "Nu exista.";
}

void afiseaza_rand_ghiseu(FILE *f, List **ghisee, int numar_ghiseu)
{
    if (vector_ghiseu_gol (ghisee))
        return;

    if (date_invalide (numar_ghiseu))
        return;

    if (ghiseu_gol(ghisee, numar_ghiseu))
    {
        fprintf (f,"Ghiseul %d nu are nicio persoana in asteptare.\n",
            numar_ghiseu);
        return;
    }

    ListNode *node = ghisee[numar_ghiseu]->primul;
    while (node != NULL)
    {
        fprintf (f,"%s-%d;", node->nume, node->prioritate);
        node = node->urmator;
    }
    fprintf (f, "\n");
}

#endif