#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "headers/Sprite.h"

Sprite sprite;
const int BMP_WIDTH = 56;
const int BMP_HEIGHT = 170;
bool isBmp = false;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    sprite.x = 100;
    sprite.y = 100;

    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Learn to Program Windows",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    RECT rcClient;

    GetClientRect(hWnd, &rcClient);

    LONG leftBound = rcClient.left;
    LONG rightBound = rcClient.right;
    LONG topBound = rcClient.top;
    LONG downBound = rcClient.bottom;

    switch (uMsg) {
        case WM_MOUSEMOVE: {
            sprite.x = LOWORD(lParam) - sprite.width / 2;
            sprite.y = HIWORD(lParam) - sprite.height / 2;

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case WM_MOUSEWHEEL: {
            int wheelOffset = GET_WHEEL_DELTA_WPARAM(wParam);

            if (LOWORD(wParam) == MK_SHIFT) {
                if (wheelOffset > 0) {
                    sprite.moveLeft(leftBound);
                } else {
                    sprite.moveRight(rightBound);
                }
            } else {
                if (wheelOffset > 0) {
                    sprite.moveUp(topBound);
                } else {
                    sprite.moveDown(downBound);
                }
            }

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_RIGHT:
                    sprite.moveRight(rightBound);
                    break;
                case VK_LEFT:
                    sprite.moveLeft(leftBound);
                    break;
                case VK_UP:
                    sprite.moveUp(topBound);
                    break;
                case VK_DOWN:
                    sprite.moveDown(downBound);
                    break;
                case VK_TAB :
                    isBmp = !isBmp;

                    if (isBmp) {
                        sprite.width = 56;
                        sprite.height = 170;
                    } else {
                        sprite.width = 100;
                        sprite.height = 100;
                    }

                    break;
            }

            InvalidateRect(hWnd, NULL, TRUE);

            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = GetDC(hWnd);

            BeginPaint(hWnd, &ps);

            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 255, 255)));

            if (isBmp) {
                HBITMAP hBmp = (HBITMAP) LoadImage(NULL, L"../picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                HDC bmpDC = CreateCompatibleDC(hdc);
                SelectObject(bmpDC, hBmp);
                BitBlt(hdc, sprite.x, sprite.y, BMP_WIDTH, BMP_HEIGHT, bmpDC, 0, 0, SRCCOPY);
                DeleteDC(bmpDC);
                DeleteObject(hBmp);
            } else {
                HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 67));
                SelectObject(hdc, hBrush);
                Ellipse(hdc, sprite.x, sprite.y, sprite.x + sprite.width, sprite.y + sprite.height);
            }

            EndPaint(hWnd, &ps);
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}