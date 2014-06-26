package com.example.testjoy;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.ImageButton;
import android.widget.TextView;

import com.yeguang.paramprotocol.ParamArg;
import com.yeguang.paramprotocol.ParamArgs;
import com.yeguang.paramprotocol.ParamCallback;
import com.yeguang.paramprotocol.ParamSocket;

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
			tmp.AddArgs(new ParamArg((char) 1));
			tmp.AddArgs(new ParamArg((short) 2));
			tmp.AddArgs(new ParamArg((int) 3));
			tmp.AddArgs(new ParamArg((long) 4));
			tmp.AddArgs(new ParamArg((float) 5));
			tmp.AddArgs(new ParamArg((double) 6));
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

	ImageButton rimgbt_;
	Bitmap rbitmap_;

	ImageButton limgbt_;
	Bitmap lbitmap_;

	ImageButton uimgbt_;
	Bitmap ubitmap_;

	ImageButton dimgbt_;
	Bitmap dbitmap_;

	TextView joytip_;

	void InitJoybtn() {
		joytip_ = (TextView) findViewById(R.id.joytip);

		rimgbt_ = (ImageButton) findViewById(R.id.rightjoybtn);
		rbitmap_ = ((BitmapDrawable) (rimgbt_.getBackground())).getBitmap();// 得到ImageButton的图片

		rimgbt_.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub

				try {
					if (rbitmap_.getPixel((int) (event.getX()),
							((int) event.getY())) == 0) {// 判断点击处像素的颜色是否为0，0表示没
						// //内容
						limgbt_.dispatchTouchEvent(event);
					} else {
//						Log.e("MainActivity",
//								"点击区有图像1    "
//										+ rbitmap_.getPixel(
//												(int) (event.getX()),
//												((int) event.getY())));

						joytip_.setText("右");
					}
				} catch (Exception e) {
					return false;
				}

				return false;
			}
		});

		limgbt_ = (ImageButton) findViewById(R.id.leftjoybtn);

		lbitmap_ = ((BitmapDrawable) (limgbt_.getBackground())).getBitmap();// 得到ImageButton的图片

		limgbt_.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub
				if (lbitmap_.getPixel((int) (event.getX()),
						((int) event.getY())) == 0) {// 判断点击处像素的颜色是否为0，0表示没
					// //内容
					uimgbt_.dispatchTouchEvent(event);
				} else {
					//Log.e("MainActivity",
					//		"点击区有图像2    "
					//				+ rbitmap_.getPixel((int) (event.getX()),
					//						((int) event.getY())));

					joytip_.setText("左");
				}
				return false;
			}
		});

		uimgbt_ = (ImageButton) findViewById(R.id.upjoybtn);

		ubitmap_ = ((BitmapDrawable) (uimgbt_.getBackground())).getBitmap();// 得到ImageButton的图片

		uimgbt_.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub
				if (ubitmap_.getPixel((int) (event.getX()),
						((int) event.getY())) == 0) {// 判断点击处像素的颜色是否为0，0表示没
					// //内容
					dimgbt_.dispatchTouchEvent(event);
				} else {
//					Log.e("MainActivity",
//							"点击区有图像3    "
//									+ rbitmap_.getPixel((int) (event.getX()),
//											((int) event.getY())));

					joytip_.setText("上");
				}
				return false;
			}
		});

		dimgbt_ = (ImageButton) findViewById(R.id.downjoybtn);

		dbitmap_ = ((BitmapDrawable) (dimgbt_.getBackground())).getBitmap();// 得到ImageButton的图片

		dimgbt_.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub
				if (dbitmap_.getPixel((int) (event.getX()),
						((int) event.getY())) == 0) {// 判断点击处像素的颜色是否为0，0表示没
					// //内容
					return false;
				} else {
//					Log.e("MainActivity",
//							"点击区有图像4    "
//									+ rbitmap_.getPixel((int) (event.getX()),
//											((int) event.getY())));

					joytip_.setText("下");
				}
				return false;
			}
		});
	}

	ImageButton selectbtn_;
	Bitmap selectbitmap_;

	ImageButton startbtn_;
	Bitmap startbitmap_;

	TextView funtip_;

	void InitFunbtn() {
		funtip_ = (TextView) findViewById(R.id.funtip);

		selectbtn_ = (ImageButton) findViewById(R.id.imgselectbtn);
		selectbitmap_ = ((BitmapDrawable) (selectbtn_.getDrawable())).getBitmap();// 得到ImageButton的图片

		selectbtn_.setOnTouchListener(new OnTouchListener() {

			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub
				if (selectbitmap_.getPixel((int) (event.getX()),
						((int) event.getY())) == 0) {// 判断点击处像素的颜色是否为0，0表示没
					// //内容
					return false;
				} else {
					funtip_.setText("选择");
				}
				return false;
			}

		});

		startbtn_ = (ImageButton) findViewById(R.id.imgstartbtn);
		startbitmap_ = ((BitmapDrawable) (startbtn_.getDrawable())).getBitmap();// 得到ImageButton的图片

		startbtn_.setOnTouchListener(new OnTouchListener() {

			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub
				if (startbitmap_.getPixel((int) (event.getX()),
						((int) event.getY())) == 0) {// 判断点击处像素的颜色是否为0，0表示没
					// //内容
					return false;
				} else {
					funtip_.setText("开始");
				}
				return false;
			}

		});

	}

	ImageButton abtn_;

	ImageButton bbtn_;

	ImageButton xbtn_;

	ImageButton ybtn_;

	TextView othertip_;

	void InitOtherbtn() {
		othertip_ = (TextView) findViewById(R.id.othertip);

		abtn_ = (ImageButton) findViewById(R.id.imgabtn);

		abtn_.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				othertip_.setText("A");
			}

		});

		bbtn_ = (ImageButton) findViewById(R.id.imgbbtn);

		bbtn_.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				othertip_.setText("B");
			}

		});

		xbtn_ = (ImageButton) findViewById(R.id.imgxbtn);

		xbtn_.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				othertip_.setText("X");
			}

		});

		ybtn_ = (ImageButton) findViewById(R.id.imgybtn);

		ybtn_.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				othertip_.setText("Y");
			}

		});
	}

	@Override 
	public boolean onTouchEvent(MotionEvent event) {
		if (event.getAction() == MotionEvent.ACTION_DOWN) {
			Log.v("Himi", "ACTION_DOWN(" + event.getX(0) + ", " + event.getY(0) + ")");
		} else if (event.getAction() == MotionEvent.ACTION_UP) {
			Log.v("Himi", "ACTION_UP");
		} else if (event.getAction() == MotionEvent.ACTION_MOVE) {
			//Log.v("Himi", "ACTION_MOVE");
		} else if (event.getAction() == MotionEvent.ACTION_POINTER_1_DOWN) {
			Log.v("Himi", "ACTION_POINTER_1_DOWN");
		} else if (event.getAction() == MotionEvent.ACTION_POINTER_2_DOWN) {
			Log.v("Himi", "ACTION_POINTER_2_DOWN(" + event.getX(1) + ", " + event.getY(1) + ")");
		}
		
		return true;// 这里一定要返回true！
	}

	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// requestWindowFeature(Window.FEATURE_NO_TITLE);//隐藏标题
		// getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
		// WindowManager.LayoutParams.FLAG_FULLSCREEN);//设置全屏

		setContentView(R.layout.activity_main);

		InitJoybtn();
		
		InitFunbtn();
		
		InitOtherbtn();

		/*
		 * sock_.Create();
		 * 
		 * 
		 * sock_.AddFunction("Test", new ExecuteInterface(){
		 * 
		 * @Override public void Execute(ParamArgs args) { // TODO
		 * Auto-generated method stub int i = 0; int cnt = args.getCount();
		 * 
		 * for(i = 0; i < cnt; i++) { ParamArg arg = args.getArg(i);
		 * switch(arg.getType()){ case ParamArg.boolean_type_: {
		 * Log.e("MainActivity", "boolean:" + arg.getBoolean() + "\n"); }break;
		 * case ParamArg.char_type_: { Log.e("MainActivity", "char:" +
		 * ((int)arg.getChar()) + "\n"); }break; case ParamArg.short_type_: {
		 * Log.e("MainActivity", "short:" + arg.getShort() + "\n"); }break; case
		 * ParamArg.int_type_: { Log.e("MainActivity", "int:" + arg.getInt() +
		 * "\n"); }break; case ParamArg.long_type_: { Log.e("MainActivity",
		 * "long:" + arg.getLong() + "\n"); }break; case ParamArg.float_type_: {
		 * Log.e("MainActivity", "float:" + arg.getFloat() + "\n"); }break; case
		 * ParamArg.double_type_: { Log.e("MainActivity", "double:" +
		 * arg.getDouble() + "\n"); }break; case ParamArg.string_type_: {
		 * Log.e("MainActivity", "string:" + arg.getString() + "\n"); }break;
		 * case ParamArg.bytearray_type_: { for (byte x : arg.getByteArray()) {
		 * Log.e("MainActivity", "bytearray:" + x + "\n"); } }break; } } }
		 * 
		 * });
		 * 
		 * testthr.start(); //
		 */
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
