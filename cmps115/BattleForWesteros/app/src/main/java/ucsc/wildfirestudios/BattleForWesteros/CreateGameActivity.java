package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// CreateGameActivity.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by: 
// Notes: Launches from menu into GamePanel
//-------------------------------------------------------------------------------------

import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Window;
import android.view.WindowManager;

public class CreateGameActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // creates full screen 
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);

        // sets display size and basic structure data
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        
        // sets screen width and height
        Constants.SCREEN_WIDTH = dm.widthPixels;
        Constants.SCREEN_HEIGHT = dm.heightPixels;

        // sets screen content to GamePanel
        String sessionId= getIntent().getStringExtra("game");
        if(sessionId.equals("scripId")) setContentView(new ScriptingPanel(this));
        setContentView(new GamePanel(this));
    }

}
