#pragma once

// Network
#pragma comment (lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <mutex>

#define port "19070"
#define recvBufLen 512
#define sendBufLen 128

using std::thread;
using std::atomic;
using std::mutex;
using std::lock;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

typedef unsigned short ushort;

// ���� include
#include<Windows.h>
#include<tchar.h>
#include<memory>
#include<vector>
#include<queue>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<ctime>
#define _USE_MATH_DEFINES
#include<math.h>

// My Header
#include "Define.h"
#include "Enums.h"
#include "Vector2.h"

// ���� lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib") // transparent �� blt�� ���
#pragma comment(lib, "fmod_vc.lib") 
#pragma comment(lib, "fmodL_vc.lib")

// ���� using
using std::vector;
using std::queue;
using std::map;
using std::wstring;

// ���� define
#define PI 3.14159265f
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

// ������ �ܼ�â
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include<iostream>
using std::cout;
using std::endl;
