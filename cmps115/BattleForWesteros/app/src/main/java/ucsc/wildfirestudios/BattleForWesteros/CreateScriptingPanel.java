package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// CreateScriptingPanel.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by:
// Notes: This class is used to display a short game introduction prior to the players
//        beginning their game experience so that some very brief plot is introduced
//-------------------------------------------------------------------------------------

import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Window;
import android.view.WindowManager;

public class CreateScriptingPanel extends Activity {

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
        setContentView(new GamePanel(this));
    }

}
