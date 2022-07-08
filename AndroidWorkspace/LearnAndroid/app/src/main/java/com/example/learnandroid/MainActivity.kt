package com.example.learnandroid

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.main_layout.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_layout)
        button1.setOnClickListener {
//            //显式Intent
//            val intent = Intent(this, SubActivity::class.java)
//            //隐式Intent
//            val intent = Intent("com.example.learnandroid.ACTION_START")
            //打开网页
            val intent = Intent(Intent.ACTION_VIEW)
            intent.data = Uri.parse("https://www.baidu.com")
            startActivity(intent)
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.add_item -> Toast.makeText(
                this, "You clicked Add",
                Toast.LENGTH_SHORT
            ).show()
            R.id.remove_item -> Toast.makeText(
                this, "You clicked Remove",
                Toast.LENGTH_SHORT
            ).show()
        }
        return true
    }

}