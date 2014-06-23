package com.yeguang.paramprotocol;

public class ParamArg {	
	
	public ParamArg(char value){
		value_type_ = char_type_;
		char_value_ = value;
	}
	
	public ParamArg(short value){
		value_type_ = short_type_;
		short_value_ = value;
	}
	
	public ParamArg(int value){
		value_type_ = int_type_;
		int_value_ = value;
	}
	
	public ParamArg(long value){
		value_type_ = long_type_;
		long_value_ = value;
	}
	
	public ParamArg(float value){
		value_type_ = float_type_;
		float_value_ = value;
	}
	
	public ParamArg(double value){
		value_type_ = double_type_;
		double_value_ = value;
	}
	
	public ParamArg(String value){
		value_type_ = string_type_;
		string_value_ = value;
	}
	
	public ParamArg(byte[] value){
		value_type_ = bytearray_type_;
		bytearray_value_ = value;
	}
	
	public int getType(){
		return value_type_;
	}
	
	public char getCharValue() {
		return char_value_;
	}
	
	public short getShortValue() {
		return short_value_;
	}

	public int getIntValue() {
		return int_value_;
	}

	public long getLongValue() {
		return long_value_;
	}

	public float getFloatValue() {
		return float_value_;
	}

	public double getDoubleValue() {
		return double_value_;
	}

	public String getStringValue() {
		return string_value_;
	}

	public byte[] getByteArrayValue() {
		return bytearray_value_;
	}

	final int char_type_      = 1;
	final int short_type_     = 2;
	final int int_type_       = 3;
	final int long_type_      = 4;
	final int float_type_     = 5;
	final int double_type_    = 6;
	final int string_type_    = 7;
	final int bytearray_type_ = 8;
	
	private int value_type_ = 0;
	
	private char char_value_ = 0;
	private short short_value_ = 0;
	private int int_value_ = 0;
	private long long_value_ = 0;
	private float float_value_ = 0.0f;
	private double double_value_ = 0.0;
	private String string_value_ = null;
	private byte[] bytearray_value_ = null;
}
