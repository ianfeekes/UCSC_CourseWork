/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *cmps160 asg5
 *eventFunctions.js
 *
 *This file has been altered significantly from the previous assignment. 
 *Mostly used for dealing with initializing the functionality of html 
 *elements, allong with generating an array of tilted cubes for a maze  
 */ 

 let zoomSlider;          //Responsible for holding camera zoom value 
 let speedSlider;         //Responsible for user camera movement speed 
 let rotSlider;           //Responsible for user camera rotation speed 
 let nearSlider;          //Near values
 let farSlider;           //Far values 
 let orthoButton;         //Button toggler for orthogonal viewing
 let perButton;           //Button toggler for perspective viewing 
 let perspective=true;    //Perspective toggler initialization
 let absX, absY;          //For use in camera position movement 

/*Initiallizes a few sliders, goes through my attempt to procedurally generate the world*/ 
function initEventHandelers() {
  //Initialize the scene we are working with 
  currScene = new Scene();
  zoomSlider = document.getElementById('zoom');
  speedSlider = document.getElementById('speed'); 
  rotSlider = document.getElementById('rot'); 
  nearSlider = document.getElementById('near'); 
  farSlider = document.getElementById('far'); 
  orthoButton = document.getElementById('orthoButton');
  perButton = document.getElementById('perButton'); 
  //Button on click listeners toggle between perspective being true and false 
  orthoButton.onclick = function(){perspective = false;};
  perButton.onclick = function(){perspective=true;};
  //This adds the main world cube which is set to a sickening purple
  let mag = [.5,0.0,1.0]; 
  let baseCube = new Cube(1.0,0,0,true); 
  baseCube.setColor(mag); 
  currScene.addGeometry(baseCube);
    /*Loops through x and y coordinates representing where to generate grid cubes*/ 
    for(let i = 0; i < 10; i++) 
    {
      for(let j = 0; j < 10; j++) 
      {
        /*Logic determining where we want to initialize our grid cubes to give the world
          a somewhat maze-like appearence */ 
        if(map1[j][i]==1)
        {
          /*Create the grid cube and add it to geometry*/ 
          let gridCube = new Cube(.1, -.9+(j*.2), .9-(i*.2), false); 
          //gridCube.setColor(mag); 
         // gridCube.colors=verticesColors; 
          currScene.addGeometry(gridCube); 
        }
      }
    }
    //Initializes the key listener functionality for processing which key was pressed 
    document.onkeydown = function(ev) { 
     processKey(ev); 
    };
    //Start up the animation clock 
    tick();
}

/*Processes camera movement on key events*/ 
function processKey(ev) {
  absX = Math.abs(G_atX);
  absY = Math.abs(G_atY);
  var rightAngle = (angleRotation - 90);
  var leftAngle = (angleRotation + 90);
  if(Math.sign(rightAngle) == -1) { rightAngle += 360; }
  if(leftAngle >= 360) { leftAngle -= 360; }
  if(ev.keyCode == 68 || ev.keyCode == 39) goRight(rightAngle); 
  else if(ev.keyCode == 65 || ev.keyCode == 37)goLeft(leftAngle)
  else if(ev.keyCode == 87 || ev.keyCode == 38)goForward(); 
  else if(ev.keyCode == 83 || ev.keyCode == 40)goBackward(); 
  else if(ev.keyCode == 74)leftRotate(); 
  else if(ev.keyCode == 76)rightRotate();
  else if(ev.keyCode == 73)zoomSlider.value -= 3;
  //a distusting hack
  else if(ev.keyCode == 75){zoomSlider.value ++; zoomSlider.value++; zoomSlider.value++;}
}

function goBackward()
{
  let backVal = speedSlider.value/1000; 
  if(Math.sign(G_atX) == -1 && Math.sign(G_atY) == 1) {
      if(absX > absY) {
        g_EyeY -= backVal* (absY/absX);
        g_EyeX += backVal;
      } else {
        g_EyeY -= backVal;
        g_EyeX += backVal * (absX/absY);
      } 
    } else if(Math.sign(G_atX) == -1 && Math.sign(G_atY) == -1){             
      if(absX > absY) {
        g_EyeY += backVal * (absY/absX);
        g_EyeX += backVal;
      } else {
        g_EyeY += backVal;
        g_EyeX += backVal * (absX/absY);
      } 
    } else if (Math.sign(G_atX) == 1 && Math.sign(G_atY) == -1) {
      if(absX > absY) {
        g_EyeY += backVal * (absY/absX);
        g_EyeX -= backVal;
      } else {
        g_EyeY += backVal;
        g_EyeX -= backVal * (absX/absY);
      } 
    } else {
      if(absX > absY) {
        g_EyeY -= backVal * (absY/absX);
        g_EyeX -= backVal;
      } else {
        g_EyeY -= backVal;
        g_EyeX -= backVal * (absX/absY);
      } 
    }
}

