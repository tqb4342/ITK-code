#include "MAS_Elastix.h"


#include <fstream>
#include <time.h>



int main(int argc, char *argv[])
{	
	printf("\n\n*************************************************************************************\n");
	printf("*************************************************************************************\n");
	printf("Main Sart!!!\n\n\n");
	
 
	const int numSamples = 1;
 
	
	
	
	
	
	//int testingIndex;
	ofstream ofs( "Reconstruction_error.csv" );	
	ofstream ofsTIME( "Time.csv" );		
	
 	
    // When the OFF file is successfully opened.
	bool flag = true;
	bool USE_HEALTHY_ATLAS_AS_REF = false;
    if( ofs.is_open() )
	{
		clock_t start, end;
	    start = clock();		
		
 
	    MAS_Elastix( numSamples, USE_HEALTHY_ATLAS_AS_REF);		
		
		
		end = clock();
	    double duration = (double)( end - start ) / (double)CLOCKS_PER_SEC;	
	    printf("\n\nMAS_Elastix End in %f seconds.\n\n", duration);
		printf("\n\nMAS_Elastix Per Image in %f seconds.\n\n", duration/(double)(numSamples));
	}
	else
	{
		printf("\n\nThe file \"Reconstruction_error.csv\" can not be read correctly!!!\n\n");
		ofs.close();	
	    return 1;
	}	 
	
	
	
	printf("\n\nMain End!!!\n");
	printf("*************************************************************************************\n");
	printf("*************************************************************************************\n\n");
	
	return 0;
}