#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

  // Verifying that we have exactely 2 arguments(1 after the name)  

    if(argc != 2){
        printf("Error: Wrong number of arguments.One required\n");
        return -1;
    }

    // Verifying that the height is a positive integer
    
    int x = atoi(argv[1]);
    if((x<0) || (x%2)==0) {
        printf("ERROR: Bad argument. Height must be positive odd integer.");
        return -1;

    }
    
   // Printing the diamond


    int n, c, k, space = 1;
    n = (atoi(argv[1]))/2 +1; // Knowing that the part after the . wouldnt be considered

    space = n - 1;
    //Upper part
    
    for (k = 1; k <= n; k++)
    {  
        for (c = 1; c <= space; c++)
        printf(" ");
        
        space--;
        
        for (c = 1; c <= 2*k-1; c++)
        printf("*");
        
        printf("\n");     
    }    
    //Lower part
    space = 1;  
    for (k = 1; k <= n - 1; k++)
    {   
        for (c = 1; c <= space; c++)
        printf(" ");      
        space++;

        for (c = 1 ; c <= 2*(n-k)-1; c++)
        printf("*");       
        printf("\n");    
        
    }
    
    return 0; 

    
}


