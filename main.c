#include <stdio.h>
#include <unistd.h>
#include <windows.h>

void ShowErrorBox( char* msg, char* windowtitle ) {
    HWND   hwnd  = NULL;         // Use NULL to display the message box as a standalone window
    LPCSTR text  = msg;          // The text to display in the message box
    LPCSTR title = windowtitle;  // The title of the message box
    MessageBox( hwnd, text, title, MB_OK | MB_ICONERROR );
}

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

    int retVal = 0;

    // read and execute from file line by line
    while ( EOF != fscanf( fp, "%256[A-Za-z0-9 -\\:]\n", linebuf ) ) {
        STARTUPINFOA        startupInfo = { 0 };
        PROCESS_INFORMATION processInfo = { 0 };

        // Specify the command-line arguments to be passed to the program
        char* commandLineArgs = linebuf;

        // Initialize the startup info structure
        startupInfo.cb      = sizeof( STARTUPINFO );
        startupInfo.dwFlags = STARTF_USESHOWWINDOW;

        // Trim leading whitespace(s)
        while ( *commandLineArgs == ' ' || *commandLineArgs == '\t' ) {
            commandLineArgs++;
        }

        // Check for specified focus state and handle accordingly
        if ( strncmp( "#NOFOCUS", commandLineArgs, 8 ) == 0 ) {
            // Don't Focus new Window
            startupInfo.wShowWindow = SW_SHOWNOACTIVATE;
            commandLineArgs += 8;
        } else {  // Focus new Window
            if ( strncmp( "#FOCUS", commandLineArgs, 6 ) == 0 ) {
                commandLineArgs += 6;
            }
            startupInfo.wShowWindow = SW_SHOWNORMAL;
        }

        // Trim leading whitespace(s)
        while ( *commandLineArgs == ' ' || *commandLineArgs == '\t' ) {
            commandLineArgs++;
        }

        // Skip empty lines
        if ( strlen( commandLineArgs ) == 0 ) {
            // move fp by 1
            fgetc( fp );
            continue;
        }

        // Launch the process
        if ( CreateProcessA( NULL, commandLineArgs, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo ) ) {
            // printf( "Process started with process ID %lu\n", processInfo.dwProcessId );
            CloseHandle( processInfo.hProcess );
            CloseHandle( processInfo.hThread );
        } else {
            char* errortext = calloc( sizeof( char ), 512 + 1 /* \0 */ );
            // char errortext[512];
            snprintf( errortext,
                      512,
                      "Error launching process: %lu\nFailed command: >%s<\nLine in file: %s",
                      GetLastError(),
                      commandLineArgs,
                      linebuf );
            ShowErrorBox( errortext, "CreateProcess Error" );
            free( errortext );
            retVal = -3;
        }
    }

    // cleanup and close
    fclose( fp );
    return ( retVal );
}
