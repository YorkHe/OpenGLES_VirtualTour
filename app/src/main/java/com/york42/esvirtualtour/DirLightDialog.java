package com.york42.esvirtualtour;

import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.widget.EditText;

/**
 * @author 42 york.heyu@gmail.com
 * @since 2016/12/19
 */

public class DirLightDialog extends DialogFragment {

    String mMessage;

    EditText mDirectionX;
    EditText mDirectionY;
    EditText mDirectionZ;

    EditText mAmbientR;
    EditText mAmbientG;
    EditText mAmbientB;

    EditText mDiffuseR;
    EditText mDiffuseG;
    EditText mDiffuseB;

    EditText mSpecularR;
    EditText mSpecularG;
    EditText mSpecularB;


    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        View v = getActivity().getLayoutInflater().inflate(R.layout.dialog_dirlight, null);
        
        mDirectionX= (EditText)v.findViewById(R.id.dlight_direction_x);
        mDirectionY= (EditText)v.findViewById(R.id.dlight_direction_y);
        mDirectionZ= (EditText)v.findViewById(R.id.dlight_direction_z);

        mAmbientR = (EditText)v.findViewById(R.id.dlight_ambient_r);
        mAmbientG = (EditText)v.findViewById(R.id.dlight_ambient_g);
        mAmbientB = (EditText)v.findViewById(R.id.dlight_ambient_b);

        mDiffuseR = (EditText)v.findViewById(R.id.dlight_diffuse_r);
        mDiffuseG = (EditText)v.findViewById(R.id.dlight_diffuse_g);
        mDiffuseB = (EditText)v.findViewById(R.id.dlight_diffuse_b);

        mSpecularR = (EditText)v.findViewById(R.id.dlight_specular_r);
        mSpecularG = (EditText)v.findViewById(R.id.dlight_specular_g);
        mSpecularB = (EditText)v.findViewById(R.id.dlight_specular_b);

        mDirectionX.setText(String.valueOf(CustomRenderer.mDLDirectionX));
        mDirectionY.setText(String.valueOf(CustomRenderer.mDLDirectionY));
        mDirectionZ.setText(String.valueOf(CustomRenderer.mDLDirectionZ));

        mAmbientR.setText(String.valueOf(CustomRenderer.mDLAmbientR));
        mAmbientG.setText(String.valueOf(CustomRenderer.mDLAmbientG));
        mAmbientB.setText(String.valueOf(CustomRenderer.mDLAmbientB));

        mDiffuseR.setText(String.valueOf(CustomRenderer.mDLDiffuseR));
        mDiffuseG.setText(String.valueOf(CustomRenderer.mDLDiffuseG));
        mDiffuseB.setText(String.valueOf(CustomRenderer.mDLDiffuseB));

        mSpecularR.setText(String.valueOf(CustomRenderer.mDLSpecularR));
        mSpecularG.setText(String.valueOf(CustomRenderer.mDLSpecularG));
        mSpecularB.setText(String.valueOf(CustomRenderer.mDLSpecularB));


        builder.setMessage("调节方向光源")
                .setView(v)
                .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
        
                        CustomRenderer.setDirLight(Float.parseFloat(mDirectionX.getText().toString()), Float.parseFloat(mDirectionY.getText().toString()), Float.parseFloat(mDirectionZ.getText().toString()),
                                Float.parseFloat(mAmbientR.getText().toString()), Float.parseFloat(mAmbientG.getText().toString()), Float.parseFloat(mAmbientB.getText().toString()),
                                Float.parseFloat(mDiffuseR.getText().toString()), Float.parseFloat(mDiffuseG.getText().toString()), Float.parseFloat(mDiffuseB.getText().toString()),
                                Float.parseFloat(mDiffuseR.getText().toString()), Float.parseFloat(mSpecularG.getText().toString()), Float.parseFloat(mSpecularB.getText().toString()));
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