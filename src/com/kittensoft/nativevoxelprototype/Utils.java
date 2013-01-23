package com.kittensoft.nativevoxelprototype;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGL10;

import android.util.Log;

public class Utils {
	private static String TAG = "utils";
	
	public static void checkEglError(String prompt, EGL10 egl) {
        int error;
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
            Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }
	
	public static String readFileAsString(InputStream in) throws Exception {
        String content = new String(readFileBinary(in));
        return content;
    }
	
	protected static byte buf[] = new byte[1024];
    protected static byte[] readFileBinary(InputStream streamIn) throws IOException {
        BufferedInputStream in = new BufferedInputStream(streamIn);

        ByteArrayOutputStream out = new ByteArrayOutputStream(10240);

        int len;
        while ((len = in.read(buf)) >= 0)
            out.write(buf, 0, len);
        in.close();
        return out.toByteArray();       
    }
}
