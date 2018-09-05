package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// DungeonLauncher.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by: Joe Jiang
// Notes: 
//-------------------------------------------------------------------------------------

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

import ucsc.wildfirestudios.joes_push.R;

public class DungeonLauncher extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // displays second menu screen
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);                              // displays .xml file

        ImageButton home = (ImageButton)findViewById(R.id.but_menu);           // home button
        ImageButton game = (ImageButton)findViewById(R.id.but_fight);          // fight button
        ImageButton game2 = (ImageButton)findViewById(R.id.but_fight2);        // scripting button (for now)


        // if home button is clicked, goes back to home menu
        home.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent newIntent = new Intent(getApplicationContext(), MainMenu.class);
                finish();
                System.exit(0);
                startActivity(newIntent);
            }
        });

        // if dungeon button is clicked, goes into game screen
        game.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent newIntent = new Intent(getApplicationContext(), CreateGameActivity.class);
                newIntent.putExtra("game", "gameId");
                startActivity(newIntent);
            }
        });

        /*Button Go to Dungeon2*/
        game2.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent newIntent = new Intent(getApplicationContext(), CreateGameActivity2.class);
                newIntent.putExtra("game2", "gameId2");
                startActivity(newIntent);
            }
        });

    }
}
