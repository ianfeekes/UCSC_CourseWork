package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// MainMenu.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by: Khang Tran
// Notes: First panel to be displayed when app is opened. For navigation purposes
//-------------------------------------------------------------------------------------

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import ucsc.wildfirestudios.joes_push.R;

public class MainMenu extends AppCompatActivity {
    /* DATA --------------------------------------------------------------------------- */
    public Button exit;

    /* CONSTRUCTOR -------------------------------------------------------------------- */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button testBtn = (Button)findViewById(R.id.activityTwoBtn);

        testBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v)
            {
                Intent newIntent = new Intent(getApplicationContext(), DungeonLauncher.class);
                startActivity(newIntent);
            }
        });

        Button invt = (Button)findViewById(R.id.inventoryBtn);

        invt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent newIntent = new Intent(getApplicationContext(), InvtActivity.class);
                startActivity(newIntent);
            }
        });

        exitapp();
    }

    /* MODIFIERS (View methods) ------------------------------------------------------- */
    public void exitapp() {
        exit = findViewById(R.id.but_exit);
        exit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
                System.exit(0);
            }
        });
    }
}
