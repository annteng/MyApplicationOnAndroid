package com.example.annteng.myapplicationonmac;

import android.app.Fragment;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.io.File;


public class DisplayMessageActivity extends ActionBarActivity {

    private native String helloString(String toWhat, String outfilename, String infilename);

    private static final String sOutFileName = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS)
            + File.separator + "out.bmp";
   // private static final String sOutFileName = Environment.getExternalStorageDirectory()
     //       + File.separator + "out.bmp";
    private static final String sInFileName = "assets/1.mp4";
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
        Log.d("jni_test", path.toString());
        File file = new File(path, "DemoPicture.jpg");

        textView.setText(helloString("MagicJNI!!", sOutFileName, sInFileName));
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
}
