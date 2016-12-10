#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float find_a(float x){
	// int i = 1;
	// long long i = (long long)x;
	//assuming that maximum limit is 10^9
	// long long min = 1;
	// long long max = 1000000000;
	// long long mid = (min + max) / 2;
	if(x < 25){
		if (x < 2*2)
			return 1;
		if (x < 3*3)
			return 2;
		if (x < 4*4)
			return 3;
		return 4;
	}
	float i = 10.0, sqr_i, sqr_i1;
	sqr_i1 = 25.0;
	for(; ;i+= 5){
		sqr_i = sqr_i1;
		sqr_i1 = i*i;
		if(sqr_i <= x &&  x < sqr_i1)
			return i - 5;
	}
}

int main(){

	float n = 1.0, x, m, mysqrt, x1, c, i, j = 1, total;
	int cnt, temp;
	float a, f_a, y, multiplier;
	printf("\nEnter a number (0 to exit): ");
	scanf("%f", &n);
	while(n > 0){

		x = n;
		m = sqrt(n);


		cnt = 0;
		while(n > 1){
			n /= 4;    //short hand operators are faster
			cnt++;
		}

        //taylor series for square root
        //sqrt(x) = x ^ 1/2
        // sqrt(a + y) = sqrt(a) + y / sqrt'(a) + (y ^ 2) * sqrt''(a)/ 2! + ....
        //where a > y, and a is some perfect square number
		//select a = 1 for taylor series to increase accuracy
		f_a = 1;
		a = 1;

		mysqrt = f_a;
		y = n - a;

		//for taylor series a must be less than y
		while(a < y){
			f_a++;
			a = f_a * f_a;
			y = n - a;
			mysqrt++;
		}

		//calculate all repeated values and save in variable to avoid repeatitive multiplication
		x1 = y / (2 * f_a);
		//printf("%f  + %f \n", a, y);
		multiplier = y / (2 * a);
		mysqrt += x1;
		// j = 1;
		// c = 1 - n;  //to avoid calculating a - n every time
		for(i = -1, j = 2; i > -200; i-= 2, j++){   //i -=2 is work around of 2 * i - 3
			x1 *= i * (multiplier / j);   //j takes care of factorial in denominator in taylor series
			mysqrt += x1;
		}

		temp = 1;
		if(cnt)
			temp <<= cnt; //using bitwise shift to avoid tmp*= 2
		total = mysqrt * (float)temp;
        printf("x=%.6f, n=100\n", n);
		printf("mysqrt(%.6f): %.10f\t", x, total);
		printf("Lib. sqrt(%.6f): %.10f\n", x, m);

		printf("\nEnter a number (0 to exit): ");
		scanf("%f", &n);
	}
	return 0;
}
