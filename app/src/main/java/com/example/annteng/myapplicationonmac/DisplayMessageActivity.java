package com.example.annteng.myapplicationonmac;

import android.app.Fragment;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import java.io.File;


public class DisplayMessageActivity extends ActionBarActivity {

    private native String helloString(String toWhat);
    private native String decodeVideoFF(String outfilename, String infilename);

    private static final String sOutFileName = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS)
            + File.separator + "out.yuv";
    private static final String sInFileName = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS)
            + File.separator + "aa.h264";
   // private static final String sOutFileName = Environment.getExternalStorageDirectory()
     //       + File.separator + "out.bmp";
   // private static final String sInFileName = "assets/1-1.mp4";
    //private static final String sInFileName = Environment.getExternalStorageDirectory()
    //        + File.separator + "file_dump_test/1.mp4";

    static {
        System.loadLibrary("HelloWorldJni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       // TextView textView = (TextView) findViewById(R.id.display_message);

        setContentView(R.layout.activity_display_message);
       // super.setText(helloString("MagicJNI"));
        TextView textView = (TextView) findViewById(R.id.display_message);

        Log.d("jni_test", "filename = " + sOutFileName);
        Log.d("jni_test", Environment.getExternalStorageDirectory().toString());
        File path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
        String path_str = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS) + File.separator + "dump_bmp";
        Log.d("jni_test", path.toString());
        File file = new File(path_str);
        if (!file.exists())
            file.mkdir();

        File file2 = new File(sInFileName.toString());
        boolean exi = file2.exists();
        Log.d("jni_test", "file existsj = " + exi);
        textView.setText(helloString("MagicJNI!!"));
     //   iv.setImageBitmap(img);

    }

/*
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_display_message, menu);
        return true;
    }
*/

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }



    public void decodeVideo(View view) {
        // Do something in response to button
        //PhotoDecodeRunnable phototask = new PhotoDecodeRunnable();
        //phototask.run();
        Log.d("jni_test", "before decode video");
       // decodeVideoFF(sOutFileName, sInFileName);
        new DecodeFileTask().execute(sOutFileName, sInFileName);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {

        public PlaceholderFragment() { }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
            //View rootView = inflater.inflate(R.layout.fragment_display_message,
            //        container, false);
            //return rootView;
            return null;
        }
    }


    private class DecodeFileTask extends AsyncTask<String, Integer, Long> {
        // Do the long-running work in here
        protected Long doInBackground(String... filenames) {
            int count = filenames.length;
            long totalSize = 0;
           // for (int i = 0; i < count; i++) {
               // totalSize += Downloader.downloadFile(urls[i]);
               // publishProgress((int) ((i / (float) count) * 100));
                // Escape early if cancel() is called
             //   if (isCancelled()) break;
            //}
            decodeVideoFF(sOutFileName, sInFileName);
            return totalSize;
        }

        // This is called each time you call publishProgress()
        protected void onProgressUpdate(Integer... progress) {
           // setProgressPercent(progress[0]);
        }

        // This is called when doInBackground() is finished
        protected void onPostExecute(Long result) {
            //showNotification("Downloaded " + result + " bytes");
        }
    }

    class PhotoDecodeRunnable implements Runnable {

        @Override
        public void run() {
        /*
         * Code you want to run on the thread goes here
         */
            android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);

       // while(true) {
       //     Log.d("jni_test", "thread running");
      //  }
          //  decodeVideoFF(sOutFileName, sInFileName);

        }

    }

}


