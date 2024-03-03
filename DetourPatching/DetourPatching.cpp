#include <windows.h>


void proc()
{
	typedef LPVOID RegSetKeyValuePtr;
	RegSetKeyValuePtr fptr;

	unsigned long routineAddress;
	HINSTANCE hinstLib;
	DWORD value;
	char YesDirValue[13] = "YesDirValue";

	value = 333;
	hinstLib = LoadLibraryA("Advapi32.dll");
	if (hinstLib != NULL)
	{
		fptr = (RegSetKeyValuePtr)GetProcAddress
		(hinstLib, "RegSetKeyValueA");

		routineAddress = (unsigned long)fptr;
		if (fptr != NULL)
		{
			_asm
			{
				//push arguments from right to left
				push	 4
				lea		eax, value
				push	eax
				push	4
				lea		eax, YesDirValue
				push	eax
				push	0
				mov		ecx, hkey
				push	ecx
				mov		ecx, routineAddress

				// push on return address manually
				mov		eax, returnLabel
				push	eax

				// perform first few instructions manually
				mov		edi, edi
				push	ebp
				mov		ebp, esp
				mov		eax, dword ptr[ebp + 0ch]
				push	ebx
				push	esi
				xor ebx, ebx
				xor esi, esi

				// skip first few bytes
				add ecx, 0xE

				// jmp to routine location
				jmp ecx
				returnLabel:
				
			}
		}
		FreeLibrary(hinstLib);
	}