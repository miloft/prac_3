#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

double phi(int, double, char*);

int main () {
	cout << "u_t = a*u_xx \n" 
	<< "u(0,x) = phi(x) \n"
	<< "A1*u_x(t,0) + B1*u(t,0) = phi1(t) \n"
	<< "A2*u_x(t,X) + B2*u(t,X) = phi2(t) \n";
	ofstream out ("data.txt");
	int a, a1, a2, b1, b2, phi1, phi2, T, X;
	char func[20], phi_char[20];
	int N = 10;
	int M = 10;	
	// Uslovia 
//	{
//	cout << "a = "; cin >> a;
//	//cout << "f(t,x) = "; cin >> func;
	cout << "phi(x) = "; cin >> phi_char;
//	cout << "A1 = "; cin >> a1;
//	cout << "B1 = "; cin >> b1;
//	cout << "A2 = "; cin >> a2;
//	cout << "B2 = "; cin >> b2;
	cout << "phi1 = "; cin >> phi1;
	cout << "phi2 = "; cin >> phi2;
//	cout << "T = "; cin >> T;
//	cout << "X = "; cin >> X;
//	}
a = 1; a1 = 0; a2 = 0; b1 = 1; b2 = 1; phi1 = 1; phi2 = 3; T = 2; X = 20;
	double x[M+1], t[N+1], u[N][M];
	double h = (double )X/M;
	double tau = (double )T/N;
	
	for (int n = 0; n <= N; n++) //Шаг по времени
		t[n] = n*tau;
		
	for (int m = 0; m <= M; m++) //Шаг по пространству
		x[m] = m*h;
		
	for (int m = 0; m < M; m++) {
		u[0][m] = phi(m, h, phi_char);
	}
	
	for (int n = 0; n < N; n++) {
		cout << n << " " << t[n] << endl;
		for (int m = 1; m < M-1; m++) {
			u[n+1][m] = u[n][m]+(n*tau/(h*h))*(u[n][m-1]-2*u[n][m]+u[n][m+1]);
			u[n+1][0] = (double)phi1*n*tau;
			u[n+1][M-1] = (double)phi2*n*tau;
		}
	}
	for (int n = 0; n <= N; n++) {
		for (int m = 0; m <= M; m++) {
			out << "time = " << n*tau << " x_m = " << x[m] << " u[time][x_m] = " << u[n][m] << endl;
		}
	}
	
	return 0;
}

double phi(int q, double h, char* s) {
	int i = 0, k = 0;
	double hh = q*h;
	int fl1[10], r[10];
	double func = 1.0;
	double param = 1.0;
	size_t l = strlen(s);
	
	do {
		if (s[i] == 's' ) {
			fl1[k] = 1; 
			i += 3;
		}
		else if (s[i] == 'c') {
			fl1[k] = 2; 
			i += 3;
		}
		else if (s[i] == 'x') {
			fl1[k] = 3; 
			i++;
		}
		else {
			fl1[k] = 4;
			r[k] = s[i] - '0';
			i++;
		}
		k++;
	} while (i < l);
	
	int tt = k;
	
	for (int k = 0; k < tt; k++) {
		if (fl1[k] == 3) 
			func *= hh; 
		else if (fl1[k] == 4) 
			func *= r[k];
		else {
			for (int z = k + 1; z < tt; z++) {
				if (fl1[z] == 3) 
					param *= hh;
				else param *= r[z];
			}
			if (fl1[k] == 1) func *= sin(param);
			if (fl1[k] == 2) func *= cos(param);
		}
	}
	return func;
}
