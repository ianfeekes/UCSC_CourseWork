package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// MapManager.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by: Margarita Fernandez, Joe Jiang
// Notes: 
//-------------------------------------------------------------------------------------


import android.content.Context;
import android.graphics.Canvas;

import java.util.ArrayList;

import static ucsc.wildfirestudios.BattleForWesteros.Constants.SCREEN_HEIGHT;
import static ucsc.wildfirestudios.BattleForWesteros.Constants.SCREEN_WIDTH;
/*The mapManager class is currently brainless. It holds an arrayList called tiles which contains enough
 *tiles of whatever size we want to fill in the entire screen. It's draw method parses through the array
 *list calling the draw() method of each individual tile. */

/*
 * IDEAS:
 * MapManager can be the class that is used for procedural generation logic. It can potentially create the
 * tiles with different image arguments which can be used to make the game randomly generate maps that look
 * aethetic. An example of this would be to make the arraylist two dimensional where it has a method to return
 * an arrayList of all adjacent tiles for each tile, and it will create a special image  eg. it sees a water
 * tile next to a grass tile and it creates a transition of coastline between the two, which would solely
 * serve aesthetic purposes but would still be very interesting.
 *
 * the tile arraylist should eventually be made to function two demensionally because this wouldn't add
 * too much run-time, but it would allow for the easy log(n) implementation of findAdjacentTiles. I may work
 * on this if I have nothing to do.
 *
 * The constructor should have an int "squareSize" passed into it so that tiles of any given size can be
 * constructed for purposes of testing how many tiles we like to have displayed on a screen at once
 * -Ian July 11th*/

public class MapManager {
    /* DATA --------------------------------------------------------------------------- */
    private ArrayList<ArrayList<Tile>> tiles_holder;
    private ArrayList<RectEnemy> enemies;
    private Context con;
    int page;
    boolean enemiesInitialized;

    /* CONSTRUCTOR -------------------------------------------------------------------- */
    
    public MapManager(Context c, int x, ArrayList<RectEnemy> enemiesIn) {
        page = x;
        tiles_holder = new ArrayList<ArrayList<Tile>>();
        enemies = enemiesIn;
        con = c;
        enemiesInitialized = false;

        populateMap();
    }

