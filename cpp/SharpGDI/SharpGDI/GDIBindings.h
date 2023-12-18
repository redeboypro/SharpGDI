#pragma once
#include <cstdint>
#include <cstdio>
#include <windows.h>
#include <cmath>
#include <vector>

#define GDIBinding __declspec(dllexport)

extern "C"
{
    struct Sprite {
    private:
        HBITMAP m_hBitmap;
        INT m_width, m_height;
    public:
        Sprite(HBITMAP hBitmap, INT width, INT height);

        HBITMAP GetBitmap() const;

        INT GetWidth() const;

        INT GetHeight() const;
    };

    const FLOAT D2R = 3.141592653589793f / 180.0f;

    INT CurrentSpriteId;
    std::vector<Sprite> Sprites;

    HWND DisplayHandle;
    RECT DisplayRect;

    HDC FrontDeviceContext;
    HBITMAP FrontBitmap;

    HDC BackDeviceContext;
    HBITMAP BackBitmap;

    INT Width, Height;

    GDIBinding void InitContext(
        INT x, INT y,
        INT width, INT height);

    GDIBinding void ReleaseContext();

    GDIBinding SHORT GetKeyStateByte(BYTE key);

    GDIBinding SHORT GetKeyStateChar(CHAR key);

    GDIBinding void Begin();

    GDIBinding void End();

    GDIBinding void FillPixel(
        INT x, INT y,
        COLORREF color);

    GDIBinding void PrintText(
        LPCWSTR text,
        INT left, INT bottom, INT right, INT top,
        COLORREF color);

    GDIBinding void LoadSpriteFromFile(LPCWSTR fileName, INT& id);

    GDIBinding void GetSpriteRawSize(INT& width, INT& height);

    GDIBinding void BindSprite(INT id);

    GDIBinding void DeleteSprite();

    GDIBinding void DrawSprite();

    GDIBinding void SetTransform(
        FLOAT m11, FLOAT m12,
        FLOAT m21, FLOAT m22,
        FLOAT dX, FLOAT dY);

    GDIBinding void SetIdentity();

    GDIBinding void DrawRectangle(
        INT left, INT top, INT right, INT bottom,
        COLORREF color);

    GDIBinding void DrawEllipse(
        INT left, INT top, INT right, INT bottom,
        COLORREF color);

    GDIBinding void DrawPolygon(
        INT* inVertices,
        INT vertexCount,
        COLORREF color);
}


