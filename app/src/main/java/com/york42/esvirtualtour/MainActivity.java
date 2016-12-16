package com.york42.esvirtualtour;

import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private ImageButton left;
    private ImageButton right;
    private ImageButton up;
    private ImageButton down;
    private CustomSurfaceView mCustomSurfaceView;
    private FrameLayout mFrameLayout;


    public enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        DOWN,
        UP
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mCustomSurfaceView = new CustomSurfaceView(this);

        setContentView(mCustomSurfaceView);

        View view = LayoutInflater.from(this).inflate(R.layout.buttons, null);

        getSupportActionBar().hide();

        left = (ImageButton)view.findViewById(R.id.left);
        right = (ImageButton)view.findViewById(R.id.right);
        up = (ImageButton)view.findViewById(R.id.up);
        down = (ImageButton)view.findViewById(R.id.down);

        left.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.LEFT.ordinal()));
        right.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.RIGHT.ordinal()));
        up.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.FORWARD.ordinal()));
        down.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.BACKWARD.ordinal()));

        addContentView(view, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

    }

    class OnclickListenerFactory implements View.OnTouchListener{

        private int mDirection;

        public OnclickListenerFactory(int direction){
            mDirection = direction;
        }

        @Override
        public boolean onTouch(View view, MotionEvent event) {
            mCustomSurfaceView.onDirectionClick(mDirection, event);
            return true;
        }
    }
}
