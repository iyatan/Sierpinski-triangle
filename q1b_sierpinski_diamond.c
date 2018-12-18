#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum // datatype bool
{
    true = 1, false = 0
} bool;


bool* buildShape( int height,int width );
void printShape( bool* fr,int height,int width );
void multiply( bool* fr,int upperRow,int upperC,int upperOShapeH,int width );

int main( int argc,char* argv[] ){
    int height = atoi( argv[ 1 ] );
    int level = atoi( argv[ 2 ] );
    int halfH = ( height + 1 ) / 2;
    
    if( argc != 3 ){     //Checking if we have exactelly 2 arguments after the program name
        printf( "ERROR: Wrong number of arguments. Two required.\n" );
        return 0;
    }

    if( !( ( height + 1 ) && !( ( height + 1 ) & ( height ) ) )  || ( int )log2( height + 1 ) < level || level < 1 ){ // checking if H allow us to pefectely divide
        printf( "ERROR: Height does not allow evenly dividing requested number of levels.\n" );
        return 0;
    }

    bool* fractal = buildShape( halfH,height ); //by printing H*H chars we are printing the width
    
    int fractalHeight = halfH; //height at the time
    
    for( int i = 1; i < level; i++ ){
        multiply( fractal,0,halfH - 1,fractalHeight,height ); //
        fractalHeight /= 2; //going to lower level
    }
    
    printShape( fractal,halfH,height );

    free( fractal );
    fractal = NULL;
    return 0;
}

bool* buildShape( int height,int width ) {
    //representing in 2d
    bool ( *fractal )[ width ] = malloc( height * sizeof( *fractal ) ); 
    
    int strss = 1; //there is only one character in the very first row
    
    for( int i = 0; i < height; i++ ){
        int offset = 0;
        for( int j = 0; j < height - 1 - i; j++,offset++ ) fractal[ i ][ offset ] = false;  //left side
        for( int j = 0; j < strss; j++,offset++ )          fractal[ i ][ offset ] = true;   //strss
        for( int j = 0; j < height - 1 - i; j++,offset++ ) fractal[ i ][ offset ] = false;  //right side
        
        strss += 2;
    }
    return *fractal; //returning the pointer to be modified
}

void printShape( bool* fr,int height,int width ){
    for( int i = 0; i < height; i++ ){
        for( int j = 0; j < width; j++ ){
            //print star if the value at index [ i ][ j ] is true, space otherwise
            printf( *( ( fr + i * width ) + j ) == true ? "*" : " " );
            //printf( fr[ i ][ j ] == true ? "*" : " " );
        }
        printf( "\n" );
    }
    
    for( int i = height - 2; i >= 0; i-- ) {
        for( int j = 0; j < width; j++ ){
            printf( *( ( fr + i * width ) + j ) == true ? "*" : " " );
        }
        printf( "\n" );
    }
}

void multiply( bool* fr,int upperRow,int upperC,int upperOShapeH,int width ){
    int spaces = 1; //all empty triangles start with one space in the bottom most row
    int leftIndex = upperC;
    
    for( int i = 0; i < upperOShapeH / 2; i++ ) {
        for( int j = 0; j < spaces; j++ ){
            *( ( fr + ( upperRow + ( upperOShapeH - 1 ) - i ) * width ) + ( leftIndex + j ) ) = false;
        }
        leftIndex--; //go to left
        spaces += 2; 
    }
    
    if( upperRow + upperOShapeH - 1 != ( ( width + 1 ) / 2 ) - 1 ){
        //call itself on sides
        multiply( fr,upperRow + upperOShapeH,upperC - upperOShapeH,upperOShapeH,width );
        multiply( fr,upperRow + upperOShapeH,upperC + upperOShapeH,upperOShapeH,width );
    }
}

