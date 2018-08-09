#pragma once
#include "UberBot.h"
#define ID_BUTTON_ABOUT 10
#define ID_BUTTON_ADD_IP 12
#define ID_BUTTON_REMOVE_IP 13
#define ID_IP_LIST 14
#define ID_IP 15
#define ID_BUTTON_STARTSTOP 16
#define ID_BUTTON_EXIT 17
#define ID_LOG_START 18
#define ID_LOG_END 19


#define IDD_ADD_IP 101

#define LEFT_MARGIN 10
#define TOP_MARGIN 10

#define BUTTON_W 72
#define BUTTON_H 24

LRESULT CALLBACK WndProcPopup(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);