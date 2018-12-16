#include <stdio.h>
#include <math.h>
#include <string.h>

int get_val(char ch)
{
 int x =  (ch - 'A')+1;
 printf("%d\n", x);
 return x;
}

int gcd(int A, int B) {
    
    /*int i = 0;
    
    for(i = A; i >0 ; i--)
    {
        if(A%i == 0 && B%i==0)
         break;
         
    }*/
    
    
    printf("%d %d \n", A, B);
    if(A = 0 || B == 0)
        return 0;
    
    if(A == B)
        return A;
    
    if(A > B)
        return gcd(A-B, B);
    
    return gcd(A, B-A);
    
}


int main()
{
    gcd(4,6);
    return 0;
}