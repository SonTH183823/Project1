#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"
#include "Queue.h"

int N, Edges;
int Count = 0;
int countBFS = 0;
int countDFS = 0;
int countLienThong = 0;
int startRead, finishRead;
int startDFS, finishDFS;
int startBFS, finishBFS;
int startCountDTLT, finishCountDTLT;

typedef struct Node
{
    int ID;
    struct Node *next;
} Node;

Node *a; //mang lưu tru cac Node
struct Node_Tree *root;

int *check; //mang check trang thai cac Node

Node *initNode()
{
    Node *q = (Node *)malloc(sizeof(Node));
    q->next = NULL;
    return q;
}

void addNode(int k, Node *p)
{
    Node *q = initNode();
    Node *h;
    h = p;
    while (h->next != NULL)
    {
        h = h->next;
    }
    h->next = q;
    q->ID = k;
}

void printStruct(int s)
{
    int i;
    if (s > N)
    {
        printf("Do thi chi co %d dinh\n", N);
        s = N;
    }
    for (i = 0; i < s; i++)
    {
        Node *f = a + i;
        do
        {
            printf("%d ", f->ID);
            f = f->next;
        } while (f != NULL);
        printf("\n");
    }
}

void readFile(FILE *fin)
{
    //tach lay so node va so canh
    char str[5][255];
    int i;
    fgets(str[0], 255, fin);
    fgets(str[0], 255, fin);
    for (i = 0; i < 5; i++)
    {
        fscanf(fin, "%s", str[i]);
    }
    N = atoi(str[2]);     // so node
    Edges = atoi(str[4]); //so canh
    fgets(str[0], 255, fin);
    fgets(str[0], 255, fin);
}

void saveStruct(FILE *fin)
{
    int goc, ke, c = 0;
    int d = 0;
    while (c != Edges)
    {
        fscanf(fin, "%d%d", &goc, &ke);
        if (findValue(root, goc) == -1)
        {
            root = insert(root, goc, Count);
            d++;
            (a + Count)->ID = goc;
            addNode(ke, (a + Count));
            Count++;
            if (findValue(root, ke) == -1)
            {
                root = insert(root, ke, Count);
                d++;
                (a + Count)->ID = ke;
                Count++;
            }
        }
        else
        {
            int vt = findValue(root, goc);
            addNode(ke, (a + vt));
            if (findValue(root, ke) == -1)
            {
                root = insert(root, ke, Count);
                d++;
                (a + Count)->ID = ke;
                Count++;
            }
        }
        c++;
    }
    N = d;
    return;
}

//dua tat ca cac node ve trang thai ban dau
void resetCheck()
{
    int i;
    for (i = 0; i < N; i++)
    {
        *(check + i) = 0;
    }
    return;
}

//duyetbfs
Node *BFS(int start, int ID)
{
    if (findValue(root, start) == -1)
    {
        printf("Khong ton tai duong di tu Node co ID = %d den Node co ID = %d !\n", start, ID);
        return NULL;
    }
    else if (findValue(root, ID) == -1)
    {
        printf("Khong ton tai Node can tim %d !\n", ID);
        return NULL;
    }
    else
    {
        pushNodeQueue(start);
        *(check + findValue(root, start)) = 1;
        while (firstNodeQueue != NULL)
        {
            int first = popNodeQueue();
            if (first == -1)
            {
                printf("Khong ton tai duong di tu Node co ID = %d den Node co ID = %d !\n", start, ID);
                resetCheck();
                freeQueue();
                return NULL;
            }
            countBFS++;
            int vt = findValue(root, first);
            if (first == ID)
            {
                resetCheck();
                freeQueue();
                return (a + vt);
            }
            else
            {
                Node *p = (a + vt)->next;
                while (p != NULL)
                {
                    int vtKe = findValue(root, p->ID);
                    if (*(check + vtKe) == 0)
                    {
                        pushNodeQueue(p->ID);
                        *(check + vtKe) = 1;
                    }
                    p = p->next;
                }
            }
        }
        if (firstNodeQueue == NULL)
        {
            printf("Khong ton tai duong di tu Node co ID = %d den Node co ID = %d !\n", start, ID);
            resetCheck();
            freeQueue();
            return NULL;
        }
    }
}

//duyet dfs
void pushQ(Node *p)
{
    if (p->next != NULL)
    {
        pushQ(p->next);
    }
    int vtKe = findValue(root, p->ID);
    if (*(check + vtKe) == 0)
    {
        pushfirstNodeQueue(p->ID);
        *(check + vtKe) = 1;
    }
    return;
}

