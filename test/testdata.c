#include <stdio.h>

typedef struct complex { double real;
	double imag;
} complex, *complex_p;

double get_real(complex c) 
	{ return(c.real); }

double get_imag(complex c) 
	{ return(c.imag); }

complex assign(double r, double i) 
	{ complex c;
	c.real = r;
	c.imag = i;
	return(c);
}

complex cpxAdd(complex x, complex y) 
	{ complex z;
	z.real = x.real + y.real;
	z.imag = x.imag + y.imag;
	return(z);
}

void display(complex x) 
	{printf("\n real=%f, imag=%f \n", x.real, x.imag);}

int main() {
	complex p, q, r; double x, y;
	double r1 = 1.3; double il = 2.4;
	p = assign(r1, il);
	x = get_real(p);
	y = get_imag(p);
	q = assign(x+0.2, y-0.2);
	r = cpxAdd(p,q);
	display(p); display(q); display(r);
	return 1;
}
