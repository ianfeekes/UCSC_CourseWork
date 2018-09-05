package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// Potion.java
// Wildfire Studios
// Created by: Khang Tran
// Modified by:
// Notes:
//-------------------------------------------------------------------------------------

public class Potion {
    /* DATA --------------------------------------------------------------------------- */
    public String type, name;
    public int hpRestore;

    /* CONSTRUCTOR -------------------------------------------------------------------- */
    public Potion(String inputType, String inputName, int inputHP) {
        type = inputType;
        name = inputName;
        hpRestore = inputHP;
    }

    /* ACCESS FUNCTIONS --------------------------------------------------------------- */
    public String getType() { return type; }
    public String getName() { return name; }
    public int getHpRestore() { return hpRestore; }
}
