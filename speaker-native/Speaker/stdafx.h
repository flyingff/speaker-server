#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <string>

#include <Windows.h>
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>

//You may derive a class from CComModule and use it if you want to override something,
//but do not change the name of _Module
extern CComModule _Module;

#include <atlcom.h>
#include <sapi.h>

#pragma warning(disable:4996)
#include <sphelper.h>