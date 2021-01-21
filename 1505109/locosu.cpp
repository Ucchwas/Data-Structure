#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

void lcs( string X, string Y)
{
    int m = X.length();
    int n =Y.length();
    int L[m+1][n+1];
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    int idx = L[m][n];
    char l[idx+1];
    l[idx] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (X[i-1] == Y[j-1])
        {
            l[idx-1] = X[i-1];
            i--;
            j--;
            idx--;
        }
        else if (L[i-1][j] > L[i][j-1])
           i--;
        else
            j--;
    }
    int k=strlen(l);
    cout<<k<<endl;
    cout << l;
}

int main()
{
    string X,Y;
    cin>>X>>Y;
    lcs(X, Y);
    return 0;
}

