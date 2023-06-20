#include <iostream>
#include <cmath>

using namespace std;

void getSolution(int n, int m, double M){
  double A[m][n];
  double B[m];
  double C[n];
  //ввод данных с клавиатуры
  for(int i=0; i<m; i++){
    cout << "Введите коэф-ты перед Х в " << i+1 <<" уравнении ограничений" << "\n";
    for(int j=0; j<n; j++){
      cin >> A[i][j];      
    }
  }
  for(int i=0; i<m; i++){
    cout << "Введите свободный член в " << i+1 <<" уравнении ограничений" << "\n";
    cin >> B[i]; 
  }
  for(int i=0; i<n; i++){
    cout << "Введите коэф-т в целевой функции перед X" << i +1 << "\n";
    cin >> C[i]; 
  }
  
  double nc[n+1];//вычисляем альфы
  nc[n]=0;
  for(int i=0; i<n; i++){
    nc[i]=-C[i];
    for(int j=0; j<m; j++){
      if(B[j]>=0)
        nc[i]+=-M*A[j][i];   
      else
        nc[i]+=M*A[j][i];   
    }
  }
  for(int j=0; j<m; j++){
    if(B[j]>=0){
      nc[n]+=-M*B[j];
      }
    else{
      nc[n]+=M*B[j];   
   }
    }
  
  
  //заполняем исходную симплекс таблицу
  double table[m+1][n+m+1];
  for(int i=0; i<m+1; i++){
    for(int j=0; j<n+m+1; j++){
      table[i][j]=0;
    }
  }
  
  for(int i=0; i<m; i++){
    if(B[i]>=0){
      table[i][n+m]=B[i];
      for(int j=0; j<n; j++)
        table[i][j]=A[i][j];
    }
    else{
      table[i][n+m]=-B[i];
      for(int j=0; j<n; j++)
        table[i][j]=-A[i][j];
    }
  }
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      if(i==j){
        table[i][j+n]=1;
      }
    }
  }
  for(int i=0; i<n; i++){
      table[m][i]=nc[i];
  }
  table[m][n+m]=nc[n];
  //закончили заполнять таблицу
  //выводим на экран
  cout<<"----------------------------------------"<<'\n';
  cout<<"1-я итерация"<<'\n';
   /*for(int i=0; i<m+1; i++){
        for(int j=0; j<n+m+1; j++){
          cout << table[i][j] <<"   "<<'\t';
        }
        cout<<'\n';
      }*/
  
  
  int basis[m], //текущий базис-вектор
  k=0;
  bool exit_code = true;
  for(int i=0; i<m; i++)
    basis[i]=i+n;

  cout <<"сейчас в базис входят следующие переменные: ";
      for(int i=0; i<m; i++)
        cout <<"X"<<basis[i]+1<<" ";
      cout<<'\n';
  //выводим вершину, в которой находимся и значение функции в ней
   cout << "находимся в вершине с координатами:" << "\n";
  int kk_ = 0, bcount_=0;
  for(int j=0; j<m+n; j++){
    for(int i=0; i<m; i++){
      if(basis[i]==j){
        kk_++;
    }
  }
    if(kk_>0){
      cout << "X" << j+1 << " = "<< table[bcount_][n+m] << "\n";
      bcount_++;
      }
      else cout << "X" << j+1 << " = "<< 0 << "\n";
    }
  cout << "Значение целевой функции F = "<< table[m][n+m] << "\n";
  //начало итерационного алгоритма
  while(true){
    double newTable[m+1][n+m+1];
    int counter =0;
    for(int i=0; i<n; i++)
      if(table[m][i]<0){
        counter++;
      }
    if(counter == 0)
      break;
    else{
      
      double maxCol=0, minRow=M, Di;
      int maxColIndex = -1, minRowIndex=-1, n_amount=0;
      for(int i=0; i<n; i++){
        if(table[m][i]<0 && abs(table[m][i])>abs(maxCol)){
          maxCol = table[m][i];
          maxColIndex = i;
        }
      }
      //проверяем разрешающий столбец
      for(int i=0; i<m; i++){
        if(table[i][maxColIndex]<0){
          n_amount++;
        }
      }
      if(n_amount==m){
        exit_code = false;
        break;        
      }
      for(int i=0; i<m; i++){
        Di=table[i][m+n]/table[i][maxColIndex];
        if(Di>=0)
          if(Di<minRow){
            minRow=Di;
            minRowIndex=i;
          }
      }
      double solElem = table[minRowIndex][maxColIndex];
      cout<<"----------------------------------------"<<'\n';
      cout << k+2<<"-я итерация"<<'\n';
      cout << "на данном шаге выводим из базиса переменную X" << basis[minRowIndex]+1 <<"\n";
      cout << "и вместо нее вводим в базис переменную X" << maxColIndex+1 <<"\n"<<"\n";
      basis[minRowIndex]=maxColIndex;
      for(int i=0; i<m+1; i++)
        if(i!=minRowIndex)
          for(int j=0; j<m+n+1; j++)
            newTable[i][j]=table[i][j] - table[minRowIndex][j]*table[i][maxColIndex]/solElem;
        else 
          for(int j=0; j<m+n+1; j++)
            newTable[i][j]=table[i][j]/solElem;
      //переносим из временной таблицы в постоянную
      for(int i=0; i<m+1; i++)
        for(int j=0; j<n+m+1; j++)
           table[i][j] = newTable[i][j];
      //вывод на экран
      
      cout <<"сейчас в базис входят следующие переменные: ";
      for(int i=0; i<m; i++)
        cout <<"X"<<basis[i]+1<<" ";
      cout<<'\n';
  //выводим вершину, в которой находимся и значение функции в ней 
      cout << "находимся в вершине с координатами" << "\n";
      int bcount=0;
  for(int j=0; j<m+n; j++){
    int kk = 0;
    for(int i=0; i<m; i++){
      if(basis[i]==j){
        kk++;
    }
  }
    if(kk>0){
      cout << "X" << j+1 << " = "<< table[bcount][n+m] << "\n";
      bcount++;
      }
      else cout << "X" << j+1 << " = "<< 0 << "\n";
    }
  cout << "Значение целевой функции: F = "<< table[m][n+m] << "\n";
      
      /*for(int i=0; i<m+1; i++){
        for(int j=0; j<n+m+1; j++){
          cout << table[i][j] <<"   "<<'\t';
        }
        cout<<'\n';
      }*/
      k++;
      
  }//получили новую симплекс таблицу, переходим к следующей итерации
}//выполнился критерий оптимальности, выходим из цикла
  cout<<"----------------------------------------"<<'\n';
  cout<<"Получаем решение:"<<'\n';
  if(exit_code){
    double b[m+1], iter=0;
  b[m]=table[m][m+n];
  for(int i=0; i<m; i++){
    b[i]=table[i][m+n];
    if(basis[i]>m && b[i]!=0)
      iter++;
  }
  if(iter==0){
    for(int i=0; i<m; i++){
      if(basis[i]+1<=m){
      cout<<"Переменная Х"<<basis[i]+1<<" входит в оптимальное решение, X"<<basis[i]+1<<"="<<b[i]<<'\n';
    }
    else if (b[i]==0)
      cout<<"Искусственная переменная Х"<<basis[i]+1<<" входит в оптимальное решение с нулевым значением, поэтому на значение целевой функции не влияет"<<'\n';
    }
    cout<<"Значение целевой функции "<<b[m]<<'\n';
  }
  else cout<<"Так как в оптимальном решении присутствуют искусственные переменные , то задача не имеет допустимого решения.";
  }
  else cout<<"Функция не ограничена, оптимального решения не существует";

}
int main() {
  int n,m;
  double M=100;//большое число, используемое в методе больших штрафов
  cout << "Введите количество переменных" << "\n";
  cin >> n;
  cout << "Введите количество ограничений" << "\n";
  cin >> m;
  getSolution(n,m,M);  
}