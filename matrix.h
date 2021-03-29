#include <iostream>
#include <vector>

using namespace std;

/************************************Matrix***********************************************/

class Matrix
{
private:
    int n, m;
    vector<vector<float>> matrix;
    vector<pair<int, int>> pivote;
    pair<int, int> lastPivote;

    // Private Methods
    void findNextPivote();
    void takePivoteRowAbove(pair<int, int>);
    void makeBelowPivoteZero(pair<int, int>);
    void makeAbovePivoteZero(pair<int, int>);

public:
    Matrix() {}
    Matrix(int a, int b)
    {
        n = a;
        m = b;
    }

    // Matrix Operations
    Matrix operator*(Matrix);
    Matrix operator+(Matrix);
    Matrix operator-(Matrix);

    // Scaler Operations
    friend Matrix operator*(Matrix, int);
    friend Matrix operator/(Matrix, int);
    friend Matrix operator+(Matrix, int);
    friend Matrix operator-(Matrix, int);

    // Class Methods
    void setMatrix();
    void display();
    void makeRREF();
    void makeREF();
};


class Inverse
{
private:
    int n, m;
    vector<vector<float>> matrix;
    vector<vector<float>> inverse;
    vector<pair<int, int>> pivote;
    pair<int, int> lastPivote;
    void findNextPivote();
    void takePivoteRowAbove(pair<int, int>);
    void makeBelowPivoteZero(pair<int, int>);
    void makeAbovePivoteZero(pair<int, int>);
    void makeREF();

public:
    void setMatrix();
    void makeInverse();
    void display();
};


/************************************Defining Function of Matrix*****************************/

void Matrix ::setMatrix()
{
    cout << "Enter number of matrix rows and column seprated by space : ";
    cin >> n >> m;
    cout << "Enter Matrix element : " << endl;
    for (int i = 0; i < n; i++)
    {
        vector<float> temp;
        float x;
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            temp.push_back(x);
        }
        matrix.push_back(temp);
    }
}

void Matrix ::display()
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != (-0))
                cout << matrix[i][j] << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
    cout << endl
         << endl;
}

/************************************Defining Function of ToREF*****************************/

void Matrix ::findNextPivote()
{
    cout << "Find next pivote" << endl;
    int x = pivote.size();
    bool gotPivote = false;
    if (x == 0)
    {
        for (int i = 0; i < m; i++)
        {
            bool flag = false;
            for (int j = 0; j < n; j++)
            {
                if (matrix[j][i] != 0)
                {
                    pivote.push_back(make_pair(j, i));
                    lastPivote = make_pair(j, i);
                    gotPivote = true;
                    flag = true;
                    break;
                }
            }
            if (flag == true)
            {
                break;
            }
        }
    }

    else
    {
        int a = pivote[x - 1].second;
        int b = pivote[x - 1].first;
        if (a < m)
            ;
        {
            for (int i = a + 1; i < m; i++)
            {
                bool flag = false;
                for (int j = b + 1; j < n; j++)
                {
                    if (matrix[j][i] != 0)
                    {
                        pivote.push_back(make_pair(j, i));
                        lastPivote = make_pair(j, i);
                        gotPivote = true;
                        flag = true;
                        break;
                    }
                }
                if (flag == true)
                {
                    break;
                }
            }
        }
    }
    if (gotPivote == false)
    {
        lastPivote = make_pair(n, m);
    }
    if (lastPivote.first != n)
        cout << "Pivote : (" << lastPivote.first + 1 << ", " << lastPivote.second + 1 << ")" << endl
             << endl;
    else
    {
        cout << "No more pivotes..." << endl
             << endl;
        cout << "****REF Matrix****" << endl;
        display();
    }
}

void Matrix ::takePivoteRowAbove(pair<int, int> p)
{
    cout << "Take pivote row above" << endl
         << endl;
    int rowNo1 = pivote.size() - 1;
    int rowNo2 = p.first;

    cout << "R" << rowNo1 + 1 << " <-> R" << rowNo2 + 1 << endl;

    for (int i = 0; i < m; i++)
    {
        float temp = matrix[rowNo1][i];
        matrix[rowNo1][i] = matrix[rowNo2][i];
        matrix[rowNo2][i] = temp;
    }
    lastPivote = make_pair(rowNo1, p.second);
    pivote[rowNo1] = make_pair(rowNo1, p.second);
    display();
}

void Matrix ::makeBelowPivoteZero(pair<int, int> p)
{
    cout << "Make elements below pivote zero" << endl
         << endl;
    float a = matrix[p.first][p.second];
    cout << "R" << p.first + 1 << " --> R" << p.first + 1 << " / " << a << endl;
    for (int i = 0; i < m; i++)
    {
        matrix[p.first][i] /= a;
    }

    for (int i = p.first + 1; i < n; i++)
    {
        float b = matrix[i][p.second];
        cout << "R" << i + 1 << " --> R" << i + 1 << " - (R" << p.first + 1 << " * " << b << ")" << endl;
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] -= (b * matrix[p.first][j]);
        }
    }
    display();
}

