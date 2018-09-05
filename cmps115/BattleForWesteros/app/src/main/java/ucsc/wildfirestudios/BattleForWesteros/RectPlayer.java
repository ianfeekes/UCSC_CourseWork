package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// RectPlayer.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by: Margarita Fernandez, Thomas Zhen, Khang Tran
// Notes: 
//-------------------------------------------------------------------------------------

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;

import java.util.ArrayList;

import ucsc.wildfirestudios.joes_push.R;

import static ucsc.wildfirestudios.BattleForWesteros.InvtActivity.returnArmor;
import static ucsc.wildfirestudios.BattleForWesteros.InvtActivity.returnWeapon;

public class RectPlayer implements GameObject {
    /* DATA --------------------------------------------------------------------------- */
    private Context c;
    private Bitmap playerSprite;            // this Sprite file

    private Coord clickerCoords;            // Current clicker coordinates
    private Coord lastClickerCoords;        // Last clicker coordinates

    private Coord playerCoords;             // Current player coordinates
    private Coord tileCoords;               // Current tile coordinates
    private Coord loc;                      // Current player tile row and col
    private Tile currTile;                  // tile that player is currently on
    
    private ArrayList<Tile> adj;            // Current adjacent Tiles to this

    private int animationCounter = 0;       // This is used to give the frames for animation
    private int moveStall;
    private RectEnemy e;
    private ArrayList<RectEnemy> enemiesOnScreen;


    // game data
    public static int xp, health, damage, maxDist, level;
    public static ArrayList<Weapon> playerWeapons = new ArrayList<Weapon>();   // Inventory for weapons
    public static ArrayList<Armor> playerArmors = new ArrayList<Armor>();     // Inventory for armor
    public static Weapon currentWeapon = null;                            // No weapon equipped initially
    public static Armor currentArmor = null;                              // No armor equipped initially
    private int maxHealth;
    private ArrayList<PlayerProj> projectiles;                            // This will hold the player's projectiles
    private boolean alive;                                                // Checks if player is alive

    /* CONSTRUCTOR -------------------------------------------------------------------- */

    /* Sprite currently scaled to 200 pixels. This may be changed later*/
    public RectPlayer(Context c, Coord playerIn) {
        playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.afro);
        playerSprite = Bitmap.createScaledBitmap(playerSprite, 200,200,false);
        this.c = c;

        // Initial player coordinates
        playerCoords = new Coord(playerIn.getX(), playerIn.getY());
        clickerCoords = new Coord(0,0);
        lastClickerCoords = new Coord(0,0);
        tileCoords = new Coord(0,0);
        loc = new Coord(0,0);
        adj = new ArrayList<>();
        currTile = null;

        // Variables for player's stats
        xp = 0;
        level = 0;
        health = 100;
        damage = 20;
        maxDist = 2;
        moveStall = 0;
        alive = true;
        e = null;
        maxHealth = health;
        projectiles = new ArrayList<PlayerProj>();

        Items playerItems = new Items();            // Initializes basic weapon and armor
        playerWeapons = playerItems.getWeapons();   // Copies weapons into inventory
        playerArmors = playerItems.getArmors();     // Copies armors into inventory

