#include <stdio.h>
#include <unistd.h>
#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
    FILE* fp;
    char linebuf[256 + 1] = { 0 };
    char  path[MAX_PATH];

    //get and chdir executable dir
    GetModuleFileName( NULL, path, MAX_PATH );
    char* dirsep = strrchr( path, '\\' );
    if ( NULL != dirsep ) {
        *dirsep = 0;
        if ( 0 > chdir( path ) ) {
            perror( "chdir() not successful" );
            return -1;
        }
    }

    //open cfg file
    fp = fopen( "winrun.cfg", "r" );
    if ( NULL == fp ) {
        perror( "Could not open file winrun.cfg" );
        return -2;
    }

    //read and execute from file line by line
    while ( 0 < fscanf( fp, "%256[A-Za-z0-9 -\\:]\n", linebuf ) ) {
        printf( "> %s\n", linebuf );
        if ( -1 == system( linebuf ) ) {
            perror( "ERROR Executing system()" );
            fclose( fp );
            return -3;
        }
    }

    // cleanup and close
    fclose( fp );
    exit( 0 );
}
