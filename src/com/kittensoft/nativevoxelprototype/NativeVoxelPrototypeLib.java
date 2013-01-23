package com.kittensoft.nativevoxelprototype;

public class NativeVoxelPrototypeLib {

    static {
        System.loadLibrary("NativeVoxelPrototype");
    }

   /**
    * @param width the current view width
    * @param height the current view height
    * @param fShader 
    * @param vShader 
    */
    public static native void init(int width, int height, String vShader, String fShader, String shipRawData, String bulletRawData, String asteroidRawData);
    public static native void HandleMouseInput(int inputType);
    public static native void step();
}