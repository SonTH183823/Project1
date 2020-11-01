#include <iostream>
#include <vector>
#include <map>
#include<hash_map>
using namespace std;

int N, Edges;
int Count = 0;
vector<vector<int>> V;
map<int, int> Map;
void readFile(FILE *fin)
{
    //tach lay so node va so canh
    char str[5][255];
    int i;
    for (i = 0; i < 2; i++)
    {
        fgets(str[0], 255, fin);
    }
    for (i = 0; i < 5; i++)
    {
        fscanf(fin, "%s", str[i]);
    }
    N = atoi(str[2]);     // so node
    Edges = atoi(str[4]); //so canh
    fgets(str[0], 255, fin);
    fgets(str[0], 255, fin);
}
void saveV(FILE *fin)
{

    vector<int> tmp ={-11};
    int goc, ke;
    for (int i = 0; i < Edges; i++)
    {
        fscanf(fin, "%d%d", &goc, &ke);
        if (Map.find(goc) == Map.end())
        {
            V.push_back(tmp);
            V[Count][0] = goc;
            V[Count].push_back(ke);
            Map.insert(pair<int, int>(goc, Count));
            if (Map.find(ke) == Map.end())
            {
                Count++;
                V.push_back(tmp);
                V[Count][0] = ke;
                Map.insert(pair<int, int>(ke, Count));
            }
            Count++;
        }
        else
        {
            int vt = Map[goc];
            V[vt].push_back(ke);
            if (Map.find(ke) == Map.end())
            {
                V.push_back(tmp);
                V[Count][0] = ke;
                Map.insert(pair<int, int>(ke, Count));
                Count++;
            }
        }
    }
    return;
}
void printV()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < V[i].size(); j++)
        {
            cout << V[i][j] << " ";
        }
        cout << "\n";
    }
    return;
}
int main()
{
    FILE *fin;
    fin = fopen("D:\\ThucHanh\\Project1\\CauTruc\\roadNet-PA.txt", "r"); //doc file
    if (fin != NULL)
    {
        readFile(fin);
        saveV(fin);
        fclose(fin);
        printV();
    }
    else
    {
        printf("Khong doc duoc file");
        return 0;
    }
}
