package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// PlayerProj.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by:
// Notes: Fire projectile fired by the player at whichever enemy is closest and within
//        range.
//-------------------------------------------------------------------------------------

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

import ucsc.wildfirestudios.joes_push.R;

/*The player projectile is fired by the player at whichever enemy is closest and within range. The player
 *controls its behavior, similarly to the fire projectile. The player projectile contains methods to
 *modify its movement and target vector*/
public class PlayerProj implements GameObject
{
    /*Data Fields*/
    public Coord loc;           /*Current location of the flameProjectile in coordinate form*/
    private Coord targetVector; /*Determines towards what the projectile will be propelled, usually player coords*/
    private Bitmap flashSprite; /*Shuriken image of the projectile. May be animated later if I have time*/
    private int incrX, incrY;   /*This is the projectile's movement as it travels*/
    private Context c;          /*Context of the game, allows detailled imaging and animation*/
    private boolean isHiding;   /*Determines if we should do anything with the projectile or if it should
                                 *behave as a ghost object*/
    private int an1;

    /*target coordinates and spawn coordinates, along with a context for bitmap imaging. Sets all the
     *appropriate data fields of the class as necessary. Computes target vector for movement. Creates the
     *flash bitmap image and resizes it. Sets up default animation stall integers*/
    public PlayerProj(Coord target, Coord spawn, Context c){
        loc = spawn;
        /*Whenever we create a new projectile (which will happen a constant number of times for each
         *enemy to avoid sucking up too much processing power) we want it to initially display and update,
         *however this may change based on if it moves outside the walls or collides with the player etc.*/
        isHiding = false;
        /*Finds the vector to be used to increment the projectile coordinates during the update method*/
        resetVector(target);
        flashSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.flash1);
        flashSprite = Bitmap.createScaledBitmap(flashSprite, 30,30,false);
        /*Initialize the default integers for handling the basic animation of the object*/
        an1  = 6;
    }

    /*Computes the vector in terms of a tuple by calling the getVector method and storing it into a
     *array*/
    public void resetVector(Coord target)
    {
        targetVector = target;
        int[] vectorComputed = getVector();
        incrX = vectorComputed[0];
        incrY = vectorComputed[1];
    }

    /*Computes the movement vector based on target location and returns an integer array in the form of a tuple*/
    public int[] getVector()
    {
        /*first index will be used for incrX, and the second index will be used for incrY*/
        int[]toReturn = new int[2];
        /*diffX and diffY are the differences in pixels between their spawn and their target destination*/
        int diffX = targetVector.getX()-loc.getX();
        int diffY = targetVector.getY()-loc.getY();
        /*Scaling for the projectiles based on the target's coordinate so that they aren't rediculously
         *fast or slow in close and long range situations. This is different from the flame projectiles
         *scaling as we want the player's attacks to be faster*/
        if(Math.abs(diffX) > 400) diffX/=35;
        else if(Math.abs(diffX) >300) diffX/=25;
        else if(Math.abs(diffX) >200) diffX/=15;
        else diffX/=5;
        /*Same scaling applies to both axes*/
        if(Math.abs(diffY) > 400) diffY/=35;
        else if(Math.abs(diffY) >300) diffY/=25;
        else if(Math.abs(diffY) >200) diffY/=15;
        else diffY/=5;
        if(Math.abs(loc.getX()-targetVector.getX())<20)diffX=0;
        if(Math.abs(loc.getY()-targetVector.getY())<20)diffY=0;
        toReturn[0]=diffX;
        toReturn[1]=diffY;
        return toReturn;
    }

    /*This method simply moves the projectile. It is used to handle collisions eg. hitting the player,
     *reaching the end of the screen etc. because originally the code removed the projectile from the
     *enemy's arrayList and destroyed it, which caused the game to lag horribly because of the deallocation
     *of so much stack data. Now the projectiles handle collisions by moving back to the enemy's coordinate
     *and hiding themselves until it's time to have the launch rate*/
    public void setLoc(Coord c)
    {
        this.loc = c;
    }

    /*Access methods*/
    public Coord getLoc(){return loc;}

    /*Simply draws the bitmap image into the canvas*/
    @Override
    public void draw(Canvas c)
    {
        /*Only should be displayed if it's not hiding*/
        if(!isHiding)
        {
            Paint paint = new Paint();
            paint.setColor(Color.BLACK);
            c.drawBitmap(flashSprite, loc.getX(), loc.getY(), paint);
        }
    }

    /*Updates location*/
    @Override
    public void update()
    {
        /*Only updates if the projectile should be in commission.*/
        if(!isHiding) {
            /*Updates its location with the speed of its distance vector*/
            /*Note that collisions with the player object are not handled by each individual projectile
             *but rather by the enemy through their own arraylist of projectiles. The projectile has its
             *behavior modified by the enemy class, and the enemy handles collisions itself*/
            loc.setX(loc.getX() + incrX);
            loc.setY(loc.getY() + incrY);
        }
    }

    public void hide()
    {
        isHiding = true;
    }

    public void appear()
    {
        isHiding = false;
    }

    /*Used to determine if there is a need to start redesplaying the projectile*/
    public boolean isHidden()
    {
        return isHiding;
    }

}

