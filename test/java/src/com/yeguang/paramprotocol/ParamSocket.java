package com.yeguang.paramprotocol;

public class ParamSocket {

	private long sock_ = 0;
	
	public ParamSocket(){
		
	}
	
	public native void Create();
	public native void Destroy();
	public native void CheckConn();
	public native void InputData(byte[] data);
	public native void CallFunction(String funname, ParamArgs args);
	
	public long getSock() {
		return sock_;
	}

	public void setSock(long sock) {
		this.sock_ = sock;
	}
}
