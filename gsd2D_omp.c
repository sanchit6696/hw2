#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"
#include <omp.h>

int main (int argc, char **argv)
{
    long  i, j;
    double *rm;
    double prod;
    long p, passes;
    int nthreads=8;
    if (argc != 2) {
        fprintf(stderr, "Function needs vector size as input arguments!\n");
        abort();
    }
    int N=atol(argv[1]);
    double invh=1.0/((N+1)*(N+1));
    double *u = (double *) calloc((N+1)*(N+1),sizeof(double));
    double *f = (double *) calloc((N+1)*(N+1),sizeof(double));
    int len=(N+1)*(N+1);
    for(int i=0;i<len;i++)
        f[i]=1;
    timestamp_type time1, time2;
    
    double res=sqrt(len);
    printf("%f\n",res);
    int co=0;
    get_timestamp(&time1);
    
    while(res>sqrt(len)*pow(10,-4)&&co<1000){
    #pragma omp parallel for num_threads(nthreads) default(none) private(i) shared(nthreads,u,len,f,invh,N)
        for (i = 0; i < len; ++i) {
            int r=i/(N+1);
            int c=i-r*(N+1);
            if(r==0||r==N||c==0||c==N)
            {}
            else{

                if((r+c)%2==0)
                {                  
                    u[i]=.25*(invh*f[i]+u[(r-1)*(N+1)+c]+u[(r)*(N+1)+c-1]+u[(r+1)*(N+1)+c]+u[(r)*(N+1)+c+1]);
                    //printf("%f \n",u[i]);
                }
            }
            
            
        }
        #pragma omp parallel for default(none) private(i) shared(nthreads,u,len,f,invh,N)
        for (i = 0; i < len; ++i) {
            int r=i/(N+1);
            int c=i-r*(N+1);
            if(r==0||r==N||c==0||c==N)
            {}
            else{
                if((r+c)%2==1)
                    u[i]=.25*(invh*f[i]+u[(r-1)*(N+1)+c]+u[(r)*(N+1)+c-1]+u[(r+1)*(N+1)+c]+u[(r)*(N+1)+c+1]);
            }
            
            
        }
        
        co=co+1;
        double ressum=0;
#pragma omp parallel for reduction (+:ressum) default(none) private(i) shared(u,len,f,invh,N)

        for (i = 1; i <len; ++i) {
            int r=i/(N+1);
            int c=i-r*(N+1);
            if(r==0||r==N||c==0||c==N)
            {}
            else
                ressum=ressum+pow(len*(4*u[i]-(u[(r-1)*(N+1)+c]+u[(r)*(N+1)+c-1]+u[(r+1)*(N+1)+c]+u[(r)*(N+1)+c+1]))-f[i],2);
            
        }
        
        
        res=sqrt(ressum);
        printf("%f\n",res/sqrt(len));
        /*
        for(i=0;i<len;i++){
            u1[i]=u2[i];
        }
        */
    }
    get_timestamp(&time2);
    double elapsed = timestamp_diff_in_seconds(time1,time2);
    printf("Time elapsed is %f seconds.\n", elapsed);
    /*
     printf("Inner product is %f.\n", prod);
     
     printf("%f GB/s\n", 4*n*sizeof(double)*passes/1e9/elapsed);
     printf("%f GFlops/s\n", 2*n*passes/1e9/elapsed);*/
    
    free(u);
    free(f);
    return 0;
}

