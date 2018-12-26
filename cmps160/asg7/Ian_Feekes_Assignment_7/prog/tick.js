/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *cmps160 asg5
 *tick.js
 *
 *pretty much copied directly from previous assignments. It goes through the 
 *scene and animates all the geometries. It adjust the view matrix for 
 *perspective purposes. It calls requestAnimationFrame to the canvas
 */ 
 let ticker = 15; 
 let aVal = 2.5; 
 let deathFlag = false; 
 let onceFlag=  false; 
 let aFluc=30; 
 let rate=.5; 
 let prevX=g_EyeX;
 let prevY=g_EyeY; 
 let inc = .5/15; 

 /*Returns true if the player's camera coordinates lie within the specified bounds of the venue*/ 
 function playerWinBounds()
 {
  return(.71>g_EyeY && g_EyeY> -.31
      && .93>g_EyeX && g_EyeX> -.47); 
 }

function tick() {
  //console.log(g_EyeX+" "+g_EyeY); 
  /*Sometimes there is a strange bug where the camera position will jump up an exponential, or even
   *infinite number when running into cubes, and a rather hackey solution to this is simply setting 
   *the constraint where you can't move the camera an obsene amount each frame, and if that is the 
   *case you simply set it back to the value of the camera coordinate from the previous frame. This 
   *works because the camera values only jump to obscene values when the user moves in very specific 
   *ways*/ 
  if(Math.abs(prevX-g_EyeX)>1)g_EyeX=prevX;
  if(Math.abs(prevY-g_EyeY)>1)g_EyeY=prevY; 
  if(Math.abs(prevY-g_EyeY)<1 && Math.abs(prevX-g_EyeX)<1)
  {
    lightCube.move(g_EyeX-prevX, g_EyeY-prevY); 
//  else {console.log("foo"); lightCube.move(g_EyeX-prevX, prevY-g_EyeY);}//lightCube.move(g_EyeX-prevX, g_EyeY-prevY-.3); }
  }

  //Updates animation of all geometry before rendering 
  currScene.updateAnimation(); 
  viewMatrix.setLookAt(g_EyeX, g_EyeY, g_EyeZ, G_atX, G_atY, 0, 0, 0, 1);
  //Checks to see if we need to be dealing with orthagonal or perspective view 
  if(perspective){
  /*For some reason casting the value of the far slider to a "number" works*/ 
    projMatrix.setPerspective(30, canvas.width/canvas.height, .2, 10);
  }
  else{
    projMatrix.setOrtho(-1, 1, -1, 1, .2, 10);
  }



  //set camera parameters 
  gl.uniformMatrix4fv(u_ViewMatrix, false, viewMatrix.elements);
  gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);
  gl.uniform3f(u_AmbientLight, aVal/10, aVal/10, aVal/10); 
  //constantly throb ambient light 
  ambientThrob(); 

  //detect if the user has their glowstick out and change lighting variables based on this. 
  if(gToggle)
  {
    gl.uniform1f(u_LightSwitch, 1.0); 
    // Set the light direction (in the world coordinate)
    gl.uniform3f(u_LightPosition, lX, lY, lZ);
  }
  else if(!gToggle)
  {
    gl.uniform1f(u_LightSwitch, 0.0);
  }

  sendTextToHTML(strArr[idx], textBox); 

  if(outOfBounds())
  {
    idx=4; 
    if(!deathFlag)
    {
    currScene.clearGeometry(); 
    let c = new Cube(8,0,0,true); 
    c.setColor([.5,.5,.5]); 
    currScene.addGeometry(c);
    deathFlag=true; 
    }
  } 

  if(playerWinBounds())
  {
    idx=2; 
    //aFluc-=5; 
    aFluc=20; 
    inc=.5/15+.03;
    if(Math.random() == 1){console.log("gToggling..."); gToggle= !gToggle; }
    lZ=3; 
    lX+=Math.random()*4; 
    lY+=Math.random()*4; 
    lX-=Math.random()*4; 
    lY-=Math.random()*4; 
     gl.uniform3f(u_LightPosition, lX, lY, lZ);
  }

  prevX=g_EyeX;
  prevY=g_EyeY; 

  currScene.render();
  currScene.updateAnimation(); 
  requestAnimationFrame(tick, canvas);
}

/*Creates a pulsing ambient light for the rave atmosphere*/ 
function ambientThrob()
{
  if(ticker<aFluc)
  {
    ticker+=rate; 
    aVal+=inc; 
  }
  else if(ticker<aFluc*2)
  {
    ticker+=rate; 
    aVal-=inc; 
  }
  else ticker =0; 
}


