package com.example.testjoy;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;
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
	
	Socket client_ = null;
	OutputStream outToServer_ = null;
	InputStream inFromServer_ = null;

	public class ThreadTest extends Thread {

		public void run() {
			byte[] buf = new byte[4096];
			
			while(true){
				try {
					int len = inFromServer_.read(buf);
					
					if(len <= 0){
						inFromServer_.close();
						break;
					}
					
					sock_.InputData(buf);
					
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();					
					break;
				}				
			}
		}
	}

	private ParamSocket sock_ = new ParamSocket(this);
	ThreadTest testthr_ = new ThreadTest();
	
	boolean bpoint2_ = false;
	
	OnTouchListener listener_ = new OnTouchListener() {
		@Override
		public boolean onTouch(View v, MotionEvent event) {
			int action = event.getAction();
			int pointerCount = event.getPointerCount();

			switch(action){
			case MotionEvent.ACTION_POINTER_1_DOWN:
			case MotionEvent.ACTION_DOWN:
				Log.e("onTouch", "ACTION_DOWN(" + event.getX(0) + ", " + event.getY(0) + ")");
				for(BtnInfo info : MainActivity.this.btns){
					try {
						if(info.OnPress1(v, (int)event.getX(), (int)event.getY(), true)){
							break;
						}
					} catch (Exception e) {
						// TODO Auto-generated catch block
						for(BtnInfo info2 : MainActivity.this.btns){
							//info.GetLocation();
							info2.OnPress2(new Point(v.getLeft(), v.getTop()), 
									new Point((int)event.getX(), (int)event.getY()), true);
						}
						break;
					}
				}
			    break;
			case MotionEvent.ACTION_POINTER_1_UP:
			case MotionEvent.ACTION_UP:
				Log.e("onTouch", "ACTION_UP(" + event.getX(0) + ", " + event.getY(0) + ")");
				for(BtnInfo info : MainActivity.this.btns){
					try {
						if(info.OnPress1(v, (int)event.getX(), (int)event.getY(), false)){
							break;
						}
					} catch (Exception e) {
						// TODO Auto-generated catch block
						for(BtnInfo info2 : MainActivity.this.btns){
							//info.GetLocation();
							info2.OnPress2(new Point(v.getLeft(), v.getTop()), 
									new Point((int)event.getX(), (int)event.getY())
							, false);
						}
						break;
					}
				}
			    break;
			case MotionEvent.ACTION_MOVE:
			    break;
			case MotionEvent.ACTION_POINTER_2_DOWN:
				Log.e("onTouch", "ACTION_POINTER_2_DOWN(" + event.getX(1) + ", " + event.getY(1) + ")");
				for(BtnInfo info : MainActivity.this.btns){
					//info.GetLocation();
					info.OnPress2(new Point(v.getLeft(), v.getTop()), 
							new Point((int)event.getX(1), (int)event.getY(1)), true);
				}					
				break;	
			case MotionEvent.ACTION_POINTER_2_UP:
				Log.e("onTouch", "ACTION_POINTER_2_UP(" + event.getX(1) + ", " + event.getY(1) + ")");
				for(BtnInfo info : MainActivity.this.btns){
					//info.GetLocation();
					info.OnPress2(new Point(v.getLeft(), v.getTop()), 
							new Point((int)event.getX(1), (int)event.getY(1)), false);
				}					
				break;
			default:
				Log.e("onTouch", "other:" + action);
				break;
			}	
			
			return false;
		}
	};
	
	final int left_key_ = 0;
	final int right_key_ = 1;
	final int up_key_ = 2;
	final int down_key_ = 3;
	final int select_key_ = 4;
	final int start_key_ = 5;
	final int a_key_ = 6;
	final int b_key_ = 7;
	final int x_key_ = 8;
	final int y_key_ = 9;
	
	void keyword(int keyvalue, int keystatus){
		ParamArgs args = new ParamArgs();
		args.AddArgs(new ParamArg(keyvalue));
		args.AddArgs(new ParamArg(keystatus));
		sock_.CallFunction("key", args);
	}

    List<BtnInfo> btns = new ArrayList<BtnInfo>();

	TextView joytip_;

	void InitJoybtn() {
		joytip_ = (TextView) findViewById(R.id.joytip);

		BtnInfo rtmpbtn = new BtnInfo("rightjoybtn", this, R.id.rightjoybtn, true, listener_);
		
		btns.add(rtmpbtn);
		
		rtmpbtn.SetClickEvent(new BtnClick(){

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					joytip_.setText("右");
					keyword(right_key_, 0);
				}
				else
				{
					tip = " UP";
					joytip_.setText("");
					keyword(right_key_, 1);
				}
				Log.w("Keyword", "右" + tip);
			}
			
		});
	
		BtnInfo tmpbtn = new BtnInfo("leftjoybtn", this, R.id.leftjoybtn, true, listener_);
		
		tmpbtn.SetClickEvent(new BtnClick(){

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					joytip_.setText("左");
					keyword(left_key_, 0);
				}
				else
				{
					tip = " UP";
					joytip_.setText("");
					keyword(left_key_, 1);
				}
				Log.w("Keyword", "左" + tip);
			}
			
		});
		
		rtmpbtn.AddBrother(tmpbtn);
		
        tmpbtn = new BtnInfo("upjoybtn", this, R.id.upjoybtn, true, listener_);
		
		
		tmpbtn.SetClickEvent(new BtnClick(){

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					joytip_.setText("上");
					keyword(up_key_, 0);
				}
				else
				{
					tip = " UP";
					joytip_.setText("");
					keyword(up_key_, 1);
				}
				Log.w("Keyword", "上" + tip);
			}
			
		});
		
		rtmpbtn.AddBrother(tmpbtn);
		
        tmpbtn = new BtnInfo("downjoybtn", this, R.id.downjoybtn, true, listener_);
		
		
		tmpbtn.SetClickEvent(new BtnClick(){

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					joytip_.setText("下");
					keyword(down_key_, 0);
				}
				else
				{
					tip = " UP";
					joytip_.setText("");
					keyword(down_key_, 1);
				}
				Log.w("Keyword", "下" + tip);
			}
			
		});
		
		rtmpbtn.AddBrother(tmpbtn);
	}

	TextView funtip_;

	void InitFunbtn() {
		funtip_ = (TextView) findViewById(R.id.funtip);

		BtnInfo tmpbtn = new BtnInfo("imgselectbtn", this, R.id.imgselectbtn, false, listener_);

		btns.add(tmpbtn);

		tmpbtn.SetClickEvent(new BtnClick() {

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					funtip_.setText("选择");
					keyword(select_key_, 0);
				}
				else
				{
					tip = " UP";
					funtip_.setText("");
					keyword(select_key_, 1);
				}
				Log.w("Keyword", "选择" + tip);
			}

		});

		tmpbtn = new BtnInfo("imgstartbtn", this, R.id.imgstartbtn, false, listener_);

		btns.add(tmpbtn);

		tmpbtn.SetClickEvent(new BtnClick() {

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					funtip_.setText("开始");
					keyword(start_key_, 0);
				}
				else
				{
					tip = " UP";
					funtip_.setText("");
					keyword(start_key_, 1);
				}
				Log.w("Keyword", "开始" + tip);
			}

		});
	}

	TextView othertip_;

	void InitOtherbtn() {
		othertip_ = (TextView) findViewById(R.id.othertip);

		BtnInfo tmpbtn = new BtnInfo("imgabtn", this, R.id.imgabtn, false, listener_);

		btns.add(tmpbtn);

		tmpbtn.SetClickEvent(new BtnClick() {

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					othertip_.setText("A");
					keyword(a_key_, 0);
				}
				else
				{
					tip = " UP";
					othertip_.setText("");
					keyword(a_key_, 1);
				}
				Log.w("Keyword", "A" + tip);
			}

		});

		tmpbtn = new BtnInfo("imgbbtn", this, R.id.imgbbtn, false, listener_);

		btns.add(tmpbtn);

		tmpbtn.SetClickEvent(new BtnClick() {

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					othertip_.setText("B");
					keyword(b_key_, 0);
				}
				else
				{
					tip = " UP";
					othertip_.setText("");
					keyword(b_key_, 1);
				}
				Log.w("Keyword", "B" + tip);
			}

		});
		
		tmpbtn = new BtnInfo("imgxbtn", this, R.id.imgxbtn, false, listener_);

		btns.add(tmpbtn);

		tmpbtn.SetClickEvent(new BtnClick() {

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					othertip_.setText("X");
					keyword(x_key_, 0);
				}
				else
				{
					tip = " UP";
					othertip_.setText("");
					keyword(x_key_, 1);
				}
				Log.w("Keyword", "X" + tip);
			}

		});
		
		tmpbtn = new BtnInfo("imgybtn", this, R.id.imgybtn, false, listener_);

		btns.add(tmpbtn);

		tmpbtn.SetClickEvent(new BtnClick() {

			@Override
			public void OnClick(boolean bpress) {
				// TODO Auto-generated method stub
				String tip = "";
				if(bpress)
				{
					tip = " DOWN";
					othertip_.setText("Y");
					keyword(y_key_, 0);
				}
				else
				{
					tip = " UP";
					othertip_.setText("");
					keyword(y_key_, 1);
				}
				Log.w("Keyword", "Y" + tip);
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
		
		try {
			client_ = new Socket("10.192.1.192", 50000);
			
			outToServer_ = client_.getOutputStream();  
			inFromServer_ = client_.getInputStream();
			
			sock_.Create();
			testthr_.start();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			Log.e("Socket", e.getMessage());
			e.printStackTrace();
		}
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
		try {
			outToServer_.write(data);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void CheckCallback() {
		// TODO Auto-generated method stub
		Log.e("MainActivity", "CheckCallback");
	}

}
