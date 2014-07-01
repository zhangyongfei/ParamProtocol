package com.example.testjoy;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.graphics.Point;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
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
	
	boolean bpoint2_ = false;
	
	OnTouchListener listener_ = new OnTouchListener() {
		@Override
		public boolean onTouch(View v, MotionEvent event) {
			//joytip_.setText("");
			//funtip_.setText("");
			//othertip_.setText("");
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
				//Log.e("onTouch", "ACTION_MOVE");
				/*for(BtnInfo info : MainActivity.this.btns){
					try {
						if(info.OnClick1(v, (int)event.getX(), (int)event.getY())){
							break;
						}
					} catch (Exception e) {
						// TODO Auto-generated catch block
						for(BtnInfo info2 : MainActivity.this.btns){
							//info.GetLocation();
							info2.OnClick2(new Point(v.getLeft(), v.getTop()), 
									new Point((int)event.getX(), (int)event.getY()));
						}
						break;
					}
				}
				
				if(pointerCount == 2){
					for(BtnInfo info : MainActivity.this.btns){
						//info.GetLocation();
						info.OnClick2(new Point(v.getLeft(), v.getTop()), 
								new Point((int)event.getX(1), (int)event.getY(1)));
					}
				}*/
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
				}
				else
				{
					tip = " UP";
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
