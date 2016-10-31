
extern "C" int dsytrd_(char *uplo, int *n, double *a, int *lda, double *d__, double *e, double *tau, double *work, int *lwork, int *info);
extern "C" int dorgtr_(char *uplo, int *n, double *a, int *lda, double *tau, double *work, int *lwork, int *info);
extern "C" int dsteqr_(char *compz, int *n, double *d__, double *e, double *z__, int *ldz, double *work, int *info);



//******************* WRAPPER funkcji DSYTRD *******************
//	sprowadzenie macierzy symetrycznej do trojdiagonalnej
//IN:	n - rozmiar problemu, a - macierz wejsciowa rozmiaru n*n
//OUT:	a - macierz przeksztalcenia 
//	    uwaga: wprost z dsytrd_ NIE dostajemy macierzy przeksztalcenia, dopiero po 
//		   wywolaniu dorgtr_ a jest nadpisywane prze macierz przeksztalcenia
//	d - wektor n-elementowy, elementy diagonalne macierzy trojdiagonalnej
//	e - wektor (n-1)-elementowy, elementy nad/poddiagonalne macierzy trojdiagonalnej
int dsytrd_wrapper(int n, double *a, double *d, double *e){
	char uplo='U';
	int lda=n;
	int lwork=n*3;
	int info;
	double *tau=new double[n-1];
	double *work=new double[lwork];
		dsytrd_(&uplo, &n, a, &lda, d, e, tau, work, &lwork, &info); 

	int lwork_2=(n-1)*3;
	double *work_2=new double[lwork_2];
		dorgtr_(&uplo, &n, a, &lda, tau, work_2, &lwork_2, &info); //liczy macierz przeksztalcenia na podstawie macierzy a i tau zwroconych przez dsytrd_
	delete[] tau;
	delete[] work;
	delete[] work_2;
}


//******************* WRAPPER funkcji DSTEQR *******************
//	wyliczenie wartosci i wektorow wlasnych dla macierzy trojdiagonalnej
//IN:	compz - (patrz dokumentacja dsteqr) jesli ='I' -> 
//		liczy wartosci i wektory wlasne macierzy trojdiagonalnej
//	n - rozmiar problemu, 
//	d - wektor n-elementowy, elementy diagonalne macierzy trojdiagonalnej
//	e - wektor (n-1)-elementowy, elementy poddiagonalne macierzy trojdiagonalnej
//OUT:	d - wektor wartosci wlasnych
//	z - macierz wektorow wlasnych
int dsteqr_wrapper(char *compz, int n, double *d, double *e, double *z){
	int ldz=n;
	int info;
	double *work=new double[2*n-2];
		dsteqr_(compz, &n, d, e, z, &ldz, work, &info);
}


//********** funkcje zapisujace macierze 2D w 1D i odwrotnie **********
void mat_2Dto1D(double **a2d, double *a1d, int n){
	for(int j=0; j<n; j++){
		for(int i=0; i<n; i++){
		a1d[j*n+i]=a2d[i][j];
		}
	}
}
void mat_1Dto2D(double *a1d, double **a2d, int n){
	for(int j=0; j<n; j++){
		for(int i=0; i<n; i++){
		a2d[i][j]=a1d[j*n+i];
		}
	}
}

