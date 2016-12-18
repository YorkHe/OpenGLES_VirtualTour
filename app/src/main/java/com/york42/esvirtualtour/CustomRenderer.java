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

    public static float mPLPositionX = 0.0f;
    public static float mPLPositionY = 10.0f;
    public static float mPLPositionZ = 0.0f;

    public static float mPLAmbientR = 0.2f;
    public static float mPLAmbientG = 0.2f;
    public static float mPLAmbientB = 0.2f;

    public static float mPLDiffuseR = 0.5f;
    public static float mPLDiffuseG = 0.5f;
    public static float mPLDiffuseB = 0.5f;

    public static float mPLSpecularR = 1.0f;
    public static float mPLSpecularG = 1.0f;
    public static float mPLSpecularB = 1.0f;

    public static float mDLDirectionX = -0.2f;
    public static float mDLDirectionY = -1.0f;
    public static float mDLDirectionZ = -0.3f;

    public static float mDLAmbientR = 0.3f;
    public static float mDLAmbientG = 0.3f;
    public static float mDLAmbientB = 0.3f;

    public static float mDLDiffuseR = 0.4f;
    public static float mDLDiffuseG = 0.4f;
    public static float mDLDiffuseB = 0.4f;

    public static float mDLSpecularR = 0.5f;
    public static float mDLSpecularG = 0.5f;
    public static float mDLSpecularB = 0.5f;
    
    public static float mNNPositionX = -50.0f;
    public static float mNNPositionY = 0.0f;
    public static float mNNPositionZ = -20.0f;
     
    public static float mNNScaleX = 0.05f;
    public static float mNNScaleY = 0.05f;
    public static float mNNScaleZ = 0.05f;

    public static boolean mNNRotate = false;
     
    public static float mSTPositionX = 0.0f;
    public static float mSTPositionY = 0.0f;
    public static float mSTPositionZ = 0.0f;
     
    public static float mSTScaleX = 1.0f;
    public static float mSTScaleY = 1.0f;
    public static float mSTScaleZ = 1.0f;

    public static boolean mSTRotate = false;

    private Context mContext;
    public CustomRenderer(Context context)
    {
        super();
        mContext = context;
        startTime = System.currentTimeMillis();
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        nativeSetPointLight(mPLPositionX, mPLPositionY, mPLPositionZ,
                            mPLAmbientR, mPLAmbientG, mPLAmbientB,
                            mPLDiffuseR, mPLDiffuseG, mPLDiffuseB,
                            mPLSpecularR, mPLSpecularG, mPLSpecularB);

        nativeSetDirLight(mDLDirectionX, mDLDirectionY, mDLDirectionZ,
                          mDLAmbientR, mDLAmbientG, mDLAmbientB,
                          mDLDiffuseR, mDLDiffuseG, mDLDiffuseB,
                          mDLSpecularR, mDLSpecularG, mDLSpecularB);
        
        nativeSetNano(mNNPositionX, mNNPositionY, mNNPositionZ,
                      mNNScaleX, mNNScaleY, mNNScaleZ,
                      mNNRotate);

        nativeSetNano(mSTPositionX, mSTPositionY, mSTPositionZ,
                      mSTScaleX, mSTScaleY, mSTScaleZ,
                      mSTRotate);
        nativeInit();
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

    public static void setNano(float positionX, float positionY, float positionZ,
                               float scaleX, float scaleY, float scaleZ,
                               boolean rotate)
    {
        mNNPositionX = positionX;
        mNNPositionY = positionY;
        mNNPositionZ = positionZ;

        mNNScaleX = scaleX;
        mNNScaleY = scaleY;
        mNNScaleZ = scaleZ;

        mNNRotate = rotate;

        nativeSetNano(positionX, positionY, positionZ,
                      scaleX, scaleY, scaleZ,
                      rotate);
    }
    
    public static void setST(float positionX, float positionY, float positionZ,
                               float scaleX, float scaleY, float scaleZ,
                               boolean rotate)
    {
        mSTPositionX = positionX;
        mSTPositionY = positionY;
        mSTPositionZ = positionZ;

        mSTScaleX = scaleX;
        mSTScaleY = scaleY;
        mSTScaleZ = scaleZ;

        mSTRotate = rotate;

        nativeSetST(positionX, positionY, positionZ,
                      scaleX, scaleY, scaleZ,
                      rotate);
    }
    

    public static void setPointLight(float positionX, float positionY, float positionZ,
                                     float ambientR, float ambientG, float ambientB,
                                     float diffuseR, float diffuseG, float diffuseB,
                                     float specuarR, float specularG, float specularB)
    {
        mPLPositionX = positionX;
        mPLPositionY = positionY;
        mPLPositionZ = positionZ;

        mPLAmbientR = ambientR;
        mPLAmbientG = ambientG;
        mPLAmbientB = ambientB;

        mPLDiffuseR = diffuseR;
        mPLDiffuseG = diffuseG;
        mPLDiffuseB = diffuseB;

        mPLSpecularR = specuarR;
        mPLSpecularG = specularG;
        mPLSpecularB = specularB;

        nativeSetPointLight(positionX, positionY, positionZ,
                ambientR, ambientG, ambientR,
                diffuseR, diffuseG, diffuseB,
                specuarR, specularG, specularB);
    }


    public static void setDirLight(float directionX, float directionY, float directionZ,
                                   float ambientR, float ambientG, float ambientB,
                                   float diffuseR, float diffuseG, float diffuseB,
                                   float specuarR, float specularG, float specularB)
    {
        mDLDirectionX = directionX;
        mDLDirectionY = directionY;
        mDLDirectionZ = directionZ;

        mDLAmbientR = ambientR;
        mDLAmbientG = ambientG;
        mDLAmbientB = ambientB;

        mDLDiffuseR = diffuseR;
        mDLDiffuseG = diffuseG;
        mDLDiffuseB = diffuseB;

        mDLSpecularR = specuarR;
        mDLSpecularG = specularG;
        mDLSpecularB = specularB;

        nativeSetDirLight(directionX, directionY, directionZ,
                ambientR, ambientG, ambientR,
                diffuseR, diffuseG, diffuseB,
                specuarR, specularG, specularB);
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

    public static native void nativeInit();
    private static native void nativeDraw(long time);
    private static native void nativeSurfaceChanged(int width, int height);
    private static native void nativeDirectionCallback(int direction, int evt);
    private static native void nativeSetPointLight(float positionX, float positionY, float positionZ,
                                                   float ambientR, float ambientG, float ambientB,
                                                   float diffuseR, float diffuseG, float diffuseB,
                                                   float specuarR, float specularG, float specularB);
    private static native void nativeSetDirLight(float directionX, float directionY, float directionZ,
                                                 float ambientR, float ambientG, float ambientB,
                                                 float diffuseR, float diffuseG, float diffuseB,
                                                 float specuarR, float specularG, float specularB);
    private static native void nativeSetNano(float positionX, float positionY, float positionZ,
                                             float scaleX, float scaleY, float scaleZ,
                                             boolean rotate);
     private static native void nativeSetST(float positionX, float positionY, float positionZ,
                                             float scaleX, float scaleY, float scaleZ,
                                             boolean rotate);
    


    private static native void nativeViewCallback(float xOffset, float yOffset);
}
