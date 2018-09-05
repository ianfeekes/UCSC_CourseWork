package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// RectEnemy.java
// Wildfire Studios
// Created by: Thomas Zhen
// Modified by: Ian Feekes
// Notes: 
//-------------------------------------------------------------------------------------

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import java.util.ArrayList;
import ucsc.wildfirestudios.joes_push.R;

/*This is currently the main enemy class. It takes in the user input of x and y coordinates being
 *touched and it updates its own coordinates so that it behaves by essentially just following the
 *player around the screen. This will obviously need to be changed when the snapTo method is implemented
 *to give it more of a turn-based behavior
 */

/*The enemy takes in the coordinate of the player and fire projectile at the player*/
public class RectEnemy implements GameObject {
    /* DATA --------------------------------------------------------------------------- */
    private Bitmap enemySprite;
    private int topX = 0;
    private int topY = 0;
    private RectPlayer p;
    private int attackCounter = 0;
    private Context c;

    // Moved from enemy class
    private int health, damage, level ;
    private boolean isAlive, isEmpty;

    private Coord tileCoords;        // tile coordinates
    private Coord loc;               // tile row and col
    private Tile tile;               // tile that enemy is on

    /*This contains all projectiles that this enemy has fired*/
    private ArrayList<FlameProj> projectiles;

    /* CONSTRUCTOR -------------------------------------------------------------------- */
    
    /* Sprite currently scaled to 200 pixels. This may be changed later*/
    public RectEnemy(Context c, RectPlayer player) {
        enemySprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.enemybone);
        enemySprite = Bitmap.createScaledBitmap(enemySprite, 200,200,false);
        this.c=c;
        this.p=player;
        tileCoords = new Coord(0,0);
        loc = new Coord(0,0);
        tile = null;

