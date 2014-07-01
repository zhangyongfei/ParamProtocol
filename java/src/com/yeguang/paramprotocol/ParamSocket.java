package com.yeguang.paramprotocol;

import java.util.HashMap;

public class ParamSocket {

	private long sock_ = 0;
	private ParamCallback callback_ = null;
	private static HashMap<Integer, ExecuteInterface> exectab_ = new HashMap<Integer, ExecuteInterface>();
	
	public ParamSocket(ParamCallback callback){
		callback_ = callback;
	}
	
	public native void Create();
	public native void Destroy();
	public native void CheckConn();
	public native void InputData(byte[] data);
	public native void CallFunction(String funname, ParamArgs args);
	private native int SaveFunction(String name);
	
	private long getSock() {
		return sock_;
	}

	private void setSock(long sock) {
		this.sock_ = sock;
	}
	
	private void SendCallback(byte[] data){
		callback_.SendCallback(data);
	}
	
	private void CheckCallback(){
		callback_.CheckCallback();
	}
	
	public void AddFunction(String name, ExecuteInterface executor)	{
		int funid = SaveFunction(name);
		exectab_.put(funid, executor);
	}
	
	private void Execute(int function_id, ParamArgs argsobj){ 		
		if(exectab_.containsKey(function_id)){
			exectab_.get(function_id).Execute(argsobj);
		}		
	}
	
}
