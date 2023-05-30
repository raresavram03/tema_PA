#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE_LENGTH 100
#define PRINTARE 0

struct Jucator {
    char nume[MAX_LINE_LENGTH];
    char prenume[MAX_LINE_LENGTH];
    int punctaj;
};

struct Echipa {
    char nume[MAX_LINE_LENGTH];
    int numar_jucatori;
    struct Jucator *jucatori;
    float punctaj;
};

struct Node {
    struct Echipa echipa;
    struct Node *next;
};

// Cerinta 3
// struct MeciStruct {
//     struct Echipa *echipa_acasa;
//     struct Echipa *echipa_deplasare;
// };

// typedef struct MeciStruct Meci;

// struct MeciNodeStruct {
//     Meci meci;
//     struct Node *next;
// };

// typedef struct MeciNodeStruct MeciNode;

typedef struct MeciNode {
    struct Echipa echipa_acasa;
    struct Echipa echipa_deplasare;
    struct MeciNode* next;
} MeciNode;

struct Q {
    MeciNode *front, *rear;
};

typedef struct Q Queue;

// BST
typedef struct TreeNode {
    struct Echipa echipa;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void remove_trailing_spaces(char *str) {
    char *end = strrchr(str, '\0'); // get pointer to end of string
    while (end != str && isspace(end[-1])) {
        end--; // move pointer back while it points to a space
    }
    *end = '\0'; // terminate string at the last non-space character
}

/*
 *  Calculeaza maximul de echipe pentru cerinta 2
 *  Max echipe trebuie sa fie putere a lui 2 
 *    si <= max_echipe din fisier.
 */
int max_echipe(int numar_echipe) {
    int max_echipe = 1;
    while (max_echipe <= numar_echipe/2) {
        max_echipe *= 2;
    }
    return max_echipe;
}


/*
 *  Gaseste minimul dintr-o lista si il sterge
 */
void sterge_min(struct Node **head_ptr) {
    if (*head_ptr == NULL) {
        return;
    }
    
    struct Node *current = *head_ptr;
    struct Node *prev = NULL;
    struct Node *min_node = current;
    struct Node *prev_min_node = NULL;
    float min_val = current->echipa.punctaj;
    int found_min = 0;

    // find the minimum value and its node
    while (current != NULL) {
        if (current->echipa.punctaj < min_val) {
            min_node = current;
            prev_min_node = prev;
            min_val = current->echipa.punctaj;
            found_min = 0; // reset the flag when we find a smaller value
            if (PRINTARE == 1) {         
                printf("Gasit minim (%f) in echipa %s\n\r", current->echipa.punctaj, current->echipa.nume);
                printf("Urmatoarea echipa este echipa %s\n\r", current->next->echipa.nume);
            }
        }
        if (current->echipa.punctaj == min_val) {
            found_min++; // increment the flag for each node with the minimum value
        }
        prev = current;
        current = current->next;
    }
    
    // remove the first node with the minimum value
    if (min_node == *head_ptr) {
        if (PRINTARE == 1) {
            printf("Stergem %s\n\r", min_node->echipa.nume);    
        }
        *head_ptr = (*head_ptr)->next;
    } else {
        if (PRINTARE == 1) {
            printf("Stergem %s\n\r", min_node->echipa.nume);
            printf("Prev %s\n\r", prev_min_node->echipa.nume);
            printf("Next %s\n\r", min_node->next->echipa.nume);
        }

        prev_min_node->next = min_node->next;
    }
    
    free(min_node);
}


Queue* createQueue() {
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) return NULL;
    q->front=q->rear=NULL;
    return q;
}

/*
 * Inserare in queue
 */
