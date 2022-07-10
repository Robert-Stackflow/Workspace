package com.example.activitytest

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_second.*

class SecondActivity : BaseActivity() {
    companion object {
        fun actionStart(context: Context, data1: String, data2: String) {
            val intent = Intent(context, SecondActivity::class.java)
            intent.putExtra("param1", data1)
            intent.putExtra("param2", data2)
            context.startActivity(intent)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_second)
//        //传递数据
//        val extraData = intent.getStringExtra("extra_data")
//        Log.d("SecondActivity", "extra data is $extraData")
//        //研究Activity启动模式:Standard || SingleTop || SingleTask
//        Log.d("SecondActivity", this.toString())
        //研究Activity启动模式:SingleInstance
        Log.d("SecondActivity", "Task id is $taskId")
        button_second.setOnClickListener {
            Toast.makeText(
                this,
                "Click button_second!",
                Toast.LENGTH_SHORT
            ).show()
//            //研究Activity启动模式:SingleTop || SingleTask
//            val intent = Intent(this, FirstActivity::class.java)
//            startActivity(intent)
            //研究Activity启动模式:SingleInstance
            val intent = Intent(this, ThirdActivity::class.java)
            startActivity(intent)
//            //传递数据
//            val intent = Intent()
//            intent.putExtra("data_return", "Hello FirstActivity!")
//            setResult(RESULT_OK, intent)
//            finish()
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d("SecondActivity", "onDestroy")
    }

    override fun onBackPressed() {
        val intent = Intent()
        intent.putExtra("data_return", "Hello FirstActivity!")
        setResult(RESULT_OK, intent)
        finish()
    }
}