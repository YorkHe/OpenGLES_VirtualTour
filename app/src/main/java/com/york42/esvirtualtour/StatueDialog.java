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

public class StatueDialog extends DialogFragment{

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

        View v = getActivity().getLayoutInflater().inflate(R.layout.dialog_statue, null);
        mPositionX = (EditText)v.findViewById(R.id.st_position_x);
        mPositionY = (EditText)v.findViewById(R.id.st_position_y);
        mPositionZ = (EditText)v.findViewById(R.id.st_position_z);
        
        mScaleX = (EditText)v.findViewById(R.id.st_scale_x);
        mScaleY = (EditText)v.findViewById(R.id.st_scale_y);
        mScaleZ = (EditText)v.findViewById(R.id.st_scale_z);
        
        mRotate = (CheckBox)v.findViewById(R.id.st_rotate); 
        
        

        mPositionX.setText(String.valueOf(CustomRenderer.mSTPositionX));
        mPositionY.setText(String.valueOf(CustomRenderer.mSTPositionY));
        mPositionZ.setText(String.valueOf(CustomRenderer.mSTPositionZ));

        mScaleX.setText(String.valueOf(CustomRenderer.mSTScaleX));
        mScaleY.setText(String.valueOf(CustomRenderer.mSTScaleY));
        mScaleZ.setText(String.valueOf(CustomRenderer.mSTScaleZ));

        mRotate.setChecked(CustomRenderer.mSTRotate);


        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());


        builder.setMessage("调节雕像参数")
                .setView(v)
                .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                        CustomRenderer.setST(Float.parseFloat(mPositionX.getText().toString()), Float.parseFloat(mPositionY.getText().toString()),Float.parseFloat(mPositionZ.getText().toString()),
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
