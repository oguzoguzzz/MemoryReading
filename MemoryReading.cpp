#include "Header.h"

int main()
{
    // Open the process to read from
    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, 10728);  // pid
    if (!processHandle)
    {
        std::cout << "Error opening process" << std::endl;
        return 1;
    }

    // Get the base address of the module to read from
    HMODULE moduleHandle;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, NULL, &moduleHandle);
    DWORD baseAddress = (DWORD)moduleHandle;

    // Calculate the offset address
    DWORD offset = 0x123456;
    DWORD addressToRead = baseAddress + offset;

    // Read the value from the memory address
    int value;
    if (!ReadProcessMemory(processHandle, (LPCVOID)addressToRead, &value, sizeof(value), NULL))
    {
        std::cout << "Error reading from memory" << std::endl;
        return 1;
    }

    // Print the value
    std::cout << "Value at address 0x" << std::hex << addressToRead << " is " << value << std::endl;

    // Close the process handle
    CloseHandle(processHandle);

    return 0;
}