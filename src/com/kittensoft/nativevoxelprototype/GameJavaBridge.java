package com.kittensoft.nativevoxelprototype;

import android.R.bool;
import android.content.Context;
import android.content.res.Resources.NotFoundException;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.GestureDetector;
import android.view.GestureDetector.SimpleOnGestureListener;
import android.view.MotionEvent;
import android.widget.Toast;


public class GameJavaBridge extends GLSurfaceView {
	private static String TAG = "gameJavaBridge";
	
	String vShader;
	String fShader;
	String shipRawData;
	String bulletRawData;
	private String asteroidRawData;
	GestureDetector gestureDetector;

	
	public GameJavaBridge(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		
		init(false, 4, 0);
		gestureDetector = new GestureDetector(new MyGestureDetector());
	}

	private void init(boolean translucent, int depth, int stencil) {

//        /* By default, GLSurfaceView() creates a RGB_565 opaque surface.
//         * If we want a translucent one, we should change the surface's
//         * format here, using PixelFormat.TRANSLUCENT for GL Surfaces
//         * is interpreted as any 32-bit surface with alpha by SurfaceFlinger.
//         */
//        if (translucent) {
//            this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
//        }
//
//        /* Load the shader files and pass onto native code.
//         */
        try {
			vShader = Utils.readFileAsString(this.getContext().getResources().openRawResource(R.raw.vshader));
			fShader = Utils.readFileAsString(this.getContext().getResources().openRawResource(R.raw.fshader));
			shipRawData = Utils.readFileAsString(this.getContext().getResources().openRawResource(R.raw.spaceship));
			bulletRawData = Utils.readFileAsString(this.getContext().getResources().openRawResource(R.raw.bullet));
			asteroidRawData = Utils.readFileAsString(this.getContext().getResources().openRawResource(R.raw.asteroid));
        } catch (NotFoundException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
//        
        /* Setup the context factory for 2.0 rendering.
         * See ContextFactory class definition below
         */
        setEGLContextFactory(new ContextFactory());

        /* We need to choose an EGLConfig that matches the format of
         * our surface exactly. This is going to be done in our
         * custom config chooser. See ConfigChooser class definition
         * below.
         */
        setEGLConfigChooser( translucent ?
                             new ConfigChooser(8, 8, 8, 8, depth, stencil) :
                             new ConfigChooser(5, 6, 5, 0, depth, stencil) );
//
//        /* Set the renderer responsible for frame rendering */
//		 setEGLContextClientVersion(2);
	     
         // Set the renderer to our demo renderer, defined below.
        setRenderer(new GameRendererJavaBridge(vShader, fShader, shipRawData, bulletRawData, asteroidRawData));
    }
	
	 @Override
    public boolean onTouchEvent(MotionEvent e) {
		 float xGrad = 0, yGrad = 0;
		 
		 if(e.getHistorySize() > 0) {
			 xGrad = e.getX() - e.getHistoricalX(0);
			 yGrad = e.getY() - e.getHistoricalY(0);
		 }
		 
		 gestureDetector.onTouchEvent(e);
		 return true;
    }
}

class MyGestureDetector extends SimpleOnGestureListener {
	private static final int SWIPE_MIN_DISTANCE = 120;
	private static final int SWIPE_MAX_OFF_PATH = 250;
	private static final int SWIPE_THRESHOLD_VELOCITY = 200;
	
	private static int SWIPE_LEFT = 1;
	private static int SWIPE_RIGHT = 2;
	private static int DOUBLE_TAP = 3;
	
    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        try {
            if (Math.abs(e1.getY() - e2.getY()) > SWIPE_MAX_OFF_PATH)
                return false;
            // right to left swipe
            if(e1.getX() - e2.getX() > SWIPE_MIN_DISTANCE && Math.abs(velocityX) > SWIPE_THRESHOLD_VELOCITY) {
            	NativeVoxelPrototypeLib.HandleMouseInput(SWIPE_LEFT);
            }  else if (e2.getX() - e1.getX() > SWIPE_MIN_DISTANCE && Math.abs(velocityX) > SWIPE_THRESHOLD_VELOCITY) {
            	NativeVoxelPrototypeLib.HandleMouseInput(SWIPE_RIGHT);
            }
        } catch (Exception e) {
            // nothing
        }
        return false;
    }
    
    @Override
    public boolean onDoubleTap(MotionEvent e) {
    	Log.d("doubletap", "doubletap");
    	NativeVoxelPrototypeLib.HandleMouseInput(DOUBLE_TAP);
    	return false;
    }

}
