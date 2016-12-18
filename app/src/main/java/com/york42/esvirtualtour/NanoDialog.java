package com.york42.esvirtualtour;

import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;

/**
 * @author 42 york.heyu@gmail.com
 * @since 2016/12/19
 */

public class NanoDialog extends DialogFragment{

    EditText mPositionX;
    EditText mPositionY;
    EditText mPositionZ;
    
    EditText mScaleX;
    EditText mScaleY;
    EditText mScaleZ;
    
    CheckBox mRotate;
    
    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {

        View v = getActivity().getLayoutInflater().inflate(R.layout.dialog_nanosuit, null);
        mPositionX = (EditText)v.findViewById(R.id.nano_position_x);
        mPositionY = (EditText)v.findViewById(R.id.nano_position_y);
        mPositionZ = (EditText)v.findViewById(R.id.nano_position_z);
        
        mScaleX = (EditText)v.findViewById(R.id.nano_scale_x);
        mScaleY = (EditText)v.findViewById(R.id.nano_scale_y);
        mScaleZ = (EditText)v.findViewById(R.id.nano_scale_z);
        
        mRotate = (CheckBox)v.findViewById(R.id.nano_rotate); 
        
        

        mPositionX.setText(String.valueOf(CustomRenderer.mNNPositionX));
        mPositionY.setText(String.valueOf(CustomRenderer.mNNPositionY));
        mPositionZ.setText(String.valueOf(CustomRenderer.mNNPositionZ));

        mScaleX.setText(String.valueOf(CustomRenderer.mNNScaleX));
        mScaleY.setText(String.valueOf(CustomRenderer.mNNScaleY));
        mScaleZ.setText(String.valueOf(CustomRenderer.mNNScaleZ));

        mRotate.setChecked(CustomRenderer.mNNRotate);


        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());


        builder.setMessage("调节纳米服参数")
                .setView(v)
                .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                        CustomRenderer.setNano(Float.parseFloat(mPositionX.getText().toString()), Float.parseFloat(mPositionY.getText().toString()),Float.parseFloat(mPositionZ.getText().toString()),
                                               Float.parseFloat(mScaleX.getText().toString()),Float.parseFloat(mScaleY.getText().toString()),Float.parseFloat(mScaleZ.getText().toString()),
                                               mRotate.isChecked());
                    }
                })
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                });

        return builder.create();
    }
        
}
