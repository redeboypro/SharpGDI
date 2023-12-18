using SharpGDI;

var time = new Time();

GDI.InitContext(0, 0, 800, 600);

while (!Input.IsKeyDown(Input.Space))
{
    time.Begin();
    GDI.Begin();
    GDI.DrawRectangle(0,0, 100, 200, GDI.FromRgb(255, 255, 255));
    
    GDI.PrintText(time.GetFramesPerSecond().ToString(), 10, 100, 100, 10, GDI.FromRgb(255, 0, 0));

    GDI.End();
    time.End();
}
GDI.ReleaseContext();