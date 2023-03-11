#include <stdio.h>
#include <unistd.h>
#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int nCmdShow ) {
    FILE* fp;
    char  linebuf[256 + 1] = { 0 };
    char  path[MAX_PATH];

    // get and chdir executable dir
    GetModuleFileName( NULL, path, MAX_PATH );
    char* dirsep = strrchr( path, '\\' );
    if ( NULL != dirsep ) {
        *dirsep = 0;
        if ( 0 > chdir( path ) ) {
            perror( "chdir() not successful" );
            return -1;
        }
    }

    // open cfg file
    fp = fopen( "winrun.cfg", "r" );
    if ( NULL == fp ) {
        perror( "Could not open file winrun.cfg" );
        return -2;
    }

    // read and execute from file line by line
    while ( 0 < fscanf( fp, "%256[A-Za-z0-9 -\\:]\n", linebuf ) ) {
        STARTUPINFOA        startupInfo = { 0 };
        PROCESS_INFORMATION processInfo = { 0 };

        // Specify the command-line arguments to be passed to the program
        char* commandLineArgs = linebuf;

        // Initialize the startup info structure
        startupInfo.cb      = sizeof( STARTUPINFO );
        startupInfo.dwFlags = STARTF_USESHOWWINDOW;

        // Focus new Window
        // startupInfo.wShowWindow = SW_SHOWNORMAL;

        // Don't Focus new Window
        startupInfo.wShowWindow = SW_SHOWNOACTIVATE;

        // Launch the process
        if ( CreateProcessA( NULL, commandLineArgs, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo ) ) {
            printf( "Process started with process ID %lu\n", processInfo.dwProcessId );
            CloseHandle( processInfo.hProcess );
            CloseHandle( processInfo.hThread );
        } else {
            printf( "Error launching process: %lu\n", GetLastError() );
            fclose( fp );
            return ( -3 );
        }
    }

    // cleanup and close
    fclose( fp );
    return ( 0 );
}
