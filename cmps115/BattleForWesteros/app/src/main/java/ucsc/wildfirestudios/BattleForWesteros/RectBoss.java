package ucsc.wildfirestudios.BattleForWesteros;

///-------------------------------------------------------------------------------------
// RectBoss.java
// Wildfire Studios
// Created by: Thomas Zhen
// Modified by:
// Notes:
//-------------------------------------------------------------------------------------

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;

import ucsc.wildfirestudios.joes_push.R;

/*This is currently the boss class. It takes in the user input of x and y coordinates being
 *touched and it updates its own coordinates so that it behaves by essentially just following the
 *player around the screen. This will obviously need to be changed when the snapTo method is implemented
 *to give it more of a turn-based behavior
 */

public class RectBoss implements GameObject {
    /* DATA --------------------------------------------------------------------------- */
    private Bitmap enemySprite;

    // Moved from enemy class
    private int health, damage;
    private boolean isAlive;

    private Coord tileCoords;           // tile coordinates for Boss
    private Tile tile;                  // tile that enemy is on

    /*This contains all projectiles that this enemy has fired*/
    /* CONSTRUCTOR -------------------------------------------------------------------- */

    /* Sprite currently scaled to 200 pixels. This may be changed later*/
    public RectBoss(Context c) {
        enemySprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.enemyboss);
        enemySprite = Bitmap.createScaledBitmap(enemySprite, 400,400,false);
        tileCoords = new Coord(400,1800); // Boss location
        tile = null;

        // game data
        isAlive = true;
        health = 100;
        damage = 20;
    }


    /* ACCESS FUNCTIONS --------------------------------------------------------------- */
    public int getHealth() { return health; }
    public int getDamage() { return damage; }
    public boolean isAlive(){ return isAlive; }
    public Tile getTile() { return tile; }

    /* MAIN MODIFIERS ----------------------------------------------------------------- */

    /*Set the health of the boss*/
    public void setHealth(RectPlayer player) {
        if (isAlive) {
            if (health == 0) {
                this.health = 0;
                this.isAlive = false;
            } else {
                this.health = this.health - player.getDamage();
            }
        }
    }

    /* GAME MODIFIERS ----------------------------------------------------------------- */
    @Override
    /*Inherited but not used*/
    public void update(){
        // Empty
    }

    /*Update the location of the boss*/
    public void update(Point point){
        Coord newPoint = new Coord(point.x,point.y);

        this.tileCoords = newPoint;
    }

    /*Displays boss's sprite, health widget, and projectiles*/
    @Override
    public void draw(Canvas c)
    {
        if(isAlive) {
            Paint paint = new Paint();
            paint.setColor(Color.BLACK);
            c.drawBitmap(enemySprite, tileCoords.getX(), tileCoords.getY(), paint);
            drawHealth(c);
        }
    }

    /*Method for drawing health widget*/
    public void drawHealth(Canvas c){
        if(isAlive) {
            Paint p = new Paint();
            p.setColor(Color.RED);
            c.drawRect(tileCoords.getX() + 25, tileCoords.getY() - 10, tileCoords.getX() + health + 25, tileCoords.getY(), p);
        }
    }
}