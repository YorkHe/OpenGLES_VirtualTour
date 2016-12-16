package com.york42.esvirtualtour;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.view.SurfaceView;

/**
 * @author 42 york.heyu@gmail.com
 * @since 2016/12/15
 */

public class CustomSurfaceView extends GLSurfaceView{
    private CustomRenderer mRenderer;
    private float mPreviousX;
    private float mPreviousY;
    private final float TOUCH_SCALE_FACTOR = 0.0001f;

    public CustomSurfaceView(Context context){
        super(context);
        setEGLContextClientVersion(3);
        mRenderer = new CustomRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float x = event.getX();
        float y = event.getY();
        switch (event.getAction()){
            case MotionEvent.ACTION_MOVE:
                float dx = x - mPreviousX;
                float dy = y - mPreviousY;

//                mRenderer.mAngleX += dy * TOUCH_SCALE_FACTOR;
//                mRenderer.mAngleY += dx * TOUCH_SCALE_FACTOR;
                mRenderer.onViewMovement(dx, dy);

//                requestRender();
        }
        mPreviousX = x;
        mPreviousY = y;


        return true;
    }

    public void onDirectionClick(int direction, MotionEvent event)
    {
        mRenderer.onDirectionClick(direction, event.getAction());

    }

}