void Matrix ::makeREF()
{
    cout << endl
         << "Convert to REF" << endl;

    do
    {
        findNextPivote();
        if (lastPivote.first != n)
        {
            takePivoteRowAbove(lastPivote);
            makeBelowPivoteZero(lastPivote);
        }
    } while (lastPivote.first != n);
}

/************************************Defining Function of ToRREF*****************************/

void Matrix ::makeAbovePivoteZero(pair<int, int> p)
{
    cout << "Make all elements above pivote zero" << endl;
    for (int i = 0; i < p.first; i++)
    {
        float b = matrix[i][p.second];
        cout << "R" << i + 1 << " --> R" << i + 1 << " - (R" << p.first + 1 << " * " << b << ")" << endl;
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] -= (b * matrix[p.first][j]);
        }
    }
    display();
}

void Matrix ::makeRREF()
{
    makeREF();
    for (int i = pivote.size() - 1; i >= 0; i--)
    {
        makeAbovePivoteZero(pivote[i]);
    }
    cout << "****RREF Matrix****" << endl;
}

/************************************Matrix operator * overloading***************************/

Matrix Matrix ::operator*(Matrix Mat)
{
    Matrix product(n, Mat.m);
    if (m == Mat.n)
    {
        for (int i = 0; i < n; i++)
        {
            vector<float> temp;
            for (int j = 0; j < Mat.m; j++)
            {
                float element = 0;
                for (int k = 0; k < m; k++)
                {
                    float a = matrix[i][k];
                    float b = Mat.matrix[k][j];
                    element += (a * b);
                }
                temp.push_back(element);
            }
            product.matrix.push_back(temp);
        }
    }
    else
    {
        cout << "Matrix multiplaction of this two matrixs is not possible..." << endl;
    }
    return product;
}

/************************************Matrix operator + overloading***************************/

Matrix Matrix ::operator+(Matrix Mat)
{
    Matrix sum(n, m);
    if (n == Mat.n && m == Mat.m)
    {
        for (int i = 0; i < n; i++)
        {
            vector<float> temp;
            for (int j = 0; j < m; j++)
            {
                float elementSum = matrix[i][j] + Mat.matrix[i][j];
                temp.push_back(elementSum);
            }
            sum.matrix.push_back(temp);
        }
    }
    else
    {
        cout << "Matrix addition of this two matrixs is not possible..." << endl;
    }
    return sum;
}

/************************************Matrix operator - overloading***************************/

Matrix Matrix ::operator-(Matrix Mat)
{
    Matrix diff(n, m);
    if (n == Mat.n && m == Mat.m)
    {
        for (int i = 0; i < n; i++)
        {
            vector<float> temp;
            for (int j = 0; j < m; j++)
            {
                float elementDiff = matrix[i][j] - Mat.matrix[i][j];
                temp.push_back(elementDiff);
            }
            diff.matrix.push_back(temp);
        }
    }
    else
    {
        cout << "Matrix subtraction of this two matrixs is not possible..." << endl;
    }
    return diff;
}


/************************************Scaler operator * overloading***************************/

Matrix operator*(Matrix Mat, int a)
{
    Matrix product(Mat.n, Mat.m);
    for (int i = 0; i < Mat.n; i++)
    {
        for (int j = 0; j < Mat.m; j++)
        {
            Mat.matrix[i][j] *= a;
        }
    }
    return product;
}

/************************************Scaler operator / overloading***************************/

Matrix operator/(Matrix Mat, int a)
{
    Matrix product(Mat.n, Mat.m);
    for (int i = 0; i < Mat.n; i++)
    {
        for (int j = 0; j < Mat.m; j++)
        {
            Mat.matrix[i][j] /= a;
        }
    }
    return product;
}

/************************************Scaler operator + overloading***************************/

Matrix operator+(Matrix Mat, int a)
{
    Matrix sum(Mat.n, Mat.m);
    for (int i = 0; i < Mat.n; i++)
    {
        for (int j = 0; j < Mat.m; j++)
        {
            Mat.matrix[i][j] += a;
        }
    }
    return sum;
}

/************************************Scaler operator - overloading***************************/

Matrix operator-(Matrix Mat, int a)
{
    Matrix diff(Mat.n, Mat.m);
    for (int i = 0; i < Mat.n; i++)
    {
        for (int j = 0; j < Mat.m; j++)
        {
            Mat.matrix[i][j] -= a;
        }
    }
    return diff;
}

/************************************Defining Function of Inverse*****************************/


void Inverse :: setMatrix()
{
    cout << "Enter size of square matrix : ";
    cin >> n;
    m = n;
    cout << "Enter Matrix element : " << endl;
    for(int i = 0; i < n; i++)
    {
        vector<float> temp1;
        vector<float> temp2;
        float x;
        for(int j = 0; j < m; j++)
        {            
            cin >> x;
            temp1.push_back(x);
            temp2.push_back((i==j ? 1 : 0));
        }
        matrix.push_back(temp1);
        inverse.push_back(temp2);
    }  
}


