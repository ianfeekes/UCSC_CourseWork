/**
 * Special cube who's coordinates are used for lighting 
 *
 * @author "Ian Feekes"
 * @this {TiltedCube}
 */
class Lcube extends Geometry {
  
  constructor(size, centerX, centerY, centerZ) {
    super();
    this.generateCubeVertices(size, centerX, centerY, centerZ);
   // this.vertices.push(cubeVertices);
   this.centerX=centerX;
   this.centerY=centerY;
   this.centerZ=centerZ; 
   this.size=size; 
   this.thetaIncr=.003; 
   this.incrX = .007; 
   this.incrZ = .007; 

   this.theta=0; 

   this.transX=0;
   this.transY=0;
   this.transZ=0; 
    
  }

  translate()
  {
    this.modelMatrix.setTranslate(0, 0, -1.6);
   // this.modelMatrix.setTranslate(0,0,incr); 
  }

  render() {
    gl.enable(gl.DEPTH_TEST);
  /*var indexBuffer = gl.createBuffer();
  if (!indexBuffer) {
    console.log('Failed to create the buffer object');
    return false;
  }
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this.indices, gl.STATIC_DRAW);  */ 
    //super.render(36, gl.TRIANGLES, 3);
    let vColorBuffer = gl.createBuffer(); 
    gl.bindBuffer(gl.ARRAY_BUFFER, vColorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, this.colors, gl.STATIC_DRAW);
    gl.vertexAttribPointer(a_Color, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_Color);

    let normBuffer = gl.createBuffer(); 
    gl.bindBuffer(gl.ARRAY_BUFFER, normBuffer); 
    gl.bufferData(gl.ARRAY_BUFFER, this.normals, gl.STATIC_DRAW); 
    gl.vertexAttribPointer(a_Normal, 3, gl.FLOAT, false, 0,0); 
    gl.enableVertexAttribArray(a_Normal); 

    sendUniformMatToGLSL(this.modelMatrix.elements, u_ModelMatrix);  
    sendAttributeBufferToGLSL(this.vertices, 3, a_Position);

    //added messing around with normal matrix variable 
    normalMatrix.setInverseOf(this.modelMatrix); 
    normalMatrix.transpose(); 
    gl.uniformMatrix4fv(u_NormalMatrix, false, normalMatrix.elements); 


    tellGLSLToDrawCurrentBuffer(gl.TRIANGLES, 36);
  // super.render(this.indices.length, gl.TRIANGLES, 3); 
    gl.disable(gl.DEPTH_TEST);


  } 

