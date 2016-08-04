//
// Created by Hindrik Stegenga on 7/27/2016.
//

#ifndef ASCENSION_CORE_RELEASE_COM_H
#define ASCENSION_CORE_RELEASE_COM_H

#include <string>
#include <d3d11.h>

using std::wstring;

//Released een com object veilig
template<typename T>
void ReleaseCOM(T& ptr)
{
	if (ptr != NULL)
	{
		ptr->Release();
		ptr = NULL;
	}
}

void CheckFail(HRESULT hr, wstring text);

#endif