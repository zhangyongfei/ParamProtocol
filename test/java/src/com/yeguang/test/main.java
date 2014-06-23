package com.yeguang.test;

import com.yeguang.paramprotocol.*;

public class main implements ExecuteInterface, ParamCallback {

	static {
		
		try {
			System.loadLibrary("ParamProtocol");
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
	
	private ParamSocket sock_ = new ParamSocket();
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		main testmain = new main();
		ParamExecutor execute = new ParamExecutor();
		
		execute.AddFunction("Test", testmain);
				
		testmain.sock_.Create(testmain);
		ParamArgs tmp = new ParamArgs();
		testmain.sock_.CallFunction("Test", tmp);
	}

	@Override
	public void Execute(ParamArgs args) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void SendCallback(byte[] data) {
		// TODO Auto-generated method stub
		sock_.InputData(data);
	}

	@Override
	public void CheckCallback() {
		// TODO Auto-generated method stub
		
	}

}
