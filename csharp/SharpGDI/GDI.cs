using System.Runtime.InteropServices;

namespace SharpGDI;

public static class GDI
{
    private const string ExternalDll = "libgdi.dll";
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void InitContext(
        Int32 x, Int32 y,
        Int32 width, Int32 height);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void ReleaseContext();
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern short GetKeyStateByte(Byte key);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern short GetKeyStateChar(Char key);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void Begin();
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void End();
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void LoadSpriteFromFile([MarshalAs(UnmanagedType.LPWStr)] String fileName, out Int32 id);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void GetSpriteRawSize(out Int32 width, out Int32 height);

    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DeleteSprite();
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void BindSprite(Int32 id);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DrawSprite();
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetTransform(
        Single m11, Single m12,
        Single m21, Single m22,
        Single dX, Single dY);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetIdentity();
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void FillPixel(
        Int32 x, Int32 y, Int32 rgb);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void PrintText(
        [MarshalAs(UnmanagedType.LPWStr)] String text,
        Int32 left, Int32 bottom, Int32 right, Int32 top,
        Int32 rgb);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DrawRectangle(Int32 left, Int32 top, Int32 right, Int32 bottom, Int32 rgb);

    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DrawEllipse(Int32 left, Int32 top, Int32 right, Int32 bottom, Int32 rgb);
    
    [DllImport(ExternalDll, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DrawPolygon(Int32[] vertices, Int32 vertexCount, Int32 rgb);
    
    public static void DrawLine(Int32 x1, Int32 y1, Int32 x2, Int32 y2, Int32 rgb)
    {
        var deltaX = Math.Abs(x2 - x1);
        var deltaY = -Math.Abs(y2 - y1);

        var xDirection = x1 < x2 ? 1 : -1;
        var yDirection = y1 < y2 ? 1 : -1;

        var err = deltaX + deltaY;

        while (true)
        {
            FillPixel(x1, y1, rgb);
            
            if (x1 == x2 && y1 == y2)
            {
                break;
            }

            var doubleErr = 2 * err;
            if (doubleErr >= deltaY)
            {
                if (x1 == x2)
                {
                    break;
                }

                err += deltaY;
                x1 += xDirection;
            }

            if (doubleErr > deltaX)
            {
                continue;
            }
            
            if (y1 == y2)
            {
                break;
            }

            err += deltaX;
            y1 += yDirection;
        }
    }

    public static Int32 FromRgb(Byte r, Byte g, Byte b)
    {
        return r | (g << 8) | (b << 16);
    }
    
    public static void ToRgb(
        Int32 rgb, 
        out Byte r, out Byte g, out Byte b)
    {
        r = (byte) (rgb & 0xFF);
        g = (byte) ((rgb >> 8) & 0xFF);
        b = (byte) ((rgb >> 16) & 0xFF);
    }
}