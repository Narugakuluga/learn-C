#include <stdio.h>
#include <math.h>

int math(void);
double N(double P,double p2);

int main(void){
    int x;
    while(1){
        x = math();
        if (x == 0){
            break;
        }
    }
    return 0;
}

int math(void){
    double p,n;
    int t;
    printf("Probability[%%] : ");
    scanf("%lf",&p);
    p /= 100;
    if (p >= 1.0)
        p = 1.0;

    printf("N of roll : ");
    scanf("%lf",&n);
    printf("Probability of at least you got one : %lf%%\n",100 * (1 - (pow(1-p,n))));
    printf("50%% : %.0lf    75%% : %.0lf    90%% : %.0lf    99%% : %.0lf\n",N(0.50,1-p),N(0.75,1-p),N(0.90,1-p),N(0.99,1-p));

    while((t = getchar()) != EOF && t != '\n'){

    }
    
    printf("Continue? y/n : ");
    t = getchar();
    if (t == 'y'){
        printf("\n");
        return 1;
    } else {
        return 0;
    }
}

double N(double P,double p2){
    return log(1.0 - P) / log(p2);
}
