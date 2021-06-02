
/** 
 * 2018. Nov. 16th- 1D random walks
 * 
**/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "/home/js131/work/utils/mt19937-64/mt19937-64.c"  // You need to have this in your local directory!! with correct folder

/** 
* Generation of random number seed, get a current time in micri-second unit
**/
int gus() {
	struct timeval tp;
	gettimeofday(&tp,0);
	return tp.tv_usec;
}

int main(){
	unsigned long long idum;
	idum=gus();
	init_genrand64(idum);


	int total; //total number of searching events
	
	int n1 ; //Coordinate of Random walker
	int m1 ;// the position of target
	double k0; // hopping rate on the lattice along one direction.
	double ks;  //total transition rate
	double rr; //random number between [0, 1]

	int L1 ;// lattice size
	
	

	FILE *eqFile ;
	FILE *timeFile ;
		timeFile=fopen("time.txt", "w");
		eqFile=fopen("eq.txt","w");

	int i, j;
	double dt;
	double t0;
	double tt ;
	double t_sum ;
	
	L1=20 ; //lattice size
	m1=L1 ; //target is at the right end
	total = 1000; // the number of simulation runs.
	
	k0=1.0;
	t_sum= 0.0;	

	for (j=0;j<total; j++){
		tt=0.0;
		n1=1; // Initial Position

			for (i=0;;i++){
				
					
							
				if ( n1==m1 ) {  //if the random walker arrive at the taget site
					fprintf(timeFile, "%f \n", tt); // save the arrival time and the loop ends
					t_sum= t_sum+ tt;
						break;			} 
						
						
				
								
				if( n1>1 && n1< L1 ) {   //random walker is not at the end of the lattice (1<n1<L)- there are two ways to jump, right or left.
					ks=2.*k0; //right+ left
					t0=1.0/ks;  
					rr=genrand64_real2();  
					dt=-t0*log(rr);
					tt=tt+dt;
					rr=genrand64_real2();
							if(rr< 0.5){n1=n1+1;}  //to the right
							else {n1=n1-1;}	   // to the left
					}
					
					
				else if(n1==1) {  // at the left end, ther is only one way to jump (to the right)
					ks=1.*k0;  //right
					t0=1.0/ks;
					rr=genrand64_real2();
					dt=-t0*log(rr);
					tt=tt+dt;
					n1=n1+1;
					}
				
					
				else if(n1==L1) {  // at the right end, ther is only one way to jump (to the left)
					ks=k0;
					t0=1.0/ks;
					rr=genrand64_real2();
					dt=-t0*log(rr);
					tt=tt+dt;
					n1=n1-1;
					}
				}
	}
	
	fclose(timeFile);
	fclose(eqFile);
	printf ("average time= %f", t_sum/total);
	return 0 ;
	
}
		
