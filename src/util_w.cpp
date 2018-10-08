#include "util.h"


bool ezc::exec(std::string cmd) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );


    // Start the child process. 
    if( !CreateProcessA( NULL,   // No module name (use command line)
        (LPSTR)cmd.c_str(),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        return false;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    return true;
}

std::vector<std::string> ezc::getfiles(){
    std::vector<std::string> v;
    WIN32_FIND_DATAA data;
    HANDLE hFile;

    if((hFile = FindFirstFileA("*", &data))){
         do{
            v.push_back(std::string(data.cFileName));
        }while(FindNextFileA(hFile, &data));
    }

   v.shrink_to_fit();
    return v;
}