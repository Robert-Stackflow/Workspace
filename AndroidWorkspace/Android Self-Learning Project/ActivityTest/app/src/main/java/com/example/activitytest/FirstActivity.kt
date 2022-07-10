package com.example.activitytest

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_first.*

class FirstActivity : BaseActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
//        //研究Activity启动模式:Standard || SingleTop || SingleTask
//        Log.d("FirstActivity", this.toString())
        //研究Activity启动模式:SingleInstance
        Log.d("FirstActivity", "Task id is $taskId")
        setContentView(R.layout.activity_first)
        button_first.setOnClickListener {
            Toast.makeText(
                this,
                "Click button_first!",
                Toast.LENGTH_SHORT
            ).show()
//            //研究Activity启动模式:Standard
//            val intent = Intent(this, FirstActivity::class.java)
            //研究Activity启动模式:SingleTop || SingleTask
            val intent = Intent(this, SecondActivity::class.java)
            startActivity(intent)
//            //显示Intent
//            val intent = Intent(this, SecondActivity::class.java)
//            startActivity(intent)
//            //显示Intent传递数据
//            val intent = Intent(this, SecondActivity::class.java)
//            intent.putExtra("extra_data", "Hello SecondActivity!")
//            startActivity(intent)
//            //显示Intent回传数据
//            val intent = Intent(this, SecondActivity::class.java)
//            startActivityForResult(intent, 1)
//            //隐式Intent
//            val intent = Intent("com.example.activitytest.ACTION_START")
//            intent.addCategory("com.example.activitytest.MY_CATEGORY")
//            startActivity(intent)
//            //隐式Intent打开网页
//            val intent = Intent(Intent.ACTION_VIEW)
//            intent.data = Uri.parse("https://www.github.com")
//            startActivity(intent)
//            //隐式Intent拨号
//            val intent = Intent(Intent.ACTION_DIAL)
//            intent.data = Uri.parse("tel:10086")
//            startActivity(intent)
//            //传递数据的最佳写法
//            SecondActivity.actionStart(this, "data1", "data2")
        }
    }

    override fun onRestart() {
        super.onRestart()
        Log.d("FirstActivity", "onRestart")
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        when (requestCode) {
            1 -> if (resultCode == RESULT_OK) {
                val returnedData = data?.getStringExtra("data_return")
                Log.d("FirstActivity", "returned data is $returnedData")
            }
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.item_first -> Toast.makeText(
                this,
                "Click item_first!",
                Toast.LENGTH_SHORT
            ).show()
            R.id.item_second -> Toast.makeText(
                this,
                "Click item_second!",
                Toast.LENGTH_SHORT
            ).show()
        }
        return true
    }
}