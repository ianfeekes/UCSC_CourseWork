package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// GameObject.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by:
// Notes: Any class that implements this interface must contain all methods declared
// in this
//-------------------------------------------------------------------------------------

import android.graphics.Canvas;

public interface GameObject {
    
    // void update()
    // updates entity as needed during gameplay
    public void update();

    // void draw()
    // draws entity on canvas
    public void draw(Canvas canvas);
}
