package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// Tile.java
// Wildfire Studios
// Created by: Margarita Fernandez
// Modified by: Ian Feekes
// Notes: 
//-------------------------------------------------------------------------------------


import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;

import java.util.ArrayList;

import ucsc.wildfirestudios.joes_push.R;

public class Tile implements GameObject {
    /* DATA --------------------------------------------------------------------------- */
    private boolean occupied;
    private boolean selectable;     // true if this can currently be selected
    private boolean attackable;     // true if there is currently an enemy on this Tile

    private boolean arrowTile;
    private final int tileLength;   // current tileLength = 200
    private int color;              // Base rectangle color
    private String tileType;        // "grass" "water" "rock" as args display different images
    private Bitmap tileImg;         // = BitmapFactory.decodeResource(getResources(), R.drawable.tester);

    // pixel coordinates
    private Coord tl;               // Top left
    private Coord tr;               // Top right
    private Coord bl;               // Bottom left
    private Coord br;               // Bottom right

    // grid location
    private Coord loc;
    private int row;                // row number in grid
    private int col;                // col number in grid

    /*This is to allow tiles to process their adjacent tiles*/
    private ArrayList<Tile> adj;

    private Context c;
    private boolean notProcessed = true;


    private boolean temp = false;

    /* CONSTRUCTOR -------------------------------------------------------------------- */

    public Tile(int tileLengthIn, Coord tlIn, int rowIn, int colIn, String tileType, Context con) {
        arrowTile = false;
        selectable = false;
        attackable = false;
        tileLength = tileLengthIn;
        row = rowIn;
        col = colIn;
        loc = new Coord(col, row);

        processCoordinates(tlIn);
        c = con;
        this.tileType = tileType;
        processTileType(tileType, c);
        tileImg = Bitmap.createScaledBitmap(tileImg, 200, 200, false);
        adj = new ArrayList<>();
    }

    // void processCoordinates()
    // calculates the pixel coordinates of each corner (tl, tr, bl, br)
    private void processCoordinates(Coord tlIn) {
        int xl = tlIn.getX();           // Leftmost x
        int xr = xl + tileLength;       // Rightmost x
        int yt = tlIn.getY();           // Top y
        int yb = yt + tileLength;       // Bottom y

        tl = new Coord(xl, yt);
        tr = new Coord(xr, yt);
        bl = new Coord(xl, yb);
        br = new Coord(xr, yb);
    }

