/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.hellocpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import tv.ouya.console.api.OuyaController;
import android.os.Bundle;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class HelloCpp extends Cocos2dxActivity {

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		OuyaController.init(this);
	}

	static {
		System.loadLibrary("hellocpp");
	}

	public void onPause() {

		super.onPause();
	}

	public void onResume() {

		super.onResume();
	}

	public void onDestroy() {

		super.onDestroy();
	}

	// dpad up 19
	// dpad down 20
	// dpad link 21
	// dpad right 22

	// u 99
	// y 100
	// a 97
	// o 96

	// rd r2 105
	// ru r1 103
	// ld l2 104
	// lu l1 102

	// rc r3 106
	// lc l3 107

	// menu 82

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {

		boolean returnValue = true;
		int playerNum = OuyaController.getPlayerNumByDeviceId(event
				.getDeviceId());
		if (playerNum >= 0 && playerNum < 4) {
			keyPressed(playerNum, keyCode);
		}

		if (keyCode == 82) {
			super.onKeyDown(keyCode, event);
		}

		return returnValue;
	}

	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {

		boolean returnValue = true;
		int playerNum = OuyaController.getPlayerNumByDeviceId(event
				.getDeviceId());
		if (playerNum >= 0 && playerNum < 4) {
			keyReleased(playerNum, keyCode);
		}

		if (keyCode == 82) {
			super.onKeyUp(keyCode, event);
		}

		return returnValue;
	}

	@Override
	public boolean onGenericMotionEvent(MotionEvent event) {

		boolean returnValue = true;

		if ((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) == 0) {
			// Not a joystick movement, so ignore it.
			returnValue = false;
		} else {
			int playerNum = OuyaController.getPlayerNumByDeviceId(event
					.getDeviceId());

			// Joystick
			if ((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) != 0) {

				float LS_X = event.getAxisValue(OuyaController.AXIS_LS_X);
				float LS_Y = event.getAxisValue(OuyaController.AXIS_LS_Y);

				float RS_X = event.getAxisValue(OuyaController.AXIS_RS_X);
				float RS_Y = event.getAxisValue(OuyaController.AXIS_RS_Y);

				if (LS_X * LS_X + LS_Y * LS_Y < OuyaController.STICK_DEADZONE
						* OuyaController.STICK_DEADZONE) {
					LS_X = LS_Y = 0.0f;
				}

				if (RS_Y * RS_Y + RS_X * RS_X < OuyaController.STICK_DEADZONE
						* OuyaController.STICK_DEADZONE) {
					RS_X = RS_Y = 0.0f;
				}

				controllerMotion(playerNum, LS_X, LS_Y, RS_X, RS_Y);
			}
		}
		return returnValue;
	}

	static {
		try {
			System.loadLibrary("hellocpp");
		} catch (UnsatisfiedLinkError use) {
			Log.e("JNI", "WARNING: Could not load hellocpp.so");
		}
	}

	// JNI
	public native void keyPressed(int player, int keyCode);

	public native void keyReleased(int player, int keyCode);

	public native void controllerMotion(int player, float LS_X, float LS_Y,
			float RS_X, float RS_Y);

	// life cycle functions
	public native void onResumeJNI();

	public native void onPauseJNI();

	public native void onDestroyJNI();
}