    // void populateMap()
    // Generates tiles based on screen height and width. Once levels are implemented,
    // this method should take the level as a parameter and process the tiles based on
    // that specific data
    private void populateMap(){
        /*Edit by Joe  Design the Dungeon, July,24th*/

        // page 0
        ArrayList<Tile> tiles = new ArrayList<>();

        for(int y = 0; y< SCREEN_HEIGHT; y+=200) {
            for (int x = 0; x < SCREEN_WIDTH; x += 200) {
                Coord c = new Coord(x,y);       // Tile coordinates
                String tileType = "grass";

                if(x == 400 && (y>=0 && y <= 200)) tileType = "rock";

                if (x == 400 && y ==600) tileType= "rock";

                if(x == 200 && (y == 800 || y == 1200)) tileType = "rock";

                if((x == 0 || x == 400)&& y == 1200) tileType = "rock";

                if(x == 800 && (y == 1000)) tileType = "rock";


                Tile t = new Tile(200,c,(int)(y/200),(int)(x/200),tileType, con);

                // sets arrowTiles
                int midX = SCREEN_WIDTH / 2;
                int midY = SCREEN_HEIGHT / 2;

                // left arrow
                if(t.inTile(new Coord(500, 1700)))
                    t.setArrowTile();

                tiles.add(t);
            }
        }
        tiles_holder.add(tiles);

        // page 1
        tiles = new ArrayList<Tile>();
        for(int y = 0; y< SCREEN_HEIGHT; y+=200){
            for(int x = 0; x< SCREEN_WIDTH; x+=200)
            {
                Coord c = new Coord(x,y);       // Tile coordinates
                String tileType = "grass";

                /*This line is added just to pick some specific tiles in the middle of the initial
                 *layout and set them to water and rocks rather than grass for testing purposes*/
                if((x>=0 && x<=1200)  && y==1000) tileType = "water"; // place water

                /*
                 * place more water
                 * mod by joe
                 */
                if(x == 400 && y <= 1000) tileType = "water";
                /*
                 * put rock road
                 * mod by joe
                 */;
                if(x == 0 && y == 1000) tileType = "road";

                if(x == 600 && (y<=1000 && y >= 600)) tileType = "road";

                if(y == 600 && (x == 600 || x == 800)) tileType = "road";

                if(x == 1200 && (y >= 400 && y <= 800)) tileType = "road";

                if((y == 400 || y == 200)&& x == 800) tileType = "road";


                // initializes current Tile with data obtained above
                Tile t = new Tile(200,c,(int)(y/200),(int)(x/200),tileType, con);


                // sets arrowTiles
                int midX = SCREEN_WIDTH / 2;
                int midY = SCREEN_HEIGHT / 2;

                // left arrow
                if(t.inTile(new Coord(1100, 700)))
                    t.setArrowTile();

                // Appends current Tile to ArrayList tiles
                tiles.add(t);
            }
        }
        tiles_holder.add(tiles);

        // page 2
        tiles = new ArrayList<Tile>();
        for(int y = 0; y< SCREEN_HEIGHT; y+=200){
            for(int x = 0; x< SCREEN_WIDTH; x+=200)
            {
                Coord c = new Coord(x,y);       // Tile coordinates
                String tileType = "desert";

                /*This line is added just to pick some specific tiles in the middle of the initial
                 *layout and set them to water and rocks rather than grass for testing purposes*/

                /*
                 * place more water
                 * mod by joe
                 */
                if (y == 600 && (x == 400 || x == 600)) tileType = "water";
                if (y == 800 && (x >= 200 && x <= 600)) tileType = "water";
                if (y == 1000 &&(x == 400 || x == 600)) tileType = "water";
                /*
                 * put grass
                 * mod by joe
                 */;
                if (y == 400 && (x >= 200 && x <= 600)) tileType = "grass";
                if ((y == 600 && (x == 200 || x == 800))
                        || (y == 800 && x == 800)) tileType = "grass";
                if (y == 1000 && (x == 200 || x == 800)) tileType = "grass";
                if (y == 1200 && (x >= 200 && x <= 800)) tileType = "grass";

                /*
                 * put cactus
                 * mod by joe
                 */;
                if (y == 0 && x == 400) tileType = "cactus2" ;
                if (y == 0 && x == 1000) tileType = "cactus1";
                if (y == 400 && (x == 800 || x == 0)) tileType = "cactus1" ;
                if (y == 1200 && x == 0) tileType = "cactus2" ;
                if (y == 1200 && x == 800) tileType = "cactus2" ;
                if (y == 1400 && x == 400) tileType = "cactus1" ;

                // initializes current Tile with data obtained above
                Tile t = new Tile(200,c,(int)(y/200),(int)(x/200),tileType, con);


                if(t.inTile(new Coord(700, 1700)))
                    t.setArrowTile();

                // Appends current Tile to ArrayList tiles
                tiles.add(t);
            }
        }
        tiles_holder.add(tiles);

        /* Dungeon 2*/
        // page 3
        tiles = new ArrayList<Tile>();
        for(int y = 0; y< SCREEN_HEIGHT; y+=200){
            for(int x = 0; x< SCREEN_WIDTH; x+=200)
            {
                Coord c = new Coord(x,y);       // Tile coordinates

                String tileType = "snow";

                if (y == 0 && (x >= 400 && x <= 1000)) tileType = "tree";
                if ((y == 200 || y == 400) && (x >= 600 && x <= 1000)) tileType = "tree";
                if ((y == 400 || y == 600)&& x== 0) tileType = "tree";
                if (y == 600 && x == 600)  tileType = "tree";
                if (y == 800 && x == 400) tileType = "tree";
                if (y == 1000 && (x >=400 && x <=600)) tileType = "tree";
                if ((y == 1200 || y == 1400) && x == 1000) tileType = "tree";
                if (y == 1600 &&(x == 0 || x == 800 || x == 1000)) tileType = "tree";

                Tile t  = new Tile(200,c,(int)(y/200),(int)(x/200),tileType, con);

                if(t.inTile(new Coord(1100, 1100)))
                    t.setArrowTile();

                tiles.add(t);
            }
        }
        tiles_holder.add(tiles);

        // page 4
        tiles = new ArrayList<Tile>();
        for(int y = 0; y< SCREEN_HEIGHT; y+=200){
            for(int x = 0; x< SCREEN_WIDTH; x+=200)
            {
                Coord c = new Coord(x,y);       // Tile coordinates

                String tileType = "snow";
                /* put tree */
                if (y == 0 && (x >= 200 && x <= 1000)) tileType = "tree";
                if (y == 200 && (x >= 200 && x <= 400 )) tileType = "tree";
                if ((x == 600 || x == 400) && (y >= 400 && y <=1000)) tileType = "tree";
                if (y == 1600 && (x >= 0 && x <= 1000)) tileType = "tree";
                if ((y == 1200 || y == 1400) && x == 0) tileType = "tree";

                /* put road */
                if (y == 600 && (x == 0 || x == 200)) tileType = "road";
                if (x == 200 && (y >= 600 && y <= 1000)) tileType = "road";
                if (y == 1200 && (x >= 200 && x <= 800)) tileType = "road";
                if (x == 800 && (y >= 400 && y <= 1000)) tileType = "road";

                Tile t  = new Tile(200,c,(int)(y/200),(int)(x/200),tileType, con);

                if(t.inTile(new Coord(900, 300)))
                    t.setArrowTile();

                tiles.add(t);
            }
        }
        tiles_holder.add(tiles);
        // page 5
        tiles = new ArrayList<Tile>();
        for(int y = 0; y< SCREEN_HEIGHT; y+=200){
            for(int x = 0; x< SCREEN_WIDTH; x+=200)
            {
                Coord c = new Coord(x,y);       // Tile coordinates
                String tileType = "magma";

                /*This line is added just to pick some specific tiles in the middle of the initial
                 *layout and set them to water and rocks rather than grass for testing purposes*/
                if((x>=0 && x<=1200)  && y==1000) tileType = "road"; // place water

                /*
                 * place more water
                 * mod by joe
                 */
                if(x == 400 && y <= 1000 && y != 400 && y != 600) tileType = "road";
                /*
                 * put rock road
                 * mod by joe
                 */;
                if((x == 0 && y <= 1400) ||(y == 1400 && x <= 1000)) tileType = "road";
                if(x == 1000 && (y >= 800 && y <= 1200)) tileType = "road";
                if((x == 200 && y == 600) || (x == 400 && y == 800) || ((x == 600 || x == 800) && y == 1000)) tileType = "road";
                if((x == 800 && y == 600) || (x == 600 && y == 400)) tileType = "road";
                if((x >= 400 && x <= 800)&&y <= 200) tileType = "road";


                // initializes current Tile with data obtained above
                Tile t = new Tile(200,c,(int)(y/200),(int)(x/200),tileType, con);

                // Appends current Tile to ArrayList tiles
                tiles.add(t);
            }
        }
        tiles_holder.add(tiles);
    }


