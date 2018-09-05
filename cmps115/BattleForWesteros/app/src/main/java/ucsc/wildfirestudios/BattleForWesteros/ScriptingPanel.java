package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// ScriptingPanel.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by:
// Notes:
//-------------------------------------------------------------------------------------

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class ScriptingPanel extends SurfaceView implements SurfaceHolder.Callback{

    /*---------------------Data-----------------------*/
    private Point clickerPoint;
    private MainThread thread;


    public ScriptingPanel(Context c)
    {
        super(c);
        getHolder().addCallback(this);
        setFocusable(true);
    }

    public void update()
    {

    }

    /*Draws whatever we want to be scriped onto the canvas*/
    @Override
    public void draw(Canvas c)
    {
        /*This line is necessary*/
        super.draw(c);
        /*This method is filled with bogus for testing purposes*/
        Paint p = new Paint();
        p.setColor(Color.GREEN);
        c.drawRect(25, 25, 300, 600, p);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        thread.setRunning(true);
        thread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        boolean retry = true;
        while (true) {
            try {
                thread.setRunning(false);
                thread.join();
            } catch (Exception e) {
                e.printStackTrace();
            }
            retry = false;
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:

                int x = (int) event.getX();
                int y = (int) event.getY();

                clickerPoint.set((int) event.getX(), (int) event.getY());
        }

        //  }
        /*Returning false will give the app reasons not to detect the touch in the future, but we want the app
         *to pretty much return every touch*/
        return true;
    }
}