void Inverse :: findNextPivote()
{
    cout << "Find next pivote" << endl;
    int x = pivote.size();
    bool gotPivote = false;
    if(x == 0)
    {
        for(int i = 0; i < m; i++)
        {
            bool flag = false;
            for(int j = 0; j < n; j++)
            {
                if(matrix[j][i] != 0)
                {
                    pivote.push_back(make_pair(j, i));
                    lastPivote = make_pair(j, i);
                    gotPivote = true;
                    flag = true;
                    break;
                }
            }
            if(flag == true) { break; }
        }
    }

    else
    {
        int a = pivote[x-1].second; 
        int b = pivote[x-1].first;
        if(a < m);
        {
            for(int i = a + 1; i < m; i++)
            {
                bool flag = false;
                for(int j = b + 1; j < n; j++)
                {
                    if(matrix[j][i] != 0)
                    {
                        pivote.push_back(make_pair(j, i));
                        lastPivote = make_pair(j, i);
                        gotPivote = true;
                        flag = true;
                        break;
                    }
                }
                if(flag == true) { break; }
            }
        }
    }
    if(gotPivote == false)
    {
        lastPivote = make_pair(n, m);
    }
    if(lastPivote.first != n)
        cout << "Pivote : (" << lastPivote.first + 1 << ", " << lastPivote.second + 1 << ")"<< endl << endl;
    else
    {
        cout << "No more pivotes..." << endl << endl;
        cout << "****REF Matrix****" << endl;
        display();
    }
}

void Inverse :: takePivoteRowAbove(pair<int, int> p)
{
    cout << "Take pivote row above" << endl << endl;
    int rowNo1 = pivote.size() - 1;
    int rowNo2 = p.first;

    cout << "R" << rowNo1+1 << " <-> R" << rowNo2+1 << endl; 

    for(int i = 0; i < m; i++)
    {
        float temp1 = matrix[rowNo1][i];
        float temp2 = inverse[rowNo1][i];

        matrix[rowNo1][i] = matrix[rowNo2][i];
        inverse[rowNo1][i] = inverse[rowNo2][i];
        
        matrix[rowNo2][i] = temp1;
        inverse[rowNo2][i] = temp2;
    }

    lastPivote = make_pair(rowNo1, p.second);
    pivote[rowNo1] = make_pair(rowNo1, p.second);
    display();
}

void Inverse :: makeBelowPivoteZero(pair<int, int> p)
{
    cout << "Make elements below pivote zero" << endl << endl;
    float a = matrix[p.first][p.second];
    cout << "R" << p.first+1 << " --> R" << p.first+1 << " / " << a << endl; 
    for(int i = 0; i < m; i++)
    {
        matrix[p.first][i] /= a;
        inverse[p.first][i] /= a;
    }

    for(int i = p.first + 1; i < n; i++)
    {
        float b = matrix[i][p.second];
        cout << "R" << i+1 << " --> R" << i+1 << " - (R" << p.first+1 << " * " << b << ")" << endl; 
        for(int j = 0; j < m; j++)
        {
            matrix[i][j] -= (b * matrix[p.first][j]);
            inverse[i][j] -= (b * inverse[p.first][j]);
        }

    }
    display();
}

void Inverse :: display()
{
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(matrix[i][j] != (-0))
                cout << matrix[i][j] << " "; 
            else
                cout << 0 << " ";
        }

        cout << "| ";

        for(int j = 0; j < m; j++)
        {
            if(inverse[i][j] != (-0))
                cout << inverse[i][j] << " "; 
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Inverse :: makeREF()
{
    cout << endl <<"Convert to REF" << endl;

    do
    {
        findNextPivote();
        if(lastPivote.first != n)
        {
            takePivoteRowAbove(lastPivote);
            makeBelowPivoteZero(lastPivote);
        }
    }while(lastPivote.first != n);
}


/************************************Defining Function of ToRREF*****************************/

void Inverse :: makeAbovePivoteZero(pair<int, int> p)
{
    cout << "Make all elements above pivote zero" << endl;
    for(int i = 0; i < p.first; i++)
    {
        float b = matrix[i][p.second];
        cout << "R" << i+1 << " --> R" << i+1 << " - (R" << p.first+1 << " * " << b << ")" << endl; 
        for(int j = 0; j < m; j++)
        {
            matrix[i][j] -= (b * matrix[p.first][j]);
            inverse[i][j] -= (b * inverse[p.first][j]);
        }
    }
    display();
}

void Inverse :: makeInverse()
{
    makeREF();
    for(int i = pivote.size() - 1; i >= 0; i--)
    {
        makeAbovePivoteZero(pivote[i]);
    }
    cout << "****RREF | Inverse****" << endl;
}