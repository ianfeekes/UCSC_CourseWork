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

function tick() {
  //Updates animation of all geometry before rendering 
  currScene.updateAnimation(); 
  viewMatrix.setLookAt(0,0,2,0,0,0,0,1,0);
  //viewMatrix.setLookAt(0,0,2,0,0,0,0,1,0);
  //viewMatrix.setLookAt(g_EyeX, g_EyeY, g_EyeZ, G_atX, G_atY, 0, 0, 0, 1);
  //Checks to see if we need to be dealing with orthagonal or perspective view 
  if(perspective){
    //console.log('yes'); 
    //projMatrix.setPerspective(zoomSlider.value, canvas.width/canvas.height, 0.1, 100);
    //console.log(nearSlider.value/50);
  //console.log(farSlider.value)

  /*For some reason casting the value of the far slider to a "number" works*/ 
    projMatrix.setPerspective(zoomSlider.value, canvas.width/canvas.height, nearSlider.value/50, Number(farSlider.value/10));
  }
  else{
    //console.log("no persp"); 
    projMatrix.setOrtho(-1, 1, -1, 1, nearSlider.value/50, Number(farSlider.value/10));
  }

  /*console.log(nearSlider.value/100);
  console.log(farSlider.value); 

  projMatrix.setPerspective(zoomSlider.value, canvas.width/canvas.height, 0.1, 100);*/ 
  
  gl.uniformMatrix4fv(u_ViewMatrix, false, viewMatrix.elements);
  gl.uniformMatrix4fv(u_ProjMatrix, false, projMatrix.elements);
  currScene.render();
  requestAnimationFrame(tick, canvas);
}