        currentWeapon = playerWeapons.get(returnWeapon);    // Sets basic weapon as default weapon
        currentArmor = playerArmors.get(returnArmor);       // Sets basic armor as default armor
        equipWeapon(currentWeapon);
        equipArmor(currentArmor);
    }

    /*This is done through the game panel as the enemies may have not been properly initialized during
     *the construction of the player class, also the enemies always have immediate access to the player
     *in their constructor, which is a feature I may get rid of -Ian july 24*/
    public void setEnemies(ArrayList<RectEnemy> en)
    {
        enemiesOnScreen = en;
    }

    /* ACCESS FUNCTIONS --------------------------------------------------------------- */
    
    // main game accessors
    public int getXP() { return xp; }
    public int getHealth() { return health; }
    public int getDamage() { return damage; }
    public int getMaxDist() { return maxDist; }
    public int getLevel() { return level; }
    public boolean isAlive() { return alive; }

    // ArrayList<Tile> getAdj()
    // Returns ArrayList of legal adjacent tiles to this (so no Tiles outside the map
    // or occupied)
    public ArrayList<Tile> getAdj(ArrayList<Tile> tiles){
        ArrayList<Coord> index = new ArrayList<>();

        // ArrayList tiles data
        int size = tiles.size();                        // amount of tiles in ArrayList
        int row = tiles.get(size - 1).getRow() + 1;     // num of rows in tiles
        int col = tiles.get(size - 1).getCol() + 1;     // num of columns in tiles

        // this Tile location on map
        int r = loc.getY();
        int c = loc.getX();

        // evaluates adjacent tiles
        int adjR;
        int adjC;
        for(int i = 0; i < 8; i++){
            switch(i){
                case 0:
                    adjR = r - 1;
                    adjC = c - 1;
                    if(legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
                case 1:
                    adjR = r - 1;
                    if(legalLoc(adjR, c, row, col))
                        index.add(new Coord(c, adjR));
                    break;
                case 2:
                    adjR = r - 1;
                    adjC = c + 1;
                    if(legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
                case 3:
                    adjC = c - 1;
                    if(legalLoc(r, adjC, row, col))
                        index.add(new Coord(adjC, r));
                    break;
                case 4:
                    adjC = c + 1;
                    if(legalLoc(r, adjC, row, col))
                        index.add(new Coord(adjC, r));
                    break;
                case 5:
                    adjR = r + 1;
                    adjC = c - 1;
                    if(legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
                case 6:
                    adjR = r + 1;
                    if(legalLoc(adjR, c, row, col))
                        index.add(new Coord(c, adjR));
                    break;
                case 7:
                    adjR = r + 1;
                    adjC = c + 1;
                    if(legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
            }
        }

        // adds Tiles to ArrayList tiles corresponding to the coordinates in ArrayList index
        ArrayList<Tile> adj = processAdj(tiles, index);

        return adj;
    }

    // ArrayList<Tiles> processAdj()
    // Adds Tiles to ArrayList tiles corresponding to the coordinates in ArrayList coords
    // Called by getAdj()
    private ArrayList<Tile> processAdj(ArrayList<Tile> tiles, ArrayList<Coord> coords){
        // clears ArrayList adj, sets all previous adjacent Tiles to not selectable
        if(!adj.isEmpty()) {
            // set old adj Tiles to not selectable
            for (Tile t : adj) {
                t.setSelectable(false);
            }
        }

        ArrayList<Tile> adj = new ArrayList<>();

        // for every Tile t in the map
        for (Tile t : tiles) {
            // for every Coord c in coords
            for (Coord c: coords){
                // if row and col of tile match row and col of adj, and
                // if current Tile t is not occupied,
                if(t.getLoc().equals(c) && !t.isOccupied()){
                    t.setSelectable(true);
                    adj.add(t);
                }
            }
        }

        return adj;
    }

    // boolean legalLoc()
    // Returns true if coordinates (c, r) are inside the screen
    private boolean legalLoc(int r, int c, int rows, int cols){
        if(r < 0 || r >= rows)
            return false;
        if(c < 0 || c >= cols)
            return false;
        return true;
    }

    /* MAIN MODIFIERS ----------------------------------------------------------------- */

    // void move()
    // Moves this to corresponding new Tile location if current clicker coordinates are
    // in adjacent tiles
    public void move(ArrayList<Tile> tiles){
        // stores available move tiles into adj;
        adj = getAdj(tiles);

        // for every tile in adj
        for (Tile t : adj) {
            // if the clicked coordinates are in the current tile, move player to that tile
            if (t.inTile(clickerCoords)){
                // moves player coords and loc
                playerCoords = new Coord(clickerCoords.getX(), clickerCoords.getY());
                loc.setX(t.getCol());
                loc.setY(t.getRow());

                // updates tiles
                if(currTile != null)
                    currTile.free();
                currTile = t;
                currTile.occupy();

                // snap tileCoords to Tile t coordinates for accurate image location display
                snapToTile(t);
            }
        }
    }

    // void snapToTile()
    // snaps this.clickerCoords to tile coordinates
    private void snapToTile(Tile tile){
        tileCoords.setX(tile.getTL().getX());
        tileCoords.setY(tile.getTL().getY());
        if(moveStall !=3) moveStall = 3;
    }

    public void equipWeapon(Weapon weapon) {
        damage += weapon.getDmg();
    }

    public void equipArmor(Armor armor) { health += armor.getDef(); }

    /* GAME MODIFIERS ----------------------------------------------------------------- */

    // void update()
    // Called by GamePanel.java whenever a ticker passes
    // *Empty, for now
    @Override
    public void update(){

    }

    /* Processes this RectPlayer's movement if current coordinates != last coordinates
    clicked will only be true if the point coordinates are different than the last
    clicked coordinates. Also calls for the attack animation and movement stall to restrict
    player movement*/
    public void update(Point point, ArrayList<Tile> tiles) {
        if (alive) {
            clickerCoords = new Coord(point.x, point.y);
            if (!clickerCoords.equals(lastClickerCoords) && moveStall == 0) {
                lastClickerCoords = new Coord(clickerCoords.getX(), clickerCoords.getY());
                move(tiles);
            }
            if (e == null || e.getHealth() <= 0) computeNearestEnemy();
            /*If we have a current animation to do, animate the attack and update the tic for the length
             *of the current animation*/
            if (animationCounter > 0) {
                animateAttack();
                animationCounter--;
            } else {
                playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.afro);
            }
            playerSprite = Bitmap.createScaledBitmap(playerSprite, 200, 200, false);
            /*If we have moved recently then decrement the tick for movement restriction*/
            if (moveStall > 0) moveStall--;
            computeNearestEnemy();
            if (animationCounter == 0 && projectiles.size() < 4 /*&& enemyInRange()*/)if(enemiesOnScreen.size()>0) attack();
            for (PlayerProj f : projectiles) {
                if (collides(f) || outOfScreen(f.getLoc())) {
                    f.hide();
                    if (collides(f)) {
                        e.setHealth(this);
                        /*Mechanic to incentivize aggression and attacking enemies to slightly heal player*/
                        health+=5;
                        /*Enemy should take damage in this case*/
                    }
                }
            }

            for (int i = 0; i < projectiles.size(); i++) {
                projectiles.get(i).update(); /*THIS LINE MAY NEED TO BE REMOVED*/
                if (projectiles.get(i).isHidden()) {
                    projectiles.remove(projectiles.get(i));
                    i--;
                }
            }

        }
    /*If the player is dead*/
    else {
        currTile.free();
        for(Tile t: adj){
            t.setSelectable(false);
        }
    }


}

    public void attack()
    {
        /*With this value set to the attack counter, this means that every 3 seconds each enemy can
         *attack twice*/
        animationCounter = 15;
        computeNearestEnemy();
        Coord c = e.getLoc();
        /*Offset our target vector argument to behave as desired*/
        c.setX(c.getX()+25);
        c.setY(c.getY()+25);
        shootProjectile(c);
    }

    public void shootProjectile(Coord targetVector)
    {
        //Coord adjustedEnemyPosition = new Coord(targetVector.getX()+25, targetVector.getY()+25);
        /*These numbers for the spawning position are the initial projectile coordinates which are
         *meant to come from the enemy's fire staff*/
        Coord spawningPosition = new Coord(tileCoords.getX()+125, tileCoords.getY()+75);
        PlayerProj f = new PlayerProj(targetVector, spawningPosition,c);
        projectiles.add(f);
    }

    public boolean outOfScreen(Coord c)
    {
        if(c.getX()>Constants.SCREEN_WIDTH || c.getX()<0) return true;
        if(c.getY()>Constants.SCREEN_HEIGHT || c.getY()<0) return true;
        return false;
    }

    public boolean collides(PlayerProj currentProjectile)
    {
        int projX = currentProjectile.getLoc().getX();
        int projY = currentProjectile.getLoc().getY();
        return(Math.abs(projX-(e.getLoc().getX()+50))<35 && Math.abs(projY-(e.getLoc().getY()+10))<90);
    }

    /*Computes the nearest enemy and sets e to it so that the player can focus fire them*/
    public void computeNearestEnemy()
    {
        int currXY = 10000;
        for(int i=0; i<enemiesOnScreen.size();++i)
        {
            RectEnemy en = enemiesOnScreen.get(i);
            int maxX = max(en.getLoc().getX(), getLoc().getX());
            int maxY = max(en.getLoc().getY(), getLoc().getY());
            int minX = min(en.getLoc().getX(), getLoc().getX());
            int minY = min(en.getLoc().getY(), getLoc().getY());
            int thisXY = (int)Math.sqrt((maxX-minX)*(maxX-minX)+(maxY-minY)*(maxY-minY));
            if(thisXY<currXY)
            {
                e = en;
                currXY = thisXY;
            }
        }
    }

    public int min(int x, int y)
    {
        if(x<y)return x;
        return y;
    }

    public int max(int x, int y)
    {
        if(x>y)return x;
        return y;
    }

    public boolean enemyInRange()
    {
        /*this code is purely for debugging purposes only*/
        return(Math.abs(e.getLoc().getX()-getLoc().getX())< 400 && Math.abs(e.getLoc().getY()-getLoc().getY())< 400);
    }

    /*Determines the frame to display based on when the attack was triggered*/
    public void animateAttack(){
        if(animationCounter > 13)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an1);
        else if(animationCounter > 11)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an3);
        else if(animationCounter  >9)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an4);
        else if(animationCounter  >7)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an5);
        else if(animationCounter  >5)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an6);
        else if(animationCounter  >3)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an7);
        else if(animationCounter  >2)playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an8);
        else playerSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.an9);
    }

    /*Each frame it draws the updated version of the player sprite and health widgets*/
    @Override
    public void draw(Canvas c){
        if(alive) {
            Paint paint = new Paint();
            paint.setColor(Color.BLACK);
            c.drawBitmap(playerSprite, tileCoords.getX(), tileCoords.getY(), paint);
            for(PlayerProj p : projectiles) p.draw(c);
            drawHealth(c);
        }
    }
//
    /*Method for drawing health widget. Decided that the draw method should only have high-level code inside*/
    public void drawHealth(Canvas c) {
        if (isAlive()) {
            Paint p = new Paint();
            p.setColor(Color.GREEN);
            c.drawRect(tileCoords.getX() + 25, tileCoords.getY() - 10, tileCoords.getX() + health + 25, tileCoords.getY(), p);
        }
    }

    /* OTHER -------------------------------------------------------------------------- */

    // void printAdj
    // prints row and col of current adjacent tiles
    private void printAdj(ArrayList<Tile> adj){
        int count = 0;
        for(Tile t: adj){
            System.out.println("Adj " + count + ":\trow: " + t.getRow() + "\tcol: " + t.getCol());
            count++;
        }
    }

    /*Getter method for the player's location*/
    public Coord getLoc(){return playerCoords;}


    public void takeDamage(int damageTaken)
    {
        this.health-=damageTaken;

        // kills Player if necessary
        if(health <= 0)
            alive = false;
    }

    public void setHealth(RectBoss boss){
        this.health = this.health - boss.getDamage();
    }
}