function goForward()
{
  let forVal = speedSlider.value/1000; 
  if(Math.sign(G_atX) == -1 && Math.sign(G_atY) == 1) { 
      if(absX > absY) {
        g_EyeY += forVal * (absY/absX);
        g_EyeX -= forVal;
      } else {
        g_EyeY += forVal;
        g_EyeX -= forVal * (absX/absY);
      } 
    } else if(Math.sign(G_atX) == -1 && Math.sign(G_atY) == -1){                
      if(absX > absY) {
        g_EyeY -= forVal * (absY/absX);
        g_EyeX -= forVal;
      } else {
        g_EyeY -= forVal;
        g_EyeX -= forVal * (absX/absY);
      } 
    } else if (Math.sign(G_atX) == 1 && Math.sign(G_atY) == -1) {
      if(absX > absY) {
        g_EyeY -= forVal * (absY/absX);
        g_EyeX += forVal;
      } else {
        g_EyeY -= forVal;
        g_EyeX += forVal * (absX/absY);
      } 
    } else {
      if(absX > absY) {
        g_EyeY += forVal * (absY/absX);
        g_EyeX += forVal;
      } else {
        g_EyeY += forVal;
        g_EyeX += forVal * (absX/absY);
      } 
    } 
}

function goRight(leftAngle)
{
  let lVal = speedSlider.value/1000; 
  if(leftAngle <45)
  {
    g_EyeY+=lVal*(absX/absY); 
    g_EyeX += lVal;
  }
  else if(leftAngle<90)
  {
    g_EyeY += lVal;
    g_EyeX += lVal * (absY/absX);
  }
  else if(leftAngle<135)
  {
    g_EyeY += lVal;
    g_EyeX -= lVal * (absY/absX);
  }
  else if(leftAngle<180)
  {
    g_EyeY += lVal * (absX/absY);
    g_EyeX -= lVal;
  }
  else if(leftAngle<225)
  {
    g_EyeY -= lVal * (absX/absY);
    g_EyeX -= lVal;
  }
  else if(leftAngle<270)
  {
    g_EyeY -= lVal * (absX/absY);
    g_EyeX -= lVal;
  }
  else if(leftAngle<315)
  {
    g_EyeY -= lVal;
    g_EyeX += lVal * (absY/absX);
  }
  else 
  {
    g_EyeY -= lVal * (absX/absY);
    g_EyeX += lVal;
  } 
}

/*Processes the angle for how to increment the camera*/ 
function goLeft(leftAngle)
{
  //console.log(leftAngle); 
  /* let lVal = speedSlider.value/1000; 
  if(Math.sin(leftAngle)>0)
  {
    g_EyeY+=lVal*(absX/absY);
  }
  else g_EyeY-=lVal*(absX/absY); 
  if(Math.cos(leftAngle)>0)
  {
    g_EyeX+=lVal*(absX/absY);
  }
  else g_EyeX-=lVal*(absX/absY); */ 

  let lVal = speedSlider.value/1000; 
  if(leftAngle <45)
  {
    g_EyeY+=lVal*(absX/absY); 
    g_EyeX += lVal;
  }
  else if(leftAngle<90)
  {
    g_EyeY += lVal;
    g_EyeX += lVal * (absY/absX);
  }
  else if(leftAngle<135)
  {
    g_EyeY += lVal;
    g_EyeX -= lVal * (absY/absX);
  }
  else if(leftAngle<180)
  {
    g_EyeY += lVal * (absX/absY);
    g_EyeX -= lVal;
  }
  else if(leftAngle<225)
  {
    g_EyeY -= lVal * (absX/absY);
    g_EyeX -= lVal;
  }
  else if(leftAngle<270)
  {
    g_EyeY -= lVal * (absX/absY);
    g_EyeX -= lVal;
  }
  else if(leftAngle<315)
  {
    g_EyeY -= lVal;
    g_EyeX += lVal * (absY/absX);
  }
  else 
  {
    g_EyeY -= lVal * (absX/absY);
    g_EyeX += lVal;
  } 
}

function leftRotate()
{ 
    let rotIncr = rotSlider.value/10; 
   // console.log(rotIncr);
    angleRotation += rotIncr;
    angleRotation%=360;
    G_atX = 100 * Math.cos(angleRotation*(Math.PI/180));
    G_atY = 100 * Math.sin(angleRotation*(Math.PI/180));
}

function rightRotate()
 {
    let rotIncr = rotSlider.value/10; 
    //console.log(rotIncr); 
    angleRotation -= rotIncr;
    angleRotation %=360;
    G_atX = 100 * Math.cos(angleRotation*(Math.PI/180));
    G_atY = 100 * Math.sin(angleRotation*(Math.PI/180));
  }

/*Resets the canvas' width and height to default values as specified on 
  the canvas initialization in main, and then calls reload*/ 
function resize() {
  canvas.width=window.innerWidth-200; 
  canvas.height=window.innerHeight-250; 
  window.location.reload(); 
}