void enQueue(Queue *q, struct Echipa echipaAcasa, struct Echipa echipaDeplasare) {
    if (PRINTARE == 1) {
        printf("CAMP: Creare meci acasa %s si deplasare %s\n", echipaAcasa.nume, echipaDeplasare.nume);
    }
    MeciNode* newNode = (MeciNode *)malloc(sizeof(MeciNode));
    newNode->echipa_acasa = echipaAcasa;
    newNode->echipa_deplasare = echipaDeplasare;
    newNode->next = NULL;

    if (q->front == NULL) {
        // If the queue is empty, set both the front and rear pointers to the new node
        q->front = newNode;
        q->rear = newNode;
    } else {
        // Otherwise, set the next pointer of the current rear node to the new node
        // and update the rear pointer to point to the new node
        q->rear->next = newNode;
        q->rear = newNode;

    }

    if (PRINTARE == 1) {
        printf("CAMP FRONT: acasa %s si deplasare %s\n", q->front->echipa_acasa.nume, q->front->echipa_deplasare.nume);
        printf("CAMP REAR: acasa %s si deplasare %s\n", q->rear->echipa_acasa.nume, q->rear->echipa_deplasare.nume);
    }
}

MeciNode* deQueue(Queue *q) {
    MeciNode* aux;
    if (q->front == NULL) {
        return NULL;
    }

    aux = q->front;
    if (PRINTARE == 1) {
        printf("Meci: %s vs. %s\n", aux->echipa_acasa.nume, aux->echipa_deplasare.nume);
    }
    q->front = (q->front)->next;

    return aux;
}

/*
 *  Joaca meci - 1 daca castiga acasa 0 daca deplasare
 */
int joacaMeci(struct Echipa echipaAcasa, struct Echipa echipaDeplasare) {
    if (echipaAcasa.punctaj > echipaDeplasare.punctaj) {
        return 1;
    } else {
        return 0;
    }
}

/*
 *  Inserare in stiva
 */
void push(struct Node** top, struct Echipa echipa) {
    struct Node* newNode=(struct Node *)malloc(sizeof(struct Node));
    newNode->echipa = echipa;
    newNode->next = *top;
    *top = newNode;
}

struct Node*  pop(struct Node**top) {
    struct Node* temp = (*top);
    *top =(*top)->next;
    return temp;
}

/*
 *  BST
 */ 

void insertNode(struct Node** head, struct Echipa echipa) {
    // Allocate memory for the new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Set the fields of the new node
    newNode->echipa = echipa;
    newNode->next = NULL;

    // If the list is empty, make the new node the head of the list
    if (*head == NULL) {
        *head = newNode;
    } else { // otherwise, insert the new node at the head of the list
        newNode->next = *head;
        *head = newNode;
    }
}

void insert(struct TreeNode** root, struct Echipa echipa) {
    if (*root == NULL) {
        *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        (*root)->echipa = echipa;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }

    if (echipa.punctaj > (*root)->echipa.punctaj) {
        insert(&((*root)->left), echipa);
    } else if (echipa.punctaj == (*root)->echipa.punctaj) {
        // Echipele care au acelasi punctaj sunt ordonate alfabetic
        int cmp = strcmp(echipa.nume, (*root)->echipa.nume);
        if (cmp < 0) {
            insert(&((*root)->right), echipa);
        } else {
            insert(&((*root)->left), echipa);
        }
    } else {
        insert(&((*root)->right), echipa);
    }
}

void printBST(struct TreeNode* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    printBST(root->left, file);
    fprintf(file, "%-34s-  %.2f\r\n", root->echipa.nume, root->echipa.punctaj);
    printBST(root->right, file);
}

void print_lista(struct Node *head) {
    if (PRINTARE == 0) {
        return;
    }
    int i = 0;
    printf("================ PRINTARE LIST =================\n");
    while (head != NULL) {
        i++;
        if (head->next != NULL) {
            printf("%s (%f)\n", head->echipa.nume, head->echipa.punctaj);    
        } else {
            printf("%s (%f)\n", head->echipa.nume, head->echipa.punctaj);    
        }
        head = head->next;
    }
    printf("================ PRINTARE LIST (%d echipe) =================\n", i);
}

