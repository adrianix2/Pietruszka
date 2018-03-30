#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define n 100000;


double fun1(double x)
{
	return x*x*x + 25;
}

double fun2(double x)
{
	return exp(x) - 1;
}

double fun3(double x)
{
	return sin(x);
}

double fun4(double x)
{
	return x*x + 2*x - 1;
}

double prostakaty(double (*fun)(double), double a, double b)
{
	double krok;
	krok = fabs((b-a))/n;
	double calka, x = a;
	calka = 0;
	while(b > x)
	{
		calka+= krok*fun(x);
		x += krok;
	}
	return calka;

}

double trapezy(double (*fun)(double), double a, double b)
{
	
	double krok;
	krok = fabs((b-a))/n;
	double calka = 0, x;
	calka = 0.5 * a * (fun(a) + fun(b));
	for(x = a + krok; x < b; x += krok)
		calka += fun(x);
	calka *= krok;
	return calka;
}

double losuj(double x, double y)
{	
	double a = rand();
	a /= RAND_MAX;
	a *= (y - x);
	a += x;
	return a;
}

double  monte_carlo(double (*fun)(double), double a, double b)
{
	
	double krok;
	krok = fabs((b-a))/n;
	double MIN = 0, MAX = 0;
	double x, y;
	int N = 0;
	for(x = a; x <= b; x += krok)
	{	
		if(fun(x)  > MAX)
			MAX = fun(x);
		else if(fun(x) < MIN)
			MIN = fun(x);
	}	

	for(int i = 0; i < 1000000; i++)
	{	
		x = losuj(a, b);
		y = losuj(MIN, MAX);
		if(y > 0)
			if(fun(x) > y)
				N++;
		if (y < 0)
			if(fun(x) < y)
				N--;
	}	

	return N/1000000. * (b - a) * (MAX - MIN); 
}





int main(int argc, char *argv[]){
	srand(time(NULL));
	double calka, a, b, krok;
	a = -10, b = 1;
	printf("Metoda prostokatow w przedziale od %lf do %lf  calka = %lf\n", a, b, prostakaty(&fun1,a, b));
	printf("Metoda trapezow w przedziale od %lf  do %lf  calka = %lf\n",a, b, trapezy(&fun1, a, b));
	printf("Metoda monte carlo  w przedziale od %lf  do %lf  calka = %lf\n\n",a, b,  monte_carlo(&fun1, a, b));
	a = 2, b = 4;
	printf("Metoda prostokatow w przedziale od %lf do %lf  calka = %lf\n", a, b, prostakaty(&fun2,a, b));
	printf("Metoda trapezow w przedziale od %lf  do %lf  calka = %lf\n",a, b, trapezy(&fun2, a, b));
	printf("Metoda monte carlo  w przedziale od %lf  do %lf  calka = %lf\n\n",a, b,  monte_carlo(&fun2, a, b));
	a = 1, b = 2;
	printf("Metoda prostokatow w przedziale od %lf do %lf  calka = %lf\n", a, b, prostakaty(&fun3,a, b));
	printf("Metoda trapezow w przedziale od %lf  do %lf  calka = %lf\n",a, b, trapezy(&fun3, a, b));
	printf("Metoda monte carlo  w przedziale od %lf  do %lf  calka = %lf\n\n",a, b,  monte_carlo(&fun3, a, b));
	a = -4, b = -2;
	printf("Metoda prostokatow w przedziale od %lf do %lf  calka = %lf\n", a, b, prostakaty(&fun4,a, b));
	printf("Metoda trapezow w przedziale od %lf  do %lf  calka = %lf\n",a, b, trapezy(&fun4, a, b));
	printf("Metoda monte carlo  w przedziale od %lf  do %lf  calka = %lf\n\n",a, b,  monte_carlo(&fun4, a, b));
	return 0;

}