    /* ACCESS FUNCTIONS --------------------------------------------------------------- */

    // int getPage()
    public int getPage(){ return page; }

    // ArrayList<Tile> getTiles()
    // Returns array of Tiles contained in this map
    public ArrayList<Tile> getTiles(){ return tiles_holder.get(page); }

    // boolean enemiesInitialized
    // returns false if enemies have not been given locations
    public boolean enemiesInitialized() { return enemiesInitialized; }

    // Tile findTile()
    // Returns Tile containing input coordinates. If no such Tile exists, returns null
    public Tile findTile(Coord in){
        for(Tile t: tiles_holder.get(page)){
            if(t.inTile(in))
                return t;
        }
        return null;
    }


    /* MODIFIERS ---------------------------------------------------------------------- */
    
    public void setEnemiesInitialized(boolean in){ enemiesInitialized = in; }

    // RectEnemy[] updateEnemies()
    // Updates Enemy locations only if called by client class
    public ArrayList<RectEnemy> updateEnemies(int x){
        page = x;

        // updates enemies
        // NOTE - For now, it places all enemies on the same tiles in both pages. When we
        //        decide to change their positions, we will have to create a switch
        //        statement (or helped method) to process the appropriate coordinates
        for(Tile t: tiles_holder.get(page)){
            Coord c;

            // enemies[0]
            c = new Coord(0, 800);
            //System.out.println("Tile coords: " + t.getTL());
            if(t.getTL().equals(c)){
                t.setAttackable();
                enemies.get(0).setTile(t);
                enemies.get(0).setLoc(c);
            }

            // enemies[1]
            c = new Coord(200, 1400); // left, right, down(many)
            if(t.getTL().equals(c)){
                t.setAttackable();
                enemies.get(1).setTile(t);
                enemies.get(1).setLoc(c);
            }

            // enemies[2]
            c = new Coord(600, 1400); // up, down, left, right
            if(t.getTL().equals(c)){
                t.setAttackable();
                enemies.get(2).setTile(t);
                enemies.get(2).setLoc(c);
            }

            // enemies[3]
            c = new Coord(1000, 800);  // up, left, right
            if(t.getTL().equals(c)){
                t.setAttackable();
                enemies.get(3).setTile(t);
                enemies.get(3).setLoc(c);
            }

            // enemies[4]
            c = new Coord(800, 600); // up, left, down, right
            if(t.getTL().equals(c)){
                t.setAttackable();
                enemies.get(4).setTile(t);
                enemies.get(4).setLoc(c);
            }

        }

        enemiesInitialized = true;

        return enemies;
    }

    // void update
    // Updates page number
    public void update(int x) {
        page = x;
    }

    // void draw()
    // Draws all Tiles contained in ArrayList tiles to canvas
    public void draw(Canvas c)
    {
        for(Tile t : tiles_holder.get(page))
        {
            t.draw(c);
        }
    }
}