Node *DFS(int start, int ID)
{
    if (findValue(root, start) == -1)
    {
        printf("Khong ton tai Node co ID = %d trong do thi!\n", start);
        return NULL;
    }
    else if (findValue(root, ID) == -1)
    {
        printf("Khong ton tai Node can tim! %d\n", ID);
        return NULL;
    }
    else
    {
        pushNodeQueue(start);
        *(check + findValue(root, start)) = 1;
        while (firstNodeQueue != NULL)
        {
            int first = popNodeQueue();
            if (first == -1)
            {
                printf("Khong ton tai duong di tu Node co ID = %d den Node co ID = %d !\n", start, ID);
                resetCheck();
                freeQueue();
                return NULL;
            }
            countDFS++;
            int vt = findValue(root, first);
            if (first == ID)
            {
                resetCheck();
                freeQueue();
                return (a + vt);
            }
            else
            {
                pushQ((a + vt)->next);
            }
        }
        if (firstNodeQueue == NULL)
        {
            printf("Khong ton tai duong di tu Node co ID = %d den Node co ID = %d !\n", start, ID);
            resetCheck();
            freeQueue();
            return NULL;
        }
    }
}

//ham bfs duyet tim so do thi lien thong
Node *BFS_count(int start)
{
    pushNodeQueue(start);
    *(check + findValue(root, start)) = 1;
    while (firstNodeQueue != NULL)
    {
        int first = popNodeQueue();
        int vt = findValue(root, first);
        Node *p = (a + vt)->next;
        while (p != NULL)
        {
            int vtKe = findValue(root, p->ID);
            if (*(check + vtKe) == 0)
            {
                pushNodeQueue(p->ID);
                *(check + vtKe) = 1;
            }
            p = p->next;
        }
    }
    countLienThong++;
}

void soDoThiLienThong()
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (*(check + i) == 0)
        {
            BFS_count((a + i)->ID);
        }
    }
    resetCheck();
    freeQueue();
    printf("\nSo do thi lien thong la %d", countLienThong);
    countLienThong = 0;
}

void menu()
{
    int choice;
    int IDstart, IDsearch;
    do
    {
        system("cls");
        printf("\n----------------------PROJECT1----------------------\n\n");
        printf("1.In do thi\n");
        printf("2.Duyet BFS\n");
        printf("3.Duyet DFS\n");
        printf("4.Dem so do thi lien thong\n");
        printf("5.So dinh va so canh\n");
        printf("6.Thoi gian doc file va luu cau truc\n");
        printf("0.Thoat\n");
        printf("Moi chon chuc nang? \n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nNhap so dinh : ");
            int s;
            scanf("%d", &s);
            printStruct(s);
            printf("\n----------------------------------------------------\n");
            system("pause");
            break;
        case 2:
            printf("\nNhap ID Node bat dau va ID Node can tim: ");
            scanf("%d%d", &IDstart, &IDsearch);
            startBFS = clock();
            if (BFS(IDstart, IDsearch) != NULL)
                printf("\nSo thao tac duyet la: %d", countBFS);
            finishBFS = clock();
            countBFS = 0;
            printf("\nThoi gian duyet BFS la: xap xi %d\n", (finishBFS - startBFS));
            printf("\n----------------------------------------------------\n");
            system("pause");
            break;
        case 3:
            printf("\nNhap ID Node bat dau va ID Node can tim: ");
            scanf("%d%d", &IDstart, &IDsearch);
            startDFS = clock();
            if (DFS(IDstart, IDsearch) != NULL)
                printf("So thao tac duyet la: %d", countDFS);
            finishDFS = clock();
            printf("\nThoi gian duyet DFS la: xap xi %d\n", (finishDFS - startDFS));
            countDFS = 0;
            printf("\n----------------------------------------------------\n");
            system("pause");
            break;
        case 4:
            startCountDTLT = clock();
            soDoThiLienThong();
            finishCountDTLT = clock();
            printf("\nThoi gian dem so do thi lien thong la: xap xi %d\n", (finishCountDTLT - startCountDTLT));
            resetCheck();
            printf("\n----------------------------------------------------\n");
            system("pause");
            break;
        case 5:
            printf("\nSo dinh: %d\nSo canh: %d\n", N, Edges);
            printf("\n----------------------------------------------------\n");
            system("pause");
            break;
        case 6:
            printf("Thoi gian doc file va luu cau truc: xap xi %d\n", (finishRead - startRead));
            printf("\n----------------------------------------------------\n");
            system("pause");
            break;
        case 0:
            printf("\n----------------------THANKYOU----------------------\n");
            exit(0);
            break;
        }
    } while (choice != 0);
}

int main()
{
    FILE *fin;
    fin = fopen("D:\\ThucHanh\\Project1\\CauTruc\\roadNet-TX.txt", "r"); //doc file
    if (fin != NULL)
    {
        startRead = clock();
        readFile(fin);
        a = (Node *)malloc(N * sizeof(Node));
        check = (int *)malloc(N * sizeof(int));
        saveStruct(fin);
        finishRead = clock();
        fclose(fin);
        menu();
    }
    else
    {
        printf("Khong doc duoc file");
        return 0;
    }
}
