#pragma once

#include <wincodec.h>
//#pragma comment(lib, "windowscodec.lib")
#include <windows.h>
 
// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <wchar.h>
#include <math.h>
#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include <algorithm>
#include "stdio.h"
#include <stdlib.h> 
#include <heapapi.h>
#include <cmath>
#include <array>
// user defined

#include "errors.h"


#include <unordered_map>

#include "Utils2D_v2.h"
#define MAX_TILES_PER_ROW 255
#define MAX_TILES_PER_COL 255
#define MAX_ENEMIES 30

#define GRAVITY 9.8f
#define MOVE_LEFT -1
#define MOVE_RIGHT 1


typedef std::vector<std::string> stringList;

template<typename T>
static T Sign(T val)
{
	if (val == (T)0)
		return (T)0;
	return std::signbit((float)val) ? (T)-1 : (T)1;
}
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
};
template<class Interface>
inline void SafeDelete(Interface **ppInterface)
{
	if (*ppInterface != NULL)
	{
		delete *ppInterface;

		(*ppInterface) = NULL;
	}
}

///////////////////////////////////////////////////////////
// Image Tages
#define LEVEL1_SPRITES 0


//////////////////////////////////////////////////////////

const static int TILE_WIDTH = 64;
const static int TILE_HEIGHT = 64;

#ifndef D2_MAT3x2_IDENTITY
#define D2_MATRIX_IDENTITY(m) { (m) = (D2D1::Matrix3x2F::Identity()); }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=nullptr; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=nullptr; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=nullptr; } }
#endif

template <typename T>
static void delete_ptr(T*  ptr)
{
	SAFE_DELETE(ptr);
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

