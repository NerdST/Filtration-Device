package com.example.filtrationdeviceapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import java.io.BufferedReader
import java.io.InputStreamReader
import java.lang.Exception
import java.net.HttpURLConnection
import java.net.URL

class MainActivity : AppCompatActivity() {

    private lateinit var bodyText: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        bodyText = findViewById(R.id.bodyText)
        fetchOnlineText("https://raw.githubusercontent.com/Patater/qso-generator/master/corpora/navy-seal-copypasta.txt\n")
    }

    private fun fetchOnlineText(url: String) {
        val textView = bodyText
        val chunkSize = 1024 // Adjust chunk size as needed

        val thread = Thread {
            val connection = URL(url).openConnection()
            val inputStream = connection.getInputStream()
            val buffer = ByteArray(chunkSize)
            val builder = StringBuilder()
            var totalBytesRead = 0

            while (inputStream.read(buffer) != -1) {
                val bytesRead = inputStream.read(buffer)
                if (bytesRead > 0) {
                    if (totalBytesRead < chunkSize) {
                        builder.append(String(buffer, 0, bytesRead))
                        totalBytesRead += bytesRead
                    }
                }
            }

            runOnUiThread {
                textView.text = builder.toString()
            }
            inputStream.close()
        }
        thread.start()
    }
}
