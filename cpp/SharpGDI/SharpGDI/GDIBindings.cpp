#include "GDIBindings.h"

GDIBinding void InitContext(
    INT x, INT y,
    INT width, INT height) {
    DisplayHandle = GetConsoleWindow();
    SetWindowLong(DisplayHandle, GWL_STYLE, GetWindowLong(DisplayHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    ShowScrollBar(DisplayHandle, SB_BOTH, FALSE);

    MoveWindow(DisplayHandle, x, y, width, height, TRUE);
    GetClientRect(DisplayHandle, &DisplayRect);

    FrontDeviceContext = GetDC(DisplayHandle);

    Width = width;
    Height = height;
}

GDIBinding void ReleaseContext() {
    ReleaseDC(DisplayHandle, FrontDeviceContext);
}

GDIBinding SHORT GetKeyStateByte(BYTE key) {
    return GetAsyncKeyState(key);
}

GDIBinding SHORT GetKeyStateChar(CHAR key) {
    return GetAsyncKeyState(key);
}

GDIBinding void SetTransform(
    FLOAT m11, FLOAT m12,
    FLOAT m21, FLOAT m22,
    FLOAT dX, FLOAT dY) {
    XFORM transform{};

    transform.eM11 = m11;
    transform.eM12 = m12;
    transform.eM21 = m21;
    transform.eM22 = m22;

    transform.eDx = dX;
    transform.eDy = dY;

    SetWorldTransform(BackDeviceContext, &transform);
}

GDIBinding void SetIdentity() {
    ModifyWorldTransform(BackDeviceContext, NULL, MWT_IDENTITY);
}

GDIBinding void LoadSpriteFromFile(LPCWSTR fileName, INT& id) {
    id = Sprites.size();
    HBITMAP spriteBitmap = (HBITMAP) LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    BITMAP bitmapInfo;
    GetObject(spriteBitmap, (int)sizeof bitmapInfo, &bitmapInfo);

    Sprite sprite(spriteBitmap, bitmapInfo.bmWidth, bitmapInfo.bmHeight);
    Sprites.push_back(sprite);
}

GDIBinding void GetSpriteRawSize(INT& width, INT& height) {
    Sprite& sprite = Sprites[CurrentSpriteId];
    width = sprite.GetWidth();
    height = sprite.GetHeight();
}

GDIBinding void BindSprite(INT id) {
    CurrentSpriteId = id;
}

GDIBinding void DeleteSprite() {
    DeleteObject(Sprites[CurrentSpriteId].GetBitmap());
}

GDIBinding void Begin() {
    BackDeviceContext = CreateCompatibleDC(FrontDeviceContext);
    SetGraphicsMode(BackDeviceContext, GM_ADVANCED);
    FrontBitmap = CreateCompatibleBitmap(FrontDeviceContext, Width, Height);
    BackBitmap = (HBITMAP)SelectObject(BackDeviceContext, FrontBitmap);
    SetBkMode(BackDeviceContext, TRANSPARENT);
}

GDIBinding void End() {
    BitBlt(FrontDeviceContext, 0, 0, Width, Height, BackDeviceContext, 0, 0, SRCCOPY);
    SelectObject(BackDeviceContext, BackBitmap);
    DeleteObject(FrontBitmap);
    DeleteObject(BackDeviceContext);
}

GDIBinding void FillPixel(
    INT x, INT y,
    COLORREF color) {
    SetPixel(BackDeviceContext, x, y, color);
}

GDIBinding void DrawSprite() {
    Sprite& sprite = Sprites[CurrentSpriteId];
    HBITMAP spriteBitmap = sprite.GetBitmap();

    HDC mDeviceContext = CreateCompatibleDC(BackDeviceContext);

    HBITMAP oldBitmap = (HBITMAP) SelectObject(mDeviceContext, spriteBitmap);

    INT width = sprite.GetWidth();
    INT height = sprite.GetHeight();

    BitBlt(BackDeviceContext, -width * 0.5, -height * 0.5, width, height, mDeviceContext, 0, 0, SRCCOPY);
    SelectObject(mDeviceContext, oldBitmap);
    DeleteDC(mDeviceContext);
}

GDIBinding void PrintText(
    LPCWSTR text,
    INT left, INT bottom, INT right, INT top,
    COLORREF color) {
    SetTextColor(BackDeviceContext, color);

    RECT bounds;
    bounds.left = left;
    bounds.bottom = bottom;
    bounds.right = right;
    bounds.top = top;

    DrawText(BackDeviceContext, text, -1, &bounds, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
}

GDIBinding void DrawRectangle(
    INT left, INT top, INT right, INT bottom,
    COLORREF color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(BackDeviceContext, hBrush);
    Rectangle(BackDeviceContext, left, top, right, bottom);
    DeleteObject(hBrush);
}

GDIBinding void DrawEllipse(
    INT left, INT top, INT right, INT bottom,
    COLORREF color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(BackDeviceContext, hBrush);
    Ellipse(BackDeviceContext, left, top, right, bottom);
    DeleteObject(hBrush);
}

GDIBinding void DrawPolygon(
    INT* inVertices,
    INT vertexCount,
    COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(BackDeviceContext, hBrush);

    std::vector<POINT> vertices;

    for (int i = 0; i < vertexCount; i += 2) {
        vertices.push_back({ inVertices[i], inVertices[i + 1] });
    }

    Polygon(BackDeviceContext, vertices.data(), vertices.size());

    DeleteObject(hBrush);
}

Sprite::Sprite(HBITMAP hBitmap, INT width, INT height) :
    m_hBitmap(hBitmap),
    m_width(width), m_height(height) {}

HBITMAP Sprite::GetBitmap() const
{
    return m_hBitmap;
}

INT Sprite::GetWidth() const
{
    return m_width;
}

INT Sprite::GetHeight() const
{
    return m_height;
}
