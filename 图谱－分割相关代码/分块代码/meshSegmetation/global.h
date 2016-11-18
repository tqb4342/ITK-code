#ifndef GLOBAL_H
#define GLOBAL_H



#define MaxBrightness 255
#define SHORT_MAX 0xffff

#define EPSILON1  1e-3
#define EPSILON2  1e-5

#define PI 3.14159265;

// Minimum and maximum of three variables.
#define MIN3( X, Y, Z )    ( (X)<(Y) ? ( (X)<(Z) ? (X):(Z) ):( (Y)<(Z) ? (Y):(Z) ) )
#define MAX3( X, Y, Z )    ( (X)>(Y) ? ( (X)>(Z) ? (X):(Z) ):( (Y)>(Z) ? (Y):(Z) ) )

inline int 	sign( double x )  { return (x<0) ? (-1) : (x>0); }


template<typename T>
void freeMatrix(T ***m, int width, int height)
{
	for(int i=0; i<width; i++ )
	{
		for(int j=0; j<height; j++ )
		{
			delete[] (m[i][j]);
		}
	}
}

#endif /* GLOBAL_H */