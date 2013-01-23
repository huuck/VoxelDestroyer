package com.kittensoft.nativevoxelprototype;

import android.os.Bundle;
import android.app.Activity;

public class ActivityMain extends Activity {

	GameJavaBridge game;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        game = new GameJavaBridge(getApplicationContext());
        
        setContentView(game);
    }

    @Override protected void onPause() {
        super.onPause();
        game.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        game.onResume();
    }
}
