package com.example.md5sha;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.example.md5sha.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'md5sha' library on application startup.
    static {
        System.loadLibrary("md5sha");
   }

    private ActivityMainBinding binding;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        Button  md5bt = findViewById(R.id.md5bt);
        EditText md5et  = findViewById(R.id.md5et); // 这里初始化了 editText
        TextView md5rtv = findViewById(R.id.md5rtv);
        // 这里初始化了 tvMd5Result
    // 这里初始化了 Button

        // 设置按钮点击事件
        md5bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 获取用户输入的文本
                String inputText = md5et.getText().toString();

                // 调用 C++ 的计算 MD5 方法
                String md5Result = calculateMd5(inputText);

                // 显示 MD5 结果
                md5rtv.setText(md5Result);
            }
        });



        EditText sha1et = findViewById(R.id.sha1et);
        Button sha1bt = findViewById(R.id.sha1bt);
        TextView sha1rt = findViewById(R.id.sha1rt);
        // 这里初始化了 editText
        // 这里初始化了 Button
        // 设置按钮点击事件
        sha1bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 获取用户输入的文本
                String inputText = sha1et.getText().toString();

                // 调用 C++ 的计算 MD5 方法
                String sha1text = calculateSha1(inputText);

                // 显示 sha1 结果
                sha1rt.setText(sha1text);
            }
        });

        String text = "kanxue";
        String md5Result = customMd5(text);

        // 显示在 TextView 中
        TextView textView = findViewById(R.id.Magicmd5);
        textView.setText(md5Result);


        // 设置按钮点击事件
        //test
    }


    /**
     * A native method that is implemented by the 'opensls' native library,
     * which is packaged with this application.
     */
    public native String calculateMd5(String inputText);
    public native String calculateSha1(String inputText);
    private native String customMd5(String input);

}