void print_campionat(Queue* queue) {
    if (PRINTARE == 0) {
        return;
    }
    printf("================ PRINTARE CAMPIONAT =================\n");
    int i = 1;
    MeciNode* current = queue->front;
    while (current != NULL) {
        printf("Test acasa %s\n", current->echipa_acasa.nume);
        printf("Meci %d: %s vs. %s\n", i, current->echipa_acasa.nume, current->echipa_deplasare.nume);
        current = current->next;
        i++;
    }
    printf("================ PRINTARE CAMPIONAT (%d meciuri) =================\n", i);
}


int main(int argc, char *argv[]) {

    // Citire argumente
    if (argc < 4) {
        printf("Eroare: %s incorect. Programul trebuie rulat cu 3 parametri c.in d.in r.out\n", argv[0]);
        return 1;
    }

    // Citire cerinte
    FILE *cp = fopen(argv[1], "r");
    if (cp == NULL) {
        printf("Nu s-a putut deschide fisierul cu cerinte.\n");
        return 1;
    }
    int cerinte[5];
    int i;
    for (i = 0; i < 5; i++) {
        fscanf(cp, "%d", &cerinte[i]);
    }
    fclose(cp);


    // Citire date
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Nu s-a putut deschide fisierul cu date.\n");
        return 1;
    }

    if (cerinte[0] != 1) {
        printf("Cerinta 1 nu se executa");
        return 0;
    }

    int numar_echipe;
    fscanf(fp, "%d", &numar_echipe);

    // Allocate memory for the head node of the linked list
    struct Node* head = NULL;

    for (int i = 0; i < numar_echipe; i++) {
        // Allocate memory for the new node and the Echipa struct inside it 
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
        new_node->echipa.jucatori = (struct Jucator *) malloc(sizeof(struct Jucator) * new_node->echipa.numar_jucatori);
        

        // \r pt windows si \n pt mac
        fscanf(fp, "%d %[^\r\n]\n", &new_node->echipa.numar_jucatori, new_node->echipa.nume);
        // Unele echipe au space la final
        remove_trailing_spaces(new_node->echipa.nume);
        // printf("Echipa: %s\n", new_node->echipa.nume);


        int punctaj_total = 0;
        for (int j = 0; j < new_node->echipa.numar_jucatori; j++) {            
            fscanf(fp, "%s %s %d\n", new_node->echipa.jucatori[j].nume, new_node->echipa.jucatori[j].prenume, &new_node->echipa.jucatori[j].punctaj);
            // printf("Jucator: %s\n", new_node->echipa.jucatori[j].nume);
            punctaj_total +=  new_node->echipa.jucatori[j].punctaj;
        }

        new_node->echipa.punctaj = (float)punctaj_total/new_node->echipa.numar_jucatori;

        new_node->next = head;
        head = new_node;
    }

    fclose(fp); 

    // Cerinta 2 nu se executa, printam cerinta 1
    if (cerinte[1] == 0) {
        print_lista(head);
        FILE *rp = fopen(argv[3], "w");
        if (rp == NULL) {
            printf("Error: Could not open file '%s'\n", argv[3]);
            return 1;
        }

        while (head != NULL) {
            fprintf(rp, "%s\r\n", head->echipa.nume);
            // printf("%s\n", head->echipa.nume);
            head = head->next;
        }
        fclose(rp);
        return 0;
    }


    int maxim_echipe = max_echipe(numar_echipe);
    int numar_echipe_de_sters = numar_echipe - maxim_echipe;
    if (PRINTARE == 1) {
        printf("Au fost %d echipe, trebuie sa ramana doar %d, stergem %d. \r\n", numar_echipe, maxim_echipe, numar_echipe_de_sters);    
    }

    for (int i = 0; i < numar_echipe_de_sters; i++) {
        if (PRINTARE == 1) {
            printf("Inainte de stergere %d: \n", i);
            print_lista(head);
        }
        
        sterge_min(&head);

        if (PRINTARE == 1) {
            printf("Dupa stergere %d: \n", i);
            print_lista(head);      
        }    
    }

    FILE *rp = fopen(argv[3], "w");
    if (rp == NULL) {
        printf("Error: Could not open file '%s'\n", argv[3]);
        return 1;
    }

    // Cerinta 3 nu se executa
    if (cerinte[2] == 0) {
        while (head != NULL) {
            fprintf(rp, "%s\r\n", head->echipa.nume);
            head = head->next;
        }
        fclose(rp);
        return 0;
    }

    // Incepem cerinta 3
    Queue* campionat;
    campionat = createQueue();

    while (head != NULL) {
        fprintf(rp, "%s\r\n", head->echipa.nume);
        fprintf(rp, "%s\r\n", head->next->echipa.nume);
        enQueue(campionat, head->echipa, head->next->echipa);
        struct Node* oldHead = head;
        head = oldHead->next->next;
        free(oldHead);
    }
    fprintf(rp, "\r\n");

    // Incepem campionatul
    struct Node* castigatori = NULL;
    struct Node* invinsi = NULL;
    int campionat_finalizat = 0;
    struct Node* clasament =NULL;

    // Se joaca runda
    int runda = 1;

    // 
    while (campionat_finalizat == 0) {
        fprintf(rp, "--- ROUND NO:%d\r\n", runda);
        int nr_castigatori = 0;
        while (campionat->front != NULL) {
            MeciNode* meci = deQueue(campionat);
            fprintf(rp, "%-33s-%33s\r\n", meci->echipa_acasa.nume, meci->echipa_deplasare.nume);
            int rezultat = joacaMeci(meci->echipa_acasa, meci->echipa_deplasare);
            if (rezultat == 1) {
                meci->echipa_acasa.punctaj += 1;
                push(&castigatori, meci->echipa_acasa);
                push(&invinsi, meci->echipa_deplasare);
            } else {
                meci->echipa_deplasare.punctaj += 1;
                push(&castigatori, meci->echipa_deplasare);
                push(&invinsi, meci->echipa_acasa);
            }
            nr_castigatori++;
        }
        fprintf(rp, "\r\n");

        // Stergem invinsi
        while (invinsi != NULL) {
            pop(&invinsi);
        }

        fprintf(rp, "WINNERS OF ROUND NO:%d\r\n", runda);
        // Avem un singur castigator s-a terminat campionatul
        if (castigatori->next == NULL) {
            fprintf(rp, "%-34s-  %.2f\r\n", castigatori->echipa.nume, castigatori->echipa.punctaj);
            campionat_finalizat = 1;
            continue;
        }

        // Repopulam campionat
        while (castigatori != NULL && campionat_finalizat == 0) {
            fprintf(rp, "%-34s-  %.2f\r\n", castigatori->echipa.nume, castigatori->echipa.punctaj);
            fprintf(rp, "%-34s-  %.2f\r\n", castigatori->next->echipa.nume, castigatori->next->echipa.punctaj);
            enQueue(campionat, castigatori->echipa, castigatori->next->echipa);
            if (nr_castigatori == 8) {
                insertNode(&clasament, castigatori->echipa);
                insertNode(&clasament, castigatori->next->echipa);
            }
            struct Node* oldCastigatori = castigatori;
            castigatori = oldCastigatori->next->next;
            free(oldCastigatori);
        }
        fprintf(rp, "\r\n");
        runda++;
    }

    // Cerinta 4 nu se executa
    if (cerinte[3] == 0) { 
        fclose(rp);
        return 0;
    }

    struct Node* clasamentIterator =clasament;
    TreeNode* clasamentTree = NULL;
    while (clasamentIterator != NULL) {
        insert(&clasamentTree, clasamentIterator->echipa);
        clasamentIterator = clasamentIterator->next;
    }
    free(clasamentIterator);

    fprintf(rp, "\r\nTOP 8 TEAMS:\r\n");
    printBST(clasamentTree, rp);


    // Cerinta 5 nu se executa
    if (cerinte[4] == 0) { 
        fclose(rp);
        return 0;
    }


    fclose(rp);
    return 0;
}