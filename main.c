#include <stdio.h>
#include <unistd.h>

//run contents of winrun.cfg line by line on command interpreter
int main(int argc, char *argv[])
{
    //create local variables
    FILE * fp;
    char * linebuf[ 256+1 ] = { 0 };

    //get and chdir executable dir
    char *dirsep = strrchr( argv[0], '\\' );
    if ( NULL != dirsep )
    {
        *dirsep=0;
        if ( 0 > chdir( argv[0] ) )
        {
            perror( "chdir() not successful" );
            return -1;
        }
    }

    //open cfg file
    fp = fopen("winrun.cfg", "r");
    if ( NULL == fp )
    {
        perror("Could not open file winrun.cfg");
        return -2;
    }

    //read and execute from file line by line
    while( 0 < fscanf( fp , "%256[A-Za-z0-9 -\\:]\n", &linebuf ) )
    {
        printf("> %s\n", linebuf);
        if ( -1 == system( linebuf ))
        {
            perror("ERROR Executing system()");
            fclose( fp );
            return -3;
        }
    }

    //cleanup and close
    fclose( fp );
    exit( 0 );
}
