package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// MainThread.java
// Wildfire Studios
// Created by: Ian Feekes
// Modified by: 
// Notes: 
//-------------------------------------------------------------------------------------

import android.graphics.Canvas;
import android.view.SurfaceHolder;

public class MainThread extends Thread {
    /* DATA --------------------------------------------------------------------------- */
    public static final int MAX_FPS = 30;       /*Max frames per second, most phones can do this*/
    private double averageFPS;
    private SurfaceHolder surfaceHolder;
    private GamePanel gamePanel;
    private boolean running;
    public static Canvas canvas;


    /* CONSTRUCTOR -------------------------------------------------------------------- */
    
    public MainThread(SurfaceHolder surfaceHolder, GamePanel gamePanel){
        super();
        this.surfaceHolder=surfaceHolder;
        this.gamePanel=gamePanel;
    }
    
    @Override
    public void run() {
        long startTime;
        long timeMillis = 1000 / MAX_FPS;
        long waitTime;
        long frameCount = 0;
        long totalTime = 0;
        long targetTime = 1000 / MAX_FPS;
        
        while (running) {
            startTime = System.nanoTime();
            canvas = null;

            // initializes canvas
            try {
                canvas = this.surfaceHolder.lockCanvas();
                synchronized (surfaceHolder) {
                    // updates and draws canvas with current data
                    this.gamePanel.update();
                    this.gamePanel.draw(canvas);
                }
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                if(canvas!=null)
                {
                    try{
                        surfaceHolder.unlockCanvasAndPost(canvas);
                    }catch(Exception e) {e.printStackTrace();}
                }
            }

            // internal run stuff
            timeMillis = (System.nanoTime() - startTime)/1000000;
            waitTime = targetTime - timeMillis;            
            try
            {
                if(waitTime>0)
                {
                    this.sleep(waitTime);
                }
            }catch(Exception e) {
                e.printStackTrace();
            }
            totalTime+= System.nanoTime() - startTime;
            frameCount++;
            
            if(frameCount==MAX_FPS)
            {
                averageFPS=1000/((totalTime/frameCount)/1000000);
                frameCount=0;
                totalTime=0;
                //System.out.println(averageFPS);
            }
        }
        /* Edit by Joe fix the AppCrash when click back but*/
            System.exit(0);
    }

    /* MODIFIERS ---------------------------------------------------------------------- */

    public void setRunning(boolean running)
    {
        this.running = running;
    }
}