    // void processTileType
    // Attaches to this Tile the appropriate Sprite file for drawing and occupies if needed
    private void processTileType(String tileType, Context c) {
        switch (tileType) {
            case "grass":
                occupied = false;   // grass
                int imageChoice = (int) (Math.random() * 3);
                if (imageChoice == 0)
                    tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.grass_one);
                else if (imageChoice == 1)
                    tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.grass_three);
                else
                    tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.grass_two);
                break;
            case "water":
                occupied = true;    // water
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.water_1);
                break;
            case "rock":
                occupied = true;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.rock_2);
                break;
            case "road":
                occupied = false;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.road);
                break;
            case "magma":
                occupied = true;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.magma);
                break;
            // added 5 more types of tiles, July 24th By Joe.
            case "desert":
                occupied = false;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.desert);
                break;
            case "cactus1":
                occupied = true;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.cactus_1);
                break;
            case "cactus2":
                occupied = true;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.cactus_2);
                break;
            case "tree":
                occupied = true;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.snow_tree);
                break;
            case "snow":
                occupied = false;
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.snow);
        }
    }

    // void setArrowTile
    // Sets this as an arrowTile so it is outlined green when draw. Called by mapManager
    // when populating screen tiles
    public void setArrowTile() {
        arrowTile = true;
    }


    /* ACCESS FUNCTIONS --------------------------------------------------------------- */

    public boolean isOccupied() {
        return occupied;
    }
    public boolean isSelectable() {
        return selectable;
    }
    public boolean isAttackable() {
        return attackable;
    }

    // Coord[] getPixelCoordinates
    // returns an array of size 4 containing the pixel coordinates of this tile in the
    // following order: top left, top right, bottom left, bottom right
    public Coord[] getPixelCoordinates() {
        Coord[] rtn = {tl, tr, bl, br};
        return rtn;
    }

    // Coord tl(), tr(), bl(), br()
    // returns specific coordinates
    public Coord getTL() {
        return tl;
    }

    public Coord getTR() {
        return tr;
    }

    public Coord getBL() {
        return bl;
    }

    public Coord getBR() {
        return br;
    }

    // public getTileLength()
    // returns current tile length
    public int getTileLength() {
        return tileLength;
    }

    // Coord getLoc(), getRow(), getColumn()
    // returns specific location on map
    public Coord getLoc() {
        return loc;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }


    /* COMPARISON FUNCTIONS ----------------------------------------------------------- */

    // boolean inTile
    // Checks if locIn coordinates are in this Tile
    // Returns true if locIn is in Tile
    public boolean inTile(Coord locIn) {
        int xl = tl.getX();             // Leftmost x
        int xr = br.getX();             // Rightmost x
        int yt = tl.getY();             // Top y
        int yb = br.getY();             // Bottom y

        // Checks xl <= loc.getX() <= xr)
        if (locIn.getX() < xl || locIn.getX() > xr)
            return false;

        // Checks yt <= loc.getY() <= yt
        if (locIn.getY() < yt || locIn.getY() > yb)
            return false;

        return true;
    }

    // boolean checkLoc()
    // Checks if locIn location in map is the same as this location on map
    // Returns ture if locIn = loc;
    public boolean checkLoc(Coord locIn) {
        if (locIn.equals(loc))
            return true;
        return false;
    }


    /* MAIN MODIFIERS ----------------------------------------------------------------- */

    // void occupy()/free()
    // Occupies/frees Tile by changing boolean occupied
    public void occupy() {
        occupied = true;
    }

    public void free() {
        occupied = false;
        attackable = false;
    }

    // void setAttackable()
    // Sets this Tile to attackable
    public void setAttackable() {
        attackable = true;
        occupied = true;
    }

    // void setSelectable()
    // Sets this Tile to selectable/not selectable
    public void setSelectable(boolean in) {
        selectable = in;
    }


    /* GAME MODIFIERS ----------------------------------------------------------------- */

    @Override
    public void update(){}

    // void update()
    // Called by GamePanel.java whenever a ticker passes
    // Processes any Tile changes in the map during gameplay
    // *Empty, for now
    public void update(ArrayList<Tile> tiles) {
        /*These will need to be un-commmented out*/
        if(notProcessed)
        {
            adj = getAdj(tiles);
            changeDisplay();
            notProcessed = false;
        }
    }

    public void changeDisplay()
    {
        int[][] arrangements = new int[3][3];
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
            {
                arrangements[i][j] = -1;
            }
        }
        if(tileType.equals("grass")) arrangements[1][1]=0;
        else if(tileType.equals("rock"))arrangements[1][1]=1;
        else return;

        /*Arrangements is a visualization of the adjacent tile array. If the tile is void then it will
         *be marked with a -1 */
        for(Tile t : adj)
        {
            int horzIndex = 2;
            int vertIndex=2;
            if(t.getLoc().getX()<getLoc().getX())horzIndex=0;
            else if(t.getLoc().getX()==getLoc().getX())horzIndex=1;
            if(t.getLoc().getY()>getLoc().getY())vertIndex=0;
            else if(t.getLoc().getY()==getLoc().getY()) vertIndex = 1;
            if(t.tileType.equals("water"))arrangements[horzIndex][vertIndex] = 2;
            else if(t.tileType.equals("rock"))arrangements[horzIndex][vertIndex] = 1;
            else arrangements[horzIndex][vertIndex]=0;
        }
        /*Grass case*/
        if(arrangements[1][1]==0)
        {
            if(arrangements[1][0]==2)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.b_grass_water);
            }
            else if(arrangements[1][2]==2)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.t_grass_water);
            }
        }/*Rock case*/
        else if(arrangements[1][1]==1)
        {
            if(arrangements[1][2]==0 && arrangements[0][2]==0 && arrangements[0][1]==0)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.bl_grass_rock);
            }
            else if(arrangements[1][2]==0 && arrangements[2][2]==0 && arrangements[2][1]==0)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.br_grass_rock);
            }
            else if( arrangements[1][2]==0)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.b_grass_rock);
            }
            else if(arrangements[1][0] == 0 && arrangements[0][1]==0 && arrangements[0][0]==0)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.tl_grass_rock);
            }
            else if(arrangements[1][0]==0 && arrangements[2][1]==0 && arrangements[2][0]==0)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.tr_grass_rock);
            }
            else if(arrangements[1][0]==0)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.t_grass_rock);
            }
            else if(arrangements[0][1]==2)
            {
                tileImg = BitmapFactory.decodeResource(c.getResources(), R.drawable.r_rock_water);
            }
        }
        tileImg = Bitmap.createScaledBitmap(tileImg, 200, 200, false);
    }

    /*Modified from code in the player class, but with different behavior for processing the
     *set of adjacent tiles*/
    ArrayList<Tile> getAdj(ArrayList<Tile> tiles) {
        ArrayList<Coord> index = new ArrayList<>();
        int size = tiles.size();                        // amount of tiles in ArrayList
        int row = tiles.get(size - 1).getRow() + 1;     // num of rows in tiles
        int col = tiles.get(size - 1).getCol() + 1;     // num of columns in tiles
        int r = loc.getY();
        int c = loc.getX();
        int adjR;
        int adjC;
        for(int i = 0; i < 8; i++) {
            switch (i) {
                case 0:
                    adjR = r - 1;
                    adjC = c - 1;
                    if (legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
                case 1:
                    adjR = r - 1;
                    if (legalLoc(adjR, c, row, col))
                        index.add(new Coord(c, adjR));
                    break;
                case 2:
                    adjR = r - 1;
                    adjC = c + 1;
                    if (legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
                case 3:
                    adjC = c - 1;
                    if (legalLoc(r, adjC, row, col))
                        index.add(new Coord(adjC, r));
                    break;
                case 4:
                    adjC = c + 1;
                    if (legalLoc(r, adjC, row, col))
                        index.add(new Coord(adjC, r));
                    break;
                case 5:
                    adjR = r + 1;
                    adjC = c - 1;
                    if (legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
                case 6:
                    adjR = r + 1;
                    if (legalLoc(adjR, c, row, col))
                        index.add(new Coord(c, adjR));
                    break;
                case 7:
                    adjR = r + 1;
                    adjC = c + 1;
                    if (legalLoc(adjR, adjC, row, col))
                        index.add(new Coord(adjC, adjR));
                    break;
            }
        }
        ArrayList<Tile> toReturn = adjCoordHelper(tiles, index);
        return toReturn;
    }

    private ArrayList<Tile> adjCoordHelper(ArrayList<Tile> tiles, ArrayList<Coord> coords) {
        ArrayList<Tile> adj = new ArrayList<>();
        // for every Tile t in the map
        for (Tile t : tiles) {
            // for every Coord c in coords
            for (Coord c : coords) {
                // if row and col of tile match row and col of adj, and
                // if current Tile t is not occupied,
                if (t.getLoc().equals(c)) adj.add(t);
            }
        }
        return adj;
    }

    // Draws this Tile on canvas
    // *Added functions needed to allow it to implement the GameObject interface and to be
    // *displayed on the canvas and updated
    @Override
    public void draw(Canvas c) {
        Paint paint = new Paint();
        paint.setColor(Color.BLUE);

        //adj = getAdj(tiles);


        // draws 8bit image of the tile on canvas
        c.drawBitmap(tileImg, tl.getX(), tl.getY(), paint);

        // if this needs to be outlined: is an arrow tile, selectable or attackable (TBI)
        if (selectable || arrowTile || occupied || attackable) {
            int xl = tl.getX();
            int xr = br.getX();
            int yt = tl.getY();
            int yb = br.getY();

            // if this is an arrow tile, sets outline color to green,
            // else stays blue
            if (arrowTile) {
                paint.setColor(Color.GREEN);
            }

            if (occupied) {
                paint.setColor(Color.RED);
            }

            if (attackable) {
                paint.setColor(Color.YELLOW);
            }

            /*DELETE THIS LATER*/
            if(temp)
            {
                paint.setColor(Color.BLACK);
            }

            // initializes rectangles to make up outline
            Rect left = new Rect(xl, yt, xr - 190, yb);
            Rect top = new Rect(xl, yt, xr, yb - 190);
            Rect right = new Rect(xl + 190, yt, xr, yb);
            Rect bottom = new Rect(xl, yt + 190, xr, yb);

            // draws rectangles
            c.drawRect(left, paint);
            c.drawRect(top, paint);
            c.drawRect(right, paint);
            c.drawRect(bottom, paint);
        }
    }

    /* OTHER -------------------------------------------------------------------------- */

    // String toString()
    // Prints this Tile's current data
    public String toString() {
        String rtn = "";

        // state
        rtn += "Occupied?\t " + ((occupied) ? "yes\n" : "no\n");
        rtn += "Selectable?\t " + ((selectable) ? "yes\n" : "no\n");
        rtn += "Attackable?\t " + ((attackable) ? "yes\n" : "no\n");

        // location
        rtn += "\nLocation on map:";
        rtn += "\nrow = " + row;
        rtn += "\ncol = " + col;

        // coordinates
        rtn += "\n\n\nCoordinates:";
        rtn += "\ntileLength = " + tileLength;
        rtn += "\ntop left = " + tl.toString();
        rtn += "\ntop right = " + tr.toString();
        rtn += "\nbottom left = " + bl.toString();
        rtn += "\nbottom right = " + br.toString();
        rtn += "\n";

        return rtn;
    }

    private void setTr(boolean toSet)
    {
        temp = toSet;
    }

    private boolean legalLoc(int r, int c, int rows, int cols) {
        if (r < 0 || r >= rows)
            return false;
        if (c < 0 || c >= cols)
            return false;
        return true;
    }

}