  /**
   * Generates the vertices of TiltedCube. Just a regular cube.
   *
   * @private
   */
  generateCubeVertices(size, centerX, centerY, centerZ) {


    this.vertices = new Float32Array([
      // Vertex coordinates and color
      centerX-size/2,  centerY+size/2,  centerZ+size,      centerX-size/2, centerY-size/2,  centerZ+size,       centerX+size/2, centerY-size/2,  centerZ+size,    //t0
      centerX-size/2,  centerY+size/2,  centerZ+size,      centerX+size/2,  centerY+size/2,  centerZ+size,      centerX+size/2, centerY-size/2,  centerZ+size,    //t1

      centerX+size/2,  centerY+size/2,  centerZ+size,      centerX+size/2, centerY-size/2,  centerZ+size,       centerX+size/2, centerY-size/2, centerZ-size,    //t2
      centerX+size/2,  centerY+size/2,  centerZ+size,      centerX+size/2, centerY-size/2, centerZ-size,    centerX+size/2,  centerY+size/2, centerZ-size,      //t3

      centerX+size/2,  centerY+size/2, centerZ-size,   centerX+size/2, centerY-size/2, centerZ-size,    centerX-size/2, centerY-size/2, centerZ-size,          //t4
      centerX+size/2,  centerY+size/2, centerZ-size,   centerX-size/2, centerY-size/2, centerZ-size,    centerX-size/2,  centerY+size/2, centerZ-size,         //t5
        
      centerX-size/2,  centerY+size, centerZ-size,   centerX-size/2, centerY-size/2, centerZ-size,    centerX-size/2, centerY-size/2,  centerZ+size,          //t6
      centerX-size/2,  centerY+size/2, centerZ-size,   centerX-size/2, centerY-size/2, centerZ+size,       centerX-size/2,  centerY+size/2,  centerZ+size,      //t7
       
      centerX-size/2,  centerY+size/2, centerZ-size,   centerX-size/2,  centerY+size/2,  centerZ+size,      centerX+size/2,  centerY+size/2,  centerZ+size,      //t8
      centerX-size/2,  centerY+size/2, centerZ-size,   centerX+size/2,  centerY+size/2,  centerZ+size,      centerX+size/2,  centerY+size/2, centerZ-size,      //t9

      centerX-size/2, centerY-size/2,  centerZ+size,       centerX-size/2, centerY-size/2, centerZ-size,    centerX+size/2, centerY-size/2, centerZ-size,       //t10
      centerX-size/2, centerY-size/2,  centerZ+size,       centerX+size/2, centerY-size/2, centerZ-size,    centerX+size/2, centerY-size/2,  centerZ+size        //t11
    ]);   

    //Unless we are rotating it on the z plane (which I won't do) these can remain static 
    this.normals = new Float32Array([
    0,0,0,   0,0,1,  0,0,1,      0,0,0,   0,0,1,  0,0,1, 
    1,0,0,   1,0,0,  1,0,0,      1,0,0,   1,0,0,  1,0,0,
    0,1,0,   0,1,0,  0,1,0,      0,1,0,   0,1,0,  0,1,0, 
    -1,0,0,  -1,0,0, -1,0,0,     -1,0,0,  -1,0,0, -1,0,0, 
    0,-1,0,  0,-1,0,  0,-1,0,     0,-1,0,  0,-1,0, 0,-1,0,
    0,0,-1,  0,0,-1,  0,0,-1,   0,0,-1,   0,0,-1, 0,0,-1 

    ]); 

     this.indices = new Uint8Array([
     0, 1, 2,   0, 2, 3,    // front
     4, 5, 6,   4, 6, 7,    // right
     8, 9,10,   8,10,11,    // up
    12,13,14,  12,14,15,    // left
    16,17,18,  16,18,19,    // down
    20,21,22,  20,22,23     // back
 ]);  
  
  }

  move(x,y)
  { 
    if(moveFlag && Math.abs(g_EyeX-lX)<.3 || Math.abs(g_EyeY-lY)<.3)
    {
      this.modelMatrix.translate(x, y, 0); 
      lX+=x;
      lY+=y; 
    }
  }

  rotate(incr)
  {
    //rotation should probably be around camera rather than shape center but 
    // we will figure it out as it goes 
     //this.modelMatrix.translate(this.centerX, this.centerY, 0);
     this.modelMatrix.translate(g_EyeX, g_EyeY, 0); 
     this.modelMatrix.rotate(incr,0,0,1); 
     this.modelMatrix.translate(-g_EyeX, -g_EyeY, 0); 
     //this.modelMatrix.translate(-this.centerX, -this.centerY, 0); 
  }

  /**
   * Updates the animation of the TiltedCube. Should make it rotate.
   */
  updateAnimation() {
    /*if(moveFlag)
    {
      this.modelMatrix.translate(0.01, 0.01, 0); 
    }*/ 
    /* 
    this.lXprev = lX; 
    this.lZprev = lZ; 

    this.theta+= this.thetaIncr; 
    if(this.theta>2.1){this.thetaIncr*=-1;} 
    else if(this.theta<-2.1){this.thetaIncr*=-1;}
    if(this.theta>=360)
    {
      this.theta%=360; 
      this.LXprev = 0;
      this.LZprev=0; 
    } 
    lX=Math.sin(this.theta)*1.3; 
    lZ=Math.cos(this.theta)*1.3; 
    this.incrX=lX-this.lXprev; 
    this.incrZ=lZ-this.lZprev; 

   this.modelMatrix.translate(this.incrX,0,this.incrZ);
   */ 

   //this.incr+=.0001;
   /*lX+=this.incrX; 
   lZ+=this.incrZ

   if(lX>1.5)this.incrX*=-1; 
   if(lX<-1.5)this.incrX*=-1;
   if(lZ>1.5)this.incrZ*=-1; 
   if(lZ<-1.5)this.incrZ*=-1;  */ 

  }

}
