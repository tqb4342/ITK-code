#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;


bool AffineFile( const int numFile );
bool BSplineFile( const int numFile );



int main(int argc, char *argv[])
{
	//const int numFile = 30;
	const int numFile = atoi( argv[1] );
	
	
	AffineFile( numFile );
    BSplineFile( numFile );
	
	
	return 0;
}


bool AffineFile( const int numFile )
{
	char *inputFile = NULL;
	char *outputFile = NULL;
	for( int i=0; i<numFile; i++ )
	{
		ostringstream ss;
	    string datasetFilename;
	
	    char *baseName = "Affine_Iter3_";	
	    ss << baseName << i	 << ".txt";
		datasetFilename = ss.str();
		inputFile = new char[datasetFilename.size()+1];
		strcpy( inputFile, datasetFilename.c_str() );
		printf("\n\nInput File:\t%s\n", inputFile);	
		
		
		// Write the output image. 
        ostringstream ss2;
        string datasetFilename2;	
		
		char *baseName2 = "char/Affine_Iter3_";
        ss2 << baseName2 << i << ".txt";
        datasetFilename2 = ss2.str();
        outputFile = new char[datasetFilename2.size()+1];
        strcpy( outputFile, datasetFilename2.c_str() );		
        printf("Output File:\t%s\n", outputFile);
		
		
		ifstream ifs( inputFile );	
		ofstream ofs( outputFile );
		// When the OFF file is successfully opened.
        if( ifs.is_open() && ofs.is_open() )
	    {
			string inputLine;
			for( int j=0; j<23; j++ )
	        {
				getline( ifs, inputLine );
                
				ofs << inputLine << endl;
				
			    //cout << endl << inputLine << endl;
		    }
			
			ofs << "(FinalBSplineInterpolationOrder 3)" << endl;
			ofs << "\n// Resampler specific" << endl;
			ofs << "(Resampler \"DefaultResampler\")" << endl;
			
            ofs << "(DefaultPixelValue -1024.000000)" << endl;
			ofs << "(ResultImageFormat \"nrrd\")" << endl;
			ofs << "(ResultImagePixelType \"short\")" << endl;
			ofs << "(CompressResultImage \"false\")" << endl;    
		}
		else
	    {
		    printf("\n\nThe File \"%s and %s\" can not be read correctly!!!\n\n", inputFile, outputFile);
			
		    ifs.close();	
			ofs.close();
	        return 1;
	    }
		
		ifs.close();
		ofs.close();
	}
	
	
	return true;
}












bool BSplineFile( const int numFile )
{
	char *inputFile = NULL;
	char *outputFile = NULL;
	for( int i=0; i<numFile; i++ )
	{
		ostringstream ss;
	    string datasetFilename;
	
	    char *baseName = "BSpline_Iter3_";	
	    ss << baseName << i	 << ".txt";
		datasetFilename = ss.str();
		inputFile = new char[datasetFilename.size()+1];
		strcpy( inputFile, datasetFilename.c_str() );
		printf("\n\nInput File:\t%s\n", inputFile);	
		
		
		// Write the output image. 
        ostringstream ss2;
        string datasetFilename2;	
		
		char *baseName2 = "char/BSpline_Iter3_";
        ss2 << baseName2 << i << ".txt";
        datasetFilename2 = ss2.str();
        outputFile = new char[datasetFilename2.size()+1];
        strcpy( outputFile, datasetFilename2.c_str() );		
        printf("Output File:\t%s\n", outputFile);
		
		
		ifstream ifs( inputFile );	
		ofstream ofs( outputFile );
		// When the OFF file is successfully opened.
        if( ifs.is_open() && ofs.is_open() )
	    {
			string inputLine;
			for( int j=0; j<29; j++ )
	        {
				getline( ifs, inputLine );
                
				ofs << inputLine << endl;
				
			    //cout << endl << inputLine << endl;
		    }
			
			ofs << "(FinalBSplineInterpolationOrder 3)" << endl;
			ofs << "\n// Resampler specific" << endl;
			ofs << "(Resampler \"DefaultResampler\")" << endl;
			
            ofs << "(DefaultPixelValue -1024.000000)" << endl;
			ofs << "(ResultImageFormat \"nrrd\")" << endl;
			ofs << "(ResultImagePixelType \"short\")" << endl;
			ofs << "(CompressResultImage \"false\")" << endl;   
		}
		else
	    {
		    printf("\n\nThe File \"%s and %s\" can not be read correctly!!!\n\n", inputFile, outputFile);
			
		    ifs.close();	
			ofs.close();
	        return 1;
	    }
		
		ifs.close();
		ofs.close();
	}
	
	
	return true;
}
