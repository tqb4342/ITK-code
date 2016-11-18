#include "utils.h"


bool readInputShape( char *inputFile, VectorXf& inputShape )
{
	ifstream ifs( inputFile );	
	// When the OFF file is successfully opened.
	if( ifs.is_open() ) 
	{		
		//-------------------------------------- 
		// Reading File Header.
		//-------------------------------------- 
		string inputLine;
		ifs >> inputLine;
		
		if( "OFF" == inputLine ) 
		{
			int numVertices, numFaces, numEdges;
			
			// numEdges is present but ignored in this format
			ifs >> numVertices >> numFaces >> numEdges; 
			
			// Allocate and initialize space for the Data Matrix.
			inputShape = VectorXf::Zero( 3*numVertices );  		
			//cout << "\np = " << 3*numVertices << endl;
			
			// Read every Vertex.
			float x, y, z;
			if( numVertices>0 ) 
			{
				for (int i = 0, j=0; i<numVertices; i++) 
				{
					ifs >> x >> y >> z;
					//printf("Current Vertex-xyz(%d):\t[%f, %f, %f]\n", i2+1, x, y, z);
					inputShape[j++] = x;
					inputShape[j++] = y;
					inputShape[j++] = z;
					//printf("Current inputShape(%d):\t[%f, %f, %f]\n", i+1, 
					        //inputShape(j-3), inputShape(j-2), inputShape(j-1));
				}
			}
			else  
			{
				printf("\n\nThis Input Shape file has empty _numVertices_.\n\n");
				ifs.close();	
	            return false;			        
			}
		}			
		else
		{
			printf("\n\nThis Input Shape file is NOT a correct OFF file!!!\n\n");
			ifs.close();	
	        return false;
	    }
	}
	else
	{
		printf("\n\nThis Input Shape file can not be read correctly!!!\n\n");
		ifs.close();	
	    return false;
	}

	ifs.close();	
	return true;	
}



bool readTrainingData( MatrixXf &X, char *baseName, int numTrainData , int& cols, int& numSuccessFile)
{
	// Record the read status.
	numSuccessFile = 0;
	
	// In case missing training data in middle (e.g. F1, F2, F3, F5).
	int currentIndex = 0;  
	for( int i=0; i<numTrainData; i++ )
	{
		ostringstream ss;
		string datasetFilename;
		
		ss << baseName << i << ".off";
	    datasetFilename = ss.str();
	    const char *inputFile = datasetFilename.c_str();
	    printf("\nInput File:\t%s\n\n", inputFile);

	    ifstream ifs( inputFile );
	    // When the OFF file is successfully opened.
	    if( ifs.is_open() ) 
	    {		
	        //-------------------------------------- 
	        // Reading File Header.
	        //-------------------------------------- 
		    string inputLine;
		    ifs >> inputLine;
		
		    if( "OFF" == inputLine ) 
		    {
			    int numVertices, numFaces, numEdges;
			
			    // numEdges is present but ignored in this format
			    ifs >> numVertices >> numFaces >> numEdges; 
				
				if( 0==i )
				{
	                cols = 3*numVertices;  // 3*k
			        //cout << "\np = " << cols << endl;
			
			        // Allocate and initialize space for the Data Matrix.
			        X = MatrixXf::Zero(numTrainData, cols);	
				}
				
                if( 3*numVertices!=cols )	
                {
					printf("\n\nThis Training Data (%s) has inconsistent number of Vertices.\n\n", inputFile);
					printf("\n\nCompare:\t[%d, %d]\n\n", 3*numVertices, cols);
					
					continue;
				}					
			
			    // Read every Vertex.
			    float x, y, z;
			    if( numVertices>0 ) 
			    {
					numSuccessFile++;
					
				    for (int i2 = 0, j=0; i2 < numVertices; i2++) 
				    {
				        ifs >> x >> y >> z;
  				        //printf("Current Vertex-xyz(%d):\t[%f, %f, %f]\n", i2+1, x, y, z);
					    X( currentIndex, j++) = x;
					    X( currentIndex, j++) = y;
					    X( currentIndex, j++) = z;
					    //printf("Current Vertex2-X(%d):\t[%f, %f, %f]\n", i2+1, 
						        //X( currentIndex, j-3), X( currentIndex, j-2), X( currentIndex, j-1));
				    }
					currentIndex++;
			    }
				else  
		        {
					// If the first Training file has empty _numVertices_.
                    if( 0==i )
			        {
						printf("\n\nThe first Training file has empty _numVertices_.\n\n");
						ifs.close();
				        return false;
			        }
					else
			        {
						printf("\n\nThis Training file(%s) has empty _numVertices_.\n\n", inputFile);
			        }
				}  
			}
			else
			{
				// If the first Training file is NOT a correct OFF file.
				if( 0==i )
				{
					printf("\n\nThe first Training file is NOT a correct OFF file.\n\n");
					ifs.close();
					return false;
				}	
                else
			    {
				    printf("\n\nThis Training file(%s) is NOT a correct OFF file.\n\n", inputFile);
			    }				
			}
	    }
		else
		{
			// If the first Training file can not be read correctly.
            if( 0==i )
			{
				printf("\n\nThe first Training file can not be read correctly.\n\n");
				ifs.close();
				return false;
			}
			else
			{
				printf("\n\nThis Training file(%s) can not be read correctly.\n\n", inputFile);
			}
		}
	    ifs.close();
	}
	
	return true;		
}






