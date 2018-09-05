package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// InvtActivity.java
// Wildfire Studios
// Created by: Khang Tran
// Modified by:
// Notes: Inventory menu to equip items before combat.
//-------------------------------------------------------------------------------------

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.Toast;

import ucsc.wildfirestudios.joes_push.R;

public class InvtActivity extends AppCompatActivity {

    public static int returnWeapon = 0; // Default weapon is Rusty Sword
    public static int returnArmor = 0; // Default armor is Leather Armor

    // Displays item names
    String[] itemsList = {"Rusty Sword (+5 atk)", "Steel Sword (+7 atk)", "Battle Axe (+10 atk)", "God Killer (for testing)",
            "Leather Armor (+20 def)", "Hardened Leather Armor (+30 def)", "Steel Armor (+50 def)", "God Armor (for testing)"};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_invt);

        // Displays items in a list
        ListAdapter theAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, itemsList);
        ListView invtDisplay = (ListView) findViewById(R.id.invtDisplay);
        invtDisplay.setAdapter(theAdapter);

        // Allows items to be clicked and returns the index of the item(s) to be equipped when combat begins
        invtDisplay.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int i, long l) {
                Toast.makeText(InvtActivity.this, itemsList[i] + " equipped", Toast.LENGTH_SHORT).show();

                // Returns index of the weapon/armor selected
                if(i < 4)
                    returnWeapon = i;
                else
                    returnArmor = i - 4;
            }
        });

    }
}
