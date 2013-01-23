package com.kittensoft.nativevoxelprototype;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class GameRendererJavaBridge implements GLSurfaceView.Renderer {
	private String fShader, vShader, shipRawData, bulletRawData, asteroidRawData;
	
	public GameRendererJavaBridge(String vShader, String fShader, String shipRawData, String bulletRawData, String asteroidRawData) {
		this.vShader = vShader;
		this.fShader = fShader;
		this.shipRawData = shipRawData;
		this.bulletRawData = bulletRawData;
		this.asteroidRawData = asteroidRawData;
	}
	
    public void onDrawFrame(GL10 gl) {
    	NativeVoxelPrototypeLib.step();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
    	NativeVoxelPrototypeLib.init(width, height, vShader, fShader, shipRawData, bulletRawData, asteroidRawData);
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // Do nothing.
    }
}