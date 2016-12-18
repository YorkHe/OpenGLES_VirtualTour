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

public class PointLightDialog extends DialogFragment{

    String mMessage;

    EditText mPositionX;
    EditText mPositionY;
    EditText mPositionZ;

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
        View v = getActivity().getLayoutInflater().inflate(R.layout.dialog_pointlight, null);
        mPositionX = (EditText)v.findViewById(R.id.plight_position_x);
        mPositionY = (EditText)v.findViewById(R.id.plight_position_y);
        mPositionZ = (EditText)v.findViewById(R.id.plight_position_z);

        mAmbientR = (EditText)v.findViewById(R.id.plight_ambient_r);
        mAmbientG = (EditText)v.findViewById(R.id.plight_ambient_g);
        mAmbientB = (EditText)v.findViewById(R.id.plight_ambient_b);

        mDiffuseR = (EditText)v.findViewById(R.id.plight_diffuse_r);
        mDiffuseG = (EditText)v.findViewById(R.id.plight_diffuse_g);
        mDiffuseB = (EditText)v.findViewById(R.id.plight_diffuse_b);

        mSpecularR = (EditText)v.findViewById(R.id.plight_specular_r);
        mSpecularG = (EditText)v.findViewById(R.id.plight_specular_g);
        mSpecularB = (EditText)v.findViewById(R.id.plight_specular_b);

        mPositionX.setText(String.valueOf(CustomRenderer.mPLPositionX));
        mPositionY.setText(String.valueOf(CustomRenderer.mPLPositionY));
        mPositionZ.setText(String.valueOf(CustomRenderer.mPLPositionZ));

        mAmbientR.setText(String.valueOf(CustomRenderer.mPLAmbientR));
        mAmbientG.setText(String.valueOf(CustomRenderer.mPLAmbientG));
        mAmbientB.setText(String.valueOf(CustomRenderer.mPLAmbientB));

        mDiffuseR.setText(String.valueOf(CustomRenderer.mPLDiffuseR));
        mDiffuseG.setText(String.valueOf(CustomRenderer.mPLDiffuseG));
        mDiffuseB.setText(String.valueOf(CustomRenderer.mPLDiffuseB));

        mSpecularR.setText(String.valueOf(CustomRenderer.mPLSpecularR));
        mSpecularG.setText(String.valueOf(CustomRenderer.mPLSpecularG));
        mSpecularB.setText(String.valueOf(CustomRenderer.mPLSpecularB));

        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());


        builder.setMessage("调节点光源")
                .setView(v)
                .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                        CustomRenderer.setPointLight(Float.parseFloat(mPositionX.getText().toString()), Float.parseFloat(mPositionY.getText().toString()), Float.parseFloat(mPositionZ.getText().toString()),
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
