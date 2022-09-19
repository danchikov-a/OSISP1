#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "headers/Sprite.h"

Sprite sprite;

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
    switch (uMsg) {
        case WM_MOUSEMOVE:
            sprite.x = LOWORD(lParam) - sprite.WIDTH / 2;
            sprite.y = HIWORD(lParam) - sprite.HEIGHT / 2;

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_RIGHT:
                    sprite.x += sprite.SPEED;
                    break;
                case VK_LEFT:
                    sprite.x -= sprite.SPEED;
                    break;
                case VK_UP:
                    sprite.y -= sprite.SPEED;
                    break;
                case VK_DOWN:
                    sprite.y += sprite.SPEED;
                    break;
            }

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = GetDC(hWnd);


            BeginPaint(hWnd, &ps);
            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 255, 255)));
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 67));
            SelectObject(hdc, hBrush);
             Ellipse(hdc, sprite.x, sprite.y, sprite.x + sprite.WIDTH, sprite.y + sprite.HEIGHT);
           // Ellipse(hdc, xPos, yPos, xPos + sprite.WIDTH, yPos + sprite.HEIGHT);

            EndPaint(hWnd, &ps);
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
