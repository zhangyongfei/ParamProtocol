package com.example.testjoy;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.graphics.drawable.BitmapDrawable;
import android.util.Log;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageButton;

public class BtnInfo {

	String name_;
	ImageButton btn_;
	Bitmap btnbmp_;
	BtnClick clickevent_ = null;
	boolean bbkg_= false;
	List<BtnInfo> brothers_ = new ArrayList<BtnInfo>();

	public BtnInfo(String name, Activity activity, int id, boolean isbkg, OnTouchListener listener) {
		name_ = name;
		btn_ = (ImageButton) activity.findViewById(id);
		if(isbkg){
			btnbmp_ = ((BitmapDrawable) (btn_.getBackground())).getBitmap();// 得到ImageButton的图片
		}
		else{
			btnbmp_ = ((BitmapDrawable) (btn_.getDrawable())).getBitmap();// 得到ImageButton的图片
		}
		
		bbkg_ = isbkg;
		
		btn_.setOnTouchListener(listener);
	}
	
	public void SetClickEvent(BtnClick clickevent){
		clickevent_ = clickevent;
	}
	
	public void AddBrother(BtnInfo brother){
		brothers_.add(brother);
	}
	
	public void GetLocation(){
		int[] location = new int[2];
		btn_.getLocationOnScreen(location);
		Log.e("onTouch", name_ + " WH:(" + btn_.getMeasuredWidth() + ", " + btn_.getMeasuredHeight() + ")");
		Log.e("onTouch", name_ + ":(" + btn_.getLeft() + ", " + btn_.getTop() + ")");
		Log.e("onTouch", name_ + " Raw:(" + location[0] + ", " + location[1] + ")");
	}
	
	private boolean IsMyself(View v){
		if(btn_ == v){
			return true;
		}
		
		return false;
	}
	
	private boolean CheckBrother(View v, int x, int y, boolean bpress){
		for(BtnInfo info : brothers_){
			if(info.bbkg_){
				if (info.btnbmp_.getPixel(x, y) != 0) {// 判断点击处像素的颜色是否为0，0表示没有
					if(info.clickevent_ != null){
						info.clickevent_.OnClick(bpress);
					}
		            return true;
				}			
			}
		}
		
		return false;
	}
	
	public boolean OnPress2(Point ctrl, Point p2, boolean bpress){
		int rawx = p2.x + ctrl.x;
		int rawy = p2.y + ctrl.y;
		
		if(btn_.getLeft() <= rawx && btn_.getRight() >= rawx 
		&& btn_.getTop() <= rawy && btn_.getBottom() >= rawy){
			
			int x = rawx - btn_.getLeft();
			int y = rawy - btn_.getTop();
			CheckBrother(btn_, x, y, bpress);
			
			if(bbkg_){
				if (btnbmp_.getPixel(x, y) != 0) {// 判断点击处像素的颜色是否为0，0表示没有
					if(clickevent_ != null){
						clickevent_.OnClick(bpress);
					}
		            return true;
				}			
			}
			else{
				if(clickevent_ != null){
					clickevent_.OnClick(bpress);
				}
	            return true;
			}
		}
		
		return false;
	}

	public boolean OnPress1(View v, int x, int y, boolean bpress) throws Exception {
		try{
			if(!IsMyself(v)){
				return false;
			}
			
			if(CheckBrother(v, x, y, bpress)){
				return true;
			}
			
			if(bbkg_){
				if (btnbmp_.getPixel(x, y) != 0) {// 判断点击处像素的颜色是否为0，0表示没有
					if(clickevent_ != null){
						clickevent_.OnClick(bpress);
					}
		            return true;
				}			
			}
			else{
				if(clickevent_ != null){
					clickevent_.OnClick(bpress);
				}
	            return true;
			}
		
		}catch(Exception e){
			Log.e("BtnInfo", e.getMessage() + "(" + x + ", " + y + ")");
			throw e;
		} 

		return false;
	}

}
