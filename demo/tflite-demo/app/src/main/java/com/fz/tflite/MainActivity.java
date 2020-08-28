package com.fz.tflite;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //

        AssetManager mgr = this.getAssets();
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI(mgr, "mobilenet_v1_1.0_224_quant_and_labels/mobilenet_v1_1.0_224_quant.tflite", "mobilenet_v1_1.0_224_quant_and_labels/labels_mobilenet_quant_v1_224.txt"));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(AssetManager assetManager, String pathModel, String pathLabel);
}
