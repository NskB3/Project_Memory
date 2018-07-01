#include <stdio.h>

#include <string.h>

#include <Windows.h>

#include <tlhelp32.h>

DWORD* pid_grabber(const char* proc_name, DWORD *pid)

{

    PROCESSENTRY32 pe32;

    HANDLE handler;

    

    pe32.dwSize = sizeof(pe32);

    handler = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(handler != INVALID_HANDLE_VALUE)

    {

        if(Process32First(handler, &pe32) == TRUE)

        {

            do

            {

                if(strcmp(pe32.szExeFile, proc_name) == 0)

                {

                    break;

                }

            }while(Process32Next(handler, &pe32) == TRUE);

        }

    }

    *pid = pe32.th32ProcessID;

    return pid;

    CloseHandle(handler);

}

DWORD* read_data(DWORD pid, DWORD* data, const void* base_addr)

{

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if(process != NULL)

    {

        int read = ReadProcessMemory(process, (LPCVOID)(base_addr), data, sizeof(data), NULL);

        if(read != 0)        

            return data; 

        else

            return 0;

    }

    else

        return NULL;

    CloseHandle(process);

}

DWORD* write_data(DWORD pid, DWORD* data, const void* base_addr)

{

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if(process != NULL)

    {

        int write = WriteProcessMemory(process, (LPVOID)(base_addr), data, sizeof(data), NULL)

        if(write != 0)

        {

            return data;

        }

        else

        {

            return 0;

        }

    }

    else

        return NULL;

    CloseHandle(process);

}