        projectiles = new ArrayList<FlameProj>();
        // game data
        isAlive = true;
        isEmpty = false;
        health = 100;
        damage = 5;
    }


    /* ACCESS FUNCTIONS --------------------------------------------------------------- */
    public int getHealth() { return health; }
    public int getDamage() { return damage; }
    public boolean isAlive(){ return isAlive; }
    public boolean isEmpty(){ return this.isEmpty; }
    public Coord getMapLoc(){ return loc; }
    public Tile getTile() { return tile; }


    /* MAIN MODIFIERS ----------------------------------------------------------------- */

    // moves enemy to set Tile t
    public void setTile(Tile t){
        tile = t;
        tileCoords = tile.getTL();
        loc = tile.getLoc();
    }

    // Moved from enemy class
    public void setHealth(RectPlayer player) {
        if (isAlive) {
            if (health - player.getDamage() <= 0) {
                this.health = 0;
                this.isAlive = false;
                this.isEmpty = true;
                tile.free();
            } else {
                this.health = this.health - player.getDamage();
            }
        }
    }

    /* GAME MODIFIERS ----------------------------------------------------------------- */

    /*Determines projectile firing*/
    /*update the player's coordinate, Compute players coordinate*/
    @Override
    public void update()
    {
        if(health<=0) isAlive=false;

        if(!isAlive)
        {
            //projectiles = null;
        }
        // If the enemy is alive and the player is alive
        if(p.isAlive() && isAlive)
        /*There is a stall for firing rate. For now we set the constraint that each enemy gets 5 projectiles*/
        if(attackCounter ==0 && projectiles.size()<7 && inRange()) attack();
        else if(attackCounter>0)attackCounter --;
        for(FlameProj f : projectiles)
        {
            /*This line tests to see if we need to reinstate a hidden projectile, hiding the projectile
            * on the enemy, so that it won't waste too much memory and cause the game to lag*/
            if(f.isHidden() && inRange() && attackCounter==0)
            {
                /*Reinstating hidden projectiles needs to account for attack lag else the enemys will
                 *have double the fire rate*/
                attackCounter = 20;
                f.appear();
                f.resetVector(new Coord(p.getLoc().getX(), p.getLoc().getY()));
            }
            f.update();
            /*If the projectile is out of the screen we want it to be reset to attack the character,
             *and check to see if the character is in range, else hide the projectile and avoid any
             *intensive computation*/
            if(outOfScreen(f.getLoc()) || collides(f)) {
                /*I may change the player's setHealth method to this takeDamage method that I am writing
                 *as taking in an enemy class with a static damage variable is not flexible to the leveling
                 *mechanic that we want to put into the game*/
                if (collides(f) && isAlive) p.takeDamage(10);
                Coord temp = new Coord(tileCoords.getX(), tileCoords.getY());
                f.setLoc(temp);
                //f.resetVector(new Coord(p.getLoc().getX()+50, p.getLoc().getY()+50));
                /*You only want the projectile to continue moving in a path towards the character if
                 *the player is still in range of the enemy*/
                /*Hiding the projectile stops it from being updated or drawn. It essentially a ghost
                 *object that is still reachable to save on having to deallocate and reallocate a large
                 *amount of heap memory*/
                if(inRange() && attackCounter ==0)
                {
                    attackCounter = 20;
                }
                else f.hide();
                f.resetVector(new Coord(p.getLoc().getX()+50, p.getLoc().getY()+50));

            }
        }
    }

    /*Used so that the player can find the location of the enemy to fire projectiles at them*/
    public Coord getLoc(){return loc;}

    public boolean inRange()
    {
           Coord temp = p.getLoc();
            return (Math.abs(temp.getX() - tileCoords.getX()) <= 500 && Math.abs(temp.getY() - tileCoords.getY()) <= 500);
    }

    /*Determines whether the projectile has collided with the private player the enemy class has  a
     *reference to*/
    public boolean collides(FlameProj currentProjectile)
    {
        /*projX and projY are simply to make the code clean and avoid a rediculously long line of code*/ 
        int projX = currentProjectile.getLoc().getX();
        int projY = currentProjectile.getLoc().getY();
        return(Math.abs(projX-(p.getLoc().getX()))<35 && Math.abs(projY-(p.getLoc().getY()))<90);
    }

    /*Determine wheter the projectile is out of screen*/
    public boolean outOfScreen(Coord c)
    {
        if(c.getX()>Constants.SCREEN_WIDTH || c.getX()<0) return true;
        if(c.getY()>Constants.SCREEN_HEIGHT || c.getY()<0) return true;
        return false;
    }

    /*Call the fireProjectile function and sent the attackCounter so that the enemy can fire every 3 seconds*/
    public void attack()
    {
        /*With this value set to the attack counter, this means that every 3 seconds each enemy can
         *attack twice*/
        attackCounter = 20;
        fireProjectile(p.getLoc());
    }

    /*Create FlameProj and add it to the projectiles arraylist*/
    public void fireProjectile(Coord targetVector)
    {
        Coord adjustedPlayerPosition = new Coord(targetVector.getX()+25, targetVector.getY()+25);
        /*These numbers for the spawning position are the initial projectile coordinates which are
         *meant to come from the enemy's fire staff*/
        Coord spawningPosition = new Coord(tileCoords.getX()+125, tileCoords.getY()+75);
        FlameProj f = new FlameProj(adjustedPlayerPosition, spawningPosition,c);
        projectiles.add(f);
    }

    /*Displays enemy's sprite, health widget, and projectiles*/
    @Override
    public void draw(Canvas c)
    {
        if(isAlive) {
            Paint paint = new Paint();
            paint.setColor(Color.BLACK);
            c.drawBitmap(enemySprite, tileCoords.getX(), tileCoords.getY(), paint);
            for (FlameProj f : projectiles) f.draw(c);
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

    /*Re-set the location of the loc variable*/
    public void setLoc(Coord c)
    {
        loc = c;
    }

}