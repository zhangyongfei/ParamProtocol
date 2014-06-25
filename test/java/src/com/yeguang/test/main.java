package com.yeguang.test;

import com.yeguang.paramprotocol.*;

public class main implements ParamCallback {

	static {
		try {			
			System.loadLibrary("ParamProtocol");
		} catch (UnsatisfiedLinkError ule) {
			System.err.println("WARNING: Could not load library!");
		}
	}
	
	/**
	 * 使用继承java.lang.Thread类的方式创建一个线程
	 * 
	 * @author DreamSea 2011-12-29 20:17:06
	 */
	public class ThreadTest extends Thread {

	    /**
	     * 重写（Override）run()方法 JVM会自动调用该方法
	     */
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
	    	main.this.sock_.CallFunction("Test", tmp);
	    	main.this.sock_.CheckConn();
	    }
	}
	
	private ParamSocket sock_ = new ParamSocket(this);
	ThreadTest testthr = new ThreadTest();
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		main testmain = new main();
		
		
		
		testmain.sock_.Create();
		
		testmain.sock_.AddFunction("Test", new ExecuteInterface(){

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
						System.out.print("boolean:" + arg.getBoolean() + "\n");
					}break;
					case ParamArg.char_type_:
					{
						System.out.print("char:" + ((int)arg.getChar()) + "\n");
					}break;
					case ParamArg.short_type_:
					{
						System.out.print("short:" + arg.getShort() + "\n");
					}break;
					case ParamArg.int_type_:
					{
						System.out.print("int:" + arg.getInt() + "\n");
					}break;
					case ParamArg.long_type_:
					{
						System.out.print("long:" + arg.getLong() + "\n");
					}break;
					case ParamArg.float_type_:
					{
						System.out.print("float:" + arg.getFloat() + "\n");
					}break;
					case ParamArg.double_type_:
					{
						System.out.print("double:" + arg.getDouble() + "\n");
					}break;
					case ParamArg.string_type_:
					{
						System.out.print("string:" + arg.getString() + "\n");
					}break;
					case ParamArg.bytearray_type_:
					{
						 for (byte x : arg.getByteArray()) { 
							 System.out.print("bytearray:" + x + "\n");
				         } 						
					}break;
					}
				}
			}
			
		});
		
		testmain.testthr.start();
		
		while(true){
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				testmain.sock_.Destroy();
				System.exit(0);
			}
		}
		
	}

	@Override
	public void SendCallback(byte[] data) {
		// TODO Auto-generated method stub
		sock_.InputData(data, data.length);
	}

	@Override
	public void CheckCallback() {
		// TODO Auto-generated method stub
		System.out.print("CheckCallback");
	}
	


}
