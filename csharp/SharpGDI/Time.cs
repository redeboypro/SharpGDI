namespace SharpGDI;

public class Time
{
    private DateTime _lastTime;
    private DateTime _currentTime;
    
    private Single _frameTime;
    private Int32 _frameRecorder;

    private Single _deltaTime;
    private Int32 _framesPerSecond;

    public Time()
    {
        _lastTime = DateTime.Now;
        _currentTime = DateTime.Now;
        _frameTime = 0.0f;
        _frameRecorder = 0;
        
        _deltaTime = Single.Epsilon;
        _framesPerSecond = 0;
    }

    public Single GetDeltaTime()
    {
        return _deltaTime;
    }

    public Int32 GetFramesPerSecond()
    {
        return _framesPerSecond;
    }

    public void Begin()
    {
        _currentTime = DateTime.Now;
        _deltaTime = (_currentTime.Ticks - _lastTime.Ticks) * 0.0000001f;
            
        _frameTime += _deltaTime;
        _frameRecorder++;

        if (_frameTime < 1.0f)
        {
            return;
        }
        
        _framesPerSecond = _frameRecorder;
        _frameTime = 0.0f;
        _frameRecorder = 0;
    }
        
    public void End()
    {
        _lastTime = _currentTime;
    }
}