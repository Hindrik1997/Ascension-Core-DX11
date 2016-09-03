//
// Created by Hindrik Stegenga on 7/27/2016.
//

#include "ReleaseCOM.h"

//Functie voor checken van falend HRESULT
void CheckFail(HRESULT hr, wstring text)
{
	if (FAILED(hr))
	{
		MessageBox(NULL, text.c_str(), L"Error", MB_OK);
		PostQuitMessage(0);
	}
}
