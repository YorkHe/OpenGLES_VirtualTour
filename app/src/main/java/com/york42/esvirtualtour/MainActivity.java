package com.york42.esvirtualtour;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {

    private ImageButton left;
    private ImageButton right;
    private ImageButton up;
    private ImageButton down;

    private Button pointLight;
    private Button dirLight;
    private Button nanosuit;
    private Button statue;

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
        View lightView = LayoutInflater.from(this).inflate(R.layout.lights, null);

        getSupportActionBar().hide();

        left = (ImageButton)view.findViewById(R.id.left);
        right = (ImageButton)view.findViewById(R.id.right);
        up = (ImageButton)view.findViewById(R.id.up);
        down = (ImageButton)view.findViewById(R.id.down);

        left.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.LEFT.ordinal()));
        right.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.RIGHT.ordinal()));
        up.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.FORWARD.ordinal()));
        down.setOnTouchListener(new OnclickListenerFactory(Camera_Movement.BACKWARD.ordinal()));

        pointLight  = (Button)lightView.findViewById(R.id.pointLight);
        dirLight = (Button)lightView.findViewById(R.id.dirLight);
        nanosuit = (Button)lightView.findViewById(R.id.nanosuit);
        statue = (Button)lightView.findViewById(R.id.statue);


        pointLight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PointLightDialog lightDialog = new PointLightDialog();
                lightDialog.show(getSupportFragmentManager(), "pointLight");
            }
        });

        dirLight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DirLightDialog lightDialog = new DirLightDialog();
                lightDialog.show(getSupportFragmentManager(), "dirLight");
            }
        });

        nanosuit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                NanoDialog nanoDialog = new NanoDialog();
                nanoDialog.show(getSupportFragmentManager(), "nanosuit");
            }
        });

        statue.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                StatueDialog statueDialog = new StatueDialog();
                statueDialog.show(getSupportFragmentManager(), "statue");
            }
        });

        addContentView(view, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        addContentView(lightView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

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
