package com.york42.esvirtualtour;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author 42 york.heyu@gmail.com
 * @since 2016/12/15
 */

public class CustomRenderer implements GLSurfaceView.Renderer{
    public float mAngleX;
    public float mAngleY;

    public float xOffset;
    public float yOffset;

    public long startTime;

    private Context mContext;
    public CustomRenderer(Context context)
    {
        super();
        mContext = context;
        startTime = System.currentTimeMillis();
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        String vertexShaderSource = LoadShader(mContext, R.raw.vshader);
        String fragmentShaderSource = LoadShader(mContext, R.raw.fshader);
        nativeInit(vertexShaderSource, fragmentShaderSource);

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        nativeSurfaceChanged(i, i1);
    }



    @Override
    public void onDrawFrame(GL10 gl10) {
        nativeDraw(System.currentTimeMillis() - startTime);
    }

    public void onDirectionClick(int direction, int evt)
    {
        nativeDirectionCallback(direction, evt);
    }

    public void onViewMovement(float xOffset, float yOffset)
    {
        nativeViewCallback(xOffset, yOffset);
    }


    private String LoadShader(Context context, int resId){
        StringBuffer strBuf = new StringBuffer();
        try {
            InputStream inputStream = context.getResources().openRawResource(resId);
            BufferedReader in = new BufferedReader(new InputStreamReader(inputStream));
            String read = in.readLine();
            while (read != null){
                strBuf.append(read + "\n");
                read = in.readLine();
            }
            strBuf.deleteCharAt(strBuf.length() - 1);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
        return strBuf.toString();
    }

    static {
        System.loadLibrary("NativeGLES");
    }

    public static native void nativeInit(String vertexShaderSource, String fragmentShaderSource);
    private static native void nativeDraw(long time);
    private static native void nativeSurfaceChanged(int width, int height);
    private static native void nativeDirectionCallback(int direction, int evt);
    private static native void nativeViewCallback(float xOffset, float yOffset);
}
