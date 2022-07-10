package com.example.activitytest

import android.os.Bundle
import android.util.Log

class ThirdActivity : BaseActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //研究Activity启动模式:SingleInstance
        Log.d("ThirdActivity", "Task id is $taskId")
        setContentView(R.layout.activity_third)
    }
}