bool savePointSet2Off( VectorXf mu, char *outputFile, char *refFile )	
{
	ifstream ifs( refFile );
	ofstream ofs( outputFile );
	
	// When the OFF files are successfully opened.
	if( ifs.is_open() && ofs.is_open() ) 
	{		
		//-------------------------------------- 
		// Write File Header.
		//-------------------------------------- 
		string inputLine;
		ifs >> inputLine;
		ofs << "OFF\n";
		
		int numVertices, numFaces, numEdges;			
		ifs >> numVertices >> numFaces >> numEdges; 
		ofs << numVertices << " " << numFaces << " " << numEdges << "\n"; 
		
		// Save all Vertices' info from _VectorXf_.
		float x, y, z;
		for (int i=0, j=0; i<numVertices; i++) 
		{
			ifs >> x >> y >> z;
			
			ofs << mu[j++] << " "; 
			ofs << mu[j++] << " ";
			ofs << mu[j++] << " " << "\n";
		}	
		
		// Save all Faces' info from refFile.
		int f0, f1;
        for (int i=0; i<numFaces; i++) 
		{
			//ifs >> f0 >> f1 >> f2 >> f3; 
            //ofs << f0 << " " << f1 << " " << f2 << " " << f3 << " " << "\n"; 	
			ifs >> f0;
			ofs << f0 << " ";
			for( int j=0; j<f0; j++ )
			{
				ifs >> f1; 	
                ofs << f1 << " ";				
			}				
			ofs << "\n";
		}		
	}
	else
	{
		printf("\n\nThe refFile(%s) can not be read correctly!!!   OR\n\n", refFile);
		printf("\n\nThe outputFile(%s) can not be Created Successfully!!!\n\n", outputFile);
		ifs.close();
		ofs.close();	
		
	    return false;
	}
	
	ifs.close();
	ofs.close();
	
    return true;		
}

bool saveMatrixX2Off( MatrixXf X, char *baseName )
{
	RowVectorXf mu;
	
	for( int i=0; i<X.rows() ; i++ )
	{
		ostringstream ss;
	    string datasetFilename;
		
		ss << baseName << i << ".off";
	    datasetFilename = ss.str();
		char *outputFile = new char[datasetFilename.size()+1];
		strcpy( outputFile, datasetFilename.c_str() );
		
	    printf("\nOutput File:\t%s\n\n", outputFile);
		
        mu = X.row( i );
	    savePointSet2Off( mu, outputFile, "training/liver-0.off" );		
	}
}