#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


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

double prostakaty(double a, double b, int i)
{
	double krok;
	krok = fabs((b-a))/100000;
	double calka, x = a;
	calka = 0;
	if(i == 1)
	{
		while(b > x)
		{
			calka+= krok*fun1(x);
			x += krok;
		}
	}	
	else if(i == 2)
	{
		while(b > x)
		{
			calka+= krok*fun2(x);
			x += krok;
		}
	}	
	else
	{
		while(b > x)
		{
			calka+= krok*fun3(x);
			x += krok;
		}
	}	
	return calka;

}

double trapezy(double a, double b, int i)
{
	
	double krok;
	krok = fabs((b-a))/100000;
	double calka, x = a;
	
	if(i == 1)
	{
		calka = 0.5 * x * (fun1(a) + fun1(b));
		for(x = a + krok; x < b; x += krok)
			calka += fun1(x);
	}
	else if(i == 2)
	{
		calka = 0.5 * x * (fun2(a) + fun2(b));
		for(x = a + krok; x < b; x += krok)
			calka += fun2(x);
	}
	else
	{
		calka = 0.5 * x * (fun3(a) + fun3(b));
		for(x = a + krok; x < b; x += krok)
			calka += fun3(x);
	}
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

double  monte_carlo(double a, double b, int i)
{
	
	double krok;
	krok = fabs((b-a))/100000;
	double MIN = 0, MAX = 0;
	double x, y;
	double ff;
	int N = 0;
	if(i == 1)
	{
		for(x = a; x <= b; x += krok)
		{	
			if(fun1(x)  > MAX)
				MAX = fun1(x);
			else if(fun1(x) < MIN)
				MIN = fun1(x);
		}	
	
		for(int i = 0; i < 1000000; i++)
		{	
			x = losuj(a, b);
			y = losuj(MIN, MAX);
			if(y > 0)
				if(fun1(x) > y)
					N++;
			if (y < 0)
				if(fun1(x) < y)
					N--;
		}	
	}
	
	else if(i == 2)
	{
		for(x = a; x <= b; x += krok)
		{	
			if(fun2(x)  > MAX)
				MAX = fun2(x);
			else if(fun2(x) < MIN)
				MIN = fun2(x);
		}	
		for(int i = 0; i < 1000000; i++)
		{	
			x = losuj(a, b);
			y = losuj(MIN, MAX);
			if(y > 0)			
				if(fun2(x) > y)
					N++;
			if (y < 0)
				if(fun2(x) < y)
					N--;
		}	
	}
	else
	{
		for(x = a; x <= b; x += krok)
		{	
			if(fun3(x)  > MAX)
				MAX = fun3(x);
			else if(fun3(x) < MIN)
				MIN = fun3(x);
		}	
		for(int i = 0; i < 1000000; i++)
		{	
			x = losuj(a, b);
			y = losuj(MIN, MAX);
			if(y > 0)
				if(fun3(x) > y)
					N++;
			if (y < 0)
				if(fun3(x) < y)
				N--;
		}
	}	
	return N/1000000. * (b - a) * (MAX - MIN); 
}





int main(int argc, char *argv[]){
srand(time(NULL));
double calka, a, b, krok;
a = -1, b = 1;
for(int i = 1; i <= 3; i++)
{
	{
		printf("Metoda prostokatow w przedziale od %lf do %lf  calka = %lf\n", a, b, prostakaty(a, b, i));
		printf("Metoda trapezow w przedziale od %lf  do %lf  calka = %lf\n",a, b, trapezy(a, b, i));
		printf("Metoda monte carlo  w przedziale od %lf  do %lf  calka = %lf\n\n",a, b,  monte_carlo(a, b , i));
	}
	a += 2;
	b += 3;
}
return 0;


}
