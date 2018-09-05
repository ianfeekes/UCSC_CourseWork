package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// ImgCastle.java
// Wildfire Studios
// Created by: Joe Jiang
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

public class ImgCastle implements GameObject {
    private int xcoord = 0;
    private int ycoord = 0;
    private Bitmap castleSprite;

    public ImgCastle(Context c) {
        castleSprite = BitmapFactory.decodeResource(c.getResources(), R.drawable.castle);
        castleSprite = Bitmap.createScaledBitmap(castleSprite, 420,350, false);
    }

    @Override
    public void draw(Canvas c) {
        Paint paint = new Paint();
        paint.setColor(Color.BLACK);
        c.drawBitmap(castleSprite, xcoord, ycoord, paint);
    }
    @Override
    public void update() {

    }

    public void update(Point point) {
        xcoord = point.x;
        ycoord = point.y;
    }
}

