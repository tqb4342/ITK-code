#include "Traditional_Regi_Elastix.h"


#include <fstream>
#include <time.h>



int main(int argc, char *argv[])
{	
	printf("\n\n*************************************************************************************\n");
	printf("*************************************************************************************\n");
	printf("Main Sart!!!\n\n\n");
	
	
//******************************************************************************************************
// Important Parameters!!!
//******************************************************************************************************	
	const int numSamples = 30;
    cout << "numSamples:\t" << numSamples;
	
	
	const int maxIteration = 5;
	
	
	
	
	
	
	
	bool flag = true;
	bool USE_HEALTHY_ATLAS_AS_REF = false;


    ofstream ofs( "Reconstruction_error.csv" );	
	ofstream ofsTIME( "Time.csv" );	
    if( ofs.is_open() )
	{
		ofs << maxIteration << endl;
		ofsTIME << maxIteration << endl;
		
		
		clock_t start, end;
	    start = clock();		
		
		
	    for( int i=4; i<maxIteration; i++ )
	    {
			clock_t start2, end2;
	        start2 = clock();				
			
			ofs << i+1 << "\t";
			

			flag = Traditional_Regi_Elastix( i, numSamples, USE_HEALTHY_ATLAS_AS_REF, ofs);
			
			if( false == flag )
			{
				printf("\n\nThere are problems with Traditional_Regi_Elastix()!!!!!\n\n");
				break;
			}
		
			
			end2 = clock();
	        double duration2 = (double)( end2 - start2 ) / (double)CLOCKS_PER_SEC;	
			ofsTIME << duration2 << endl;
	        printf("\n\nTraditional_Regi_Elastix for Input[%d] in %f seconds.\n\n", i+1, duration2);
		}
		
		end = clock();
	    double duration = (double)( end - start ) / (double)CLOCKS_PER_SEC;	
	    printf("\n\nTraditional_Regi_Elastix End in %f seconds.\n\n", duration);
		printf("\n\nTraditional_Regi_Elastix Per Input in %f seconds.\n\n", duration/(double)(maxIteration));
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
