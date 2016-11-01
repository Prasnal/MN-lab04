#include <iostream>
#include <stdio.h>
#include <math.h>
#include "dodatki.cpp"
#define SIZE 5

using namespace std;

void print_matrix(double** matrix){
  for(int i=0; i<SIZE; i++){
    for(int j=0; j<SIZE; j++){
      cout<<"  "<<matrix[i][j];
    }
    cout<<" "<<endl;
  }
}

int main(){
  FILE *fa=fopen("dane.dat","w");
  //fprintf(fa," %f %f \n",h*i, x[i]);

  int n=SIZE;
  double** A=new double* [n];
  double** Acp=new double* [n];
  double** wwa=new double* [n]; //wektor wlasny a
  double** awwa=new double* [n];
  double *A1D=new double [n*n];//2n
  //-----
  double* d=new double[n]; //skladowe diagonali
  double* e=new double[n-1]; //skladowe poddiagonali
  //-----
  double** z=new double*[n];
  double* z1D=new double [n*n]; //2n
  double** z2D=new double* [n];


  //inicjalizacja macierzy
  for(int i=0; i<n; i++){
    A[i]=new double [n];
    z2D[i]=new double [n];
    Acp[i]=new double [n];
    z[i]=new double [n];
    wwa[i]=new double [n];
    awwa[i]=new double [n];
    for(int j=0;j<n; j++){
      A[i][j]=sqrt((i+1)+(j+1));
      Acp[i][j]=sqrt((i+1)+(j+1));
    }
  }
  print_matrix(A);
  //zad 2 - redukcja macierzy do postaci trojdiangonalnej
  mat_2Dto1D(A,A1D,n);
  dsytrd_wrapper(n,A1D,d,e);

  //zapis do pliku macierzy A1D przerobionej na 2D
  mat_1Dto2D(A1D, A, n);
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fprintf(fa," %f ", A[i][j]);
    }
    fprintf(fa,"\n");
  }

  char I='I';
  dsteqr_wrapper(&I, n, d, e, z1D);// d-wektor wartosci wlasnych e-elementy poddiagonali z1D-macierz wektorow wlasnych

  fprintf(fa,"\n \n Wartosci wlasne macierzy T: \n ");

  fprintf(fa,"\n [");
  for(int i=0; i<n; i++){
    fprintf(fa," %f ", d[i]);
  }
  fprintf(fa,"]\n");

  fprintf(fa,"\n \n Wektory wlasne macierzy T: \n ");

  mat_1Dto2D(z1D, z2D, n);
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fprintf(fa," %f ", z2D[i][j]);
    }
    fprintf(fa,"\n");
  }
  
  
  //przeksztalcanie wektorow wlasnych macierzy A=P
  //wwa=A*z2D BLAD
  for (int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      wwa[i][j]=0;
    }
  }
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      for(int k=0; k<n; k++){
        wwa[i][j]=A[i][k]*z2D[k][j]+wwa[i][j]; 
      }
    }	
  }

  fprintf(fa,"\n \n Wektory wlasne macierzy A: \n ");

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fprintf(fa," %f ", wwa[i][j]);
    }
    fprintf(fa,"\n");
  }

  //liczenie beta
  //awwa=x*wwa
  //beta=iloczyn skalarny wwa i A (isa) przez iloczyn skalarny wwa i wwa (isw)

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      for(int k=0; k<n; k++){
        awwa[i][j]=Acp[i][k]*wwa[k][j]+awwa[i][j]; 
      }
    }	
  }

  double *isa=new double[n];
  double *isw=new double[n];
  double *beta=new double[n];

   
  for(int i=0; i<n; i++){
    isa[i]=0;
    isw[i]=0;
    for(int j=0; j<n; j++){
      isa[i]=wwa[j][i]*awwa[j][i]+isa[i];
      isw[i]=wwa[j][i]*wwa[j][i]+isw[i];
    }
    
    std::cout<<"isa"<<isa[i]<<std::endl;
    beta[i]=isa[i]/isw[i];
  }
  
  fprintf(fa,"\n \n beta: \n [ ");

  for(int i=0; i<n; i++){
      fprintf(fa," %f ", beta[i]);
  }   
    fprintf(fa,"] \n");
  



  
}






