package com.example.testjoy;

import com.yeguang.paramprotocol.ExecuteInterface;
import com.yeguang.paramprotocol.ParamArg;
import com.yeguang.paramprotocol.ParamArgs;
import com.yeguang.paramprotocol.ParamCallback;
import com.yeguang.paramprotocol.ParamSocket;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity implements ParamCallback {

	static {
		try {
			Log.e("MainActivity", System.getProperty("java.library.path"));
			System.loadLibrary("ParamProtocol");
		} catch (UnsatisfiedLinkError ule) {
			System.err.println("WARNING: Could not load library!");
		}
	}
	
	public class ThreadTest extends Thread {

	    public void run() {
	    	ParamArgs tmp = new ParamArgs();
	    	tmp.AddArgs(new ParamArg(false));
	    	tmp.AddArgs(new ParamArg((char)1));
	    	tmp.AddArgs(new ParamArg((short)2));
	    	tmp.AddArgs(new ParamArg((int)3));
	    	tmp.AddArgs(new ParamArg((long)4));
	    	tmp.AddArgs(new ParamArg((float)5));
	    	tmp.AddArgs(new ParamArg((double)6));
	    	byte[] array = new byte[1];
	    	array[0] = 7;
	    	tmp.AddArgs(new ParamArg(array));
	    	tmp.AddArgs(new ParamArg("Hello World!"));	    	
	    	MainActivity.this.sock_.CallFunction("Test", tmp);
	    	MainActivity.this.sock_.CheckConn();
	    }
	}
	
	private ParamSocket sock_ = new ParamSocket(this);
	ThreadTest testthr = new ThreadTest();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);		
		
		sock_.Create();
		
		//*
		sock_.AddFunction("Test", new ExecuteInterface(){

			@Override
			public void Execute(ParamArgs args) {
				// TODO Auto-generated method stub
				int i = 0;
				int cnt = args.getCount();
				
				for(i = 0; i < cnt; i++)
				{
					ParamArg arg = args.getArg(i);
					switch(arg.getType()){
					case ParamArg.boolean_type_:
					{
						Log.e("MainActivity", "boolean:" + arg.getBoolean() + "\n");
					}break;
					case ParamArg.char_type_:
					{
						Log.e("MainActivity", "char:" + ((int)arg.getChar()) + "\n");
					}break;
					case ParamArg.short_type_:
					{
						Log.e("MainActivity", "short:" + arg.getShort() + "\n");
					}break;
					case ParamArg.int_type_:
					{
						Log.e("MainActivity", "int:" + arg.getInt() + "\n");
					}break;
					case ParamArg.long_type_:
					{
						Log.e("MainActivity", "long:" + arg.getLong() + "\n");
					}break;
					case ParamArg.float_type_:
					{
						Log.e("MainActivity", "float:" + arg.getFloat() + "\n");
					}break;
					case ParamArg.double_type_:
					{
						Log.e("MainActivity", "double:" + arg.getDouble() + "\n");
					}break;
					case ParamArg.string_type_:
					{
						Log.e("MainActivity", "string:" + arg.getString() + "\n");
					}break;
					case ParamArg.bytearray_type_:
					{
						 for (byte x : arg.getByteArray()) { 
							 Log.e("MainActivity", "bytearray:" + x + "\n");
				         } 						
					}break;
					}
				}
			}
			
		});
		
		testthr.start();
		//*/
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void SendCallback(byte[] data) {
		// TODO Auto-generated method stub
		sock_.InputData(data);		
	}

	@Override
	public void CheckCallback() {
		// TODO Auto-generated method stub
		Log.e("MainActivity", "CheckCallback");
	}

}
