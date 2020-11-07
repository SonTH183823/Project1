#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"
#include "Queue.h"

int N, Edges;
int Count = 0;
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
        printf("Do thi chi co %d dinh!\n", N);
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
void BFS(int start)
{
    int dem = 0;
    pushNodeQueue(start);
    *(check + findValue(root, start)) = 1;
    while (firstNodeQueue != NULL)
    {
        int first = popNodeQueue();
        //printf("%d ", first);
        dem++;
        if (dem % 100000 == 0)
        {
            printf("Da duyet %d dinh!\n", dem);
        }
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
    dem = 0;
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

void DFS(int start)
{
    int dem = 0;
    pushNodeQueue(start);
    *(check + findValue(root, start)) = 1;
    while (firstNodeQueue != NULL)
    {
        int first = popNodeQueue();
        dem++;
        if (dem % 100000 == 0)
        {
            printf("Da duyet %d dinh!\n", dem);
        }
        //printf("%d ",first);
        int vt = findValue(root, first);
        pushQ((a + vt)->next);
    }
    dem = 0;
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
    int IDstart;
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
            printf("\nNhap ID Node bat dau: ");
            scanf("%d", &IDstart);
            startBFS = clock();
            BFS(IDstart);
            printf("\n");
            int i;
            for (i = 0; i < N; i++)
            {
                if (*(check + i) == 0)
                {
                    BFS((a + i)->ID);
                    //printf("\n");
                }
            }
            printf("Da duyet xong!");
            finishBFS = clock();
            printf("\nThoi gian duyet BFS la: xap xi %d\n", (finishBFS - startBFS));
            printf("\n----------------------------------------------------\n");
            freeQueue();
            resetCheck();
            system("pause");
            break;
        case 3:
            printf("\nNhap ID Node bat dau: ");
            scanf("%d", &IDstart);
            startDFS = clock();
            DFS(IDstart);
            printf("\n");
            for (i = 0; i < N; i++)
            {
                if (*(check + i) == 0)
                {
                    DFS((a + i)->ID);
                    //printf("\n");
                }
            }
            printf("Da duyet xong!");
            finishDFS = clock();
            printf("\nThoi gian duyet DFS la: xap xi %d\n", (finishDFS - startDFS));
            resetCheck();
            freeQueue();
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
    fin = fopen("D:\\ThucHanh\\Project1\\CauTruc\\roadNet-CA.txt", "r"); //doc file
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
