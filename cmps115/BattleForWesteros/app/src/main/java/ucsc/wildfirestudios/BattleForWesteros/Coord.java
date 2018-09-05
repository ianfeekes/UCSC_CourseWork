package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// Coord.java
// Wildfire Studios
// Created by: Margarita Fernandez
// Modified by:
// Notes: Created to hold basic (x, y) coordinates
//-------------------------------------------------------------------------------------

public class Coord {
    /* DATA --------------------------------------------------------------------------- */
    private int x;
    private int y;


    /* CONSTRUCTOR -------------------------------------------------------------------- */
    public Coord(int xIn, int yIn){
        x = xIn;
        y = yIn;
    }


    /* ACCESS FUNCTIONS --------------------------------------------------------------- */
    public int getX(){ return x; }
    public int getY(){ return y; }


    /* MODIFIERS ---------------------------------------------------------------------- */
    public void setX(int xIn){ x = xIn; }
    public void setY(int yIn){ y = yIn; }


    /* OTHER -------------------------------------------------------------------------- */
    public String toString(){ return ("(" + x + ", " + y + ")"); }
    public boolean equals(Coord loc){
        if(loc.getX() == x && loc.getY() == y)
            return true;
        return false;
    }
}