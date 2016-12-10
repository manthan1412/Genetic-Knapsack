#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float f(float x){
	return 4 / (1 + (x * x));
}

int main(){


	float intervals = 2, pre_result = 0, result, h, i;
	//trapezoidal method
	while(1){
		result = 0;
		h = 1 / intervals;

		for(i = 1; i < intervals; i++)
			result += 2*f(h*i);
		result = (h / 2) * (result + 4 + 2); //f(0) = 4, f(1) = 2

		if(result < pre_result){
			printf("The value of pi using Trapezoidal method is: %.8f,\n", pre_result);
			printf("The number of intervals used is %.0f.\n", intervals);
			break;
		}
		pre_result = result;
		intervals++;
	}

	//simpsons method
	result = 0;
	h = 1 / intervals;
	float temp = 0.0, temp2 = -h/2, last = f(0), current;
	for(i = 1; i <= intervals; i++){
		temp += h;   //calculate i*h
		temp2 += h;   //calculate (((i*h)+((i-1)*h))/2)
		current = f(temp); 
		result += (last + current + 4*f(temp2));  //reduced number of multiplication to one
		last = current;    //saves f(temp) to avoid calculate f(temp - h) in the next iteration
	}
	result *= h; //multiply by h only once after all summation rather than multiplying individually
	result /= 6;
	printf("The value of pi using Simson's method is: %.8f,\n", result);


	//mid point method
    result = 0;
    h = 1/ intervals;
    temp = h/2;   //first value of iteration i.e. (i*h +( hi - 1))/2
    for(i = 1; i <= intervals; i++){
    	result += f(temp);   //removed all the multiplications
    	temp += h;  //converted i*h to addition to increase speed
    }
    result *= h;   //multiply by h only once after all summation rather than multiplying individually
    printf("The value of pi using midpoint method is: %.8f,\n", result);


    //monte carlo method
    float x=0,y=0,ratio,inside_pi=0,area,pi_area;
    int samples = 10000;
	srand(time(NULL));//seed the random number generator with system time

	float max = (float) (RAND_MAX) + 1.0;  //avoid repetitive calculations
    for(i=0;i<samples;i++)
    {
        x=(float)rand()/ max;
        y=(3.99*((float)rand()/(max)));

        temp=f(x);

        if(y<=temp)
            inside_pi++;

    }

    ratio=inside_pi/samples;
    area = 4; // f(a) = 4
    pi_area = ratio*area;
    printf("The value of pi using Monte Carlo method with %d random points is: %.8f,\n", samples, pi_area);

    return 0;
}
