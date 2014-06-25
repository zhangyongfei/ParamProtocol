package com.yeguang.paramprotocol;

import java.util.ArrayList;
import java.util.List;

public class ParamArgs {
    
	private List<ParamArg> args_ = new ArrayList<ParamArg>();
	
	public ParamArgs() {
		
	}
	
	public void AddArgs(ParamArg arg){
		args_.add(arg);
	}
	
	public int getCount() {
		return args_.size();
	}
	
	public ParamArg getArg(int index){
		return args_.get(index);
	}
	
}
