#include <bits/stdc++.h>
using namespace std;

#define M 15
float ans[M];

const double EPS = 1E-9;

int compute_rank(vector<vector<double>> A) {
    int n = A.size();
    int m = A[0].size();

    int rank = 0;
    vector<bool> row_selected(n, false);
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!row_selected[j] && abs(A[j][i]) > EPS)
                break;
        }

        if (j != n) {
            ++rank;
            row_selected[j] = true;
            for (int p = i + 1; p < m; ++p)
                A[j][p] /= A[j][i];
            for (int k = 0; k < n; ++k) {
                if (k != j && abs(A[k][i]) > EPS) {
                    for (int p = i + 1; p < m; ++p)
                        A[k][p] -= A[j][p] * A[k][i];
                }
            }
        }
    }
    return rank;
}

void PrintMatrix(float a[][M], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++)
        cout << a[i][j] << " ";
        cout << endl;
    }
}

int PerformOperation(float a[][M], int n)
{
    int i, j, k = 0, c, flag = 0, m = 0;
    for (i = 0; i < n; i++)
    {
        if (a[i][i] == 0)
        {
            c = 1;
            while ((i + c) < n && a[i + c][i] == 0)
                c++;
            if ((i + c) == n) {
                flag = 1;
                break;
            }
            for (j = i, k = 0; k <= n; k++)
                swap(a[j][k], a[j+c][k]);
        }

        for (j = 0; j < n; j++) {
            if (i != j) {
                float pro = a[j][i] / a[i][i];
                for (k = 0; k <= n; k++)
                    a[j][k] = a[j][k] - (a[i][k]) * pro;
            }
        }
    }
    return flag;
}

void PrintResult(float a[][M], int n, int flag)
{
    if (flag == 2)
    cout << "Infinite Solutions Exists" << endl;
    else if (flag == 3)
    cout << "No Solution Exists" << endl;
    else {
        for (int i = 0; i < n; i++){
            cout << -(a[i][n] / a[i][i]) << " \n";
            ans[i]=(-(a[i][n] / a[i][i]));
        }

    }
}

int CheckConsistency(float a[][M], int n, int flag)
{
    int i, j;
    int sum;
    flag = 3;
    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++){
            sum = sum + a[i][j];
        }
        if (sum == a[i][j]){
            flag = 2;}
    }
    return flag;
}

int main(int argc, char *argv[])
{
    if(argc < 2)cerr<<"Please provide valid input"<<endl;
    float a[M][M];
    float org[M][M];
    int n,m;
    int argCount = 1;
    n = atoi(argv[argCount++]);
    m = atoi(argv[argCount++]);
    vector<vector<double>> v;
    for(int i=0;i<n;i++){
        vector<double> v1;
        for(int j=0;j<m;j++){
            org[i][j]=atof(argv[argCount++]);
            a[i][j] = org[i][j];
            v1.push_back((double)org[i][j]);
        }
        v.push_back(v1);
    }
    int flag = 0;
    n=compute_rank(v);
    flag = PerformOperation(a, n);

    if (flag == 1)
        flag = CheckConsistency(a, n, flag);

    PrintResult(a, n, flag);
    float value=INT_MAX;
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=0;j<n;j++){
            int num=org[i][j]*ans[j];
            sum=sum+num;
        }
        value=min(value,(-sum/org[i][n]));
    }
    cout<<value<<endl;

    return 0;
}
