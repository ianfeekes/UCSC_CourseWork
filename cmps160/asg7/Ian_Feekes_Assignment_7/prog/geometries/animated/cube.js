/**
 * Specifies a tilted cube which rotates.
 *
 * @author "Ian Feekes"
 * @this {TiltedCube}
 */
class Cube extends Geometry {
  
  constructor(size, centerX, centerY, flag) {
    super();
    this.generateCubeVertices(size, centerX, centerY);
   // this.vertices.push(cubeVertices);
    this.x.push(centerX);
    this.y.push(centerY);
    if(flag)this.translate();
    this.size=size; 
    this.centerX=centerX; 
    this.centerY=centerY;  

    // Recommendations: Might want to tilt your cube at 30 degrees relative to
    // the z-axis here. Pretty good tilt that lets us see that it's a cube.
  }

  translate()
  {
    this.modelMatrix.setTranslate(0, 0, -4.1);
    //this.modelMatrix.setTranslate(0,0,-.3); 
  }

  render() {
    gl.enable(gl.DEPTH_TEST);
    gl.enable(gl.BLEND); 
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA); 
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
    //gl.disable(gl.BLEND); 


  } 

  /**
   * Generates the vertices of TiltedCube. Just a regular cube.
   *
   * @private
   */
  generateCubeVertices(size, centerX, centerY) {
    this.vertices = new Float32Array([
      centerX-size,  centerY+size,  size,      centerX-size, centerY-size,  size,       centerX+size, centerY-size,  size,    //t0
      centerX-size,  centerY+size,  size,      centerX+size,  centerY+size,  size,      centerX+size, centerY-size,  size,    //t1

      centerX+size,  centerY+size,  size,      centerX+size, centerY-size,  size,       centerX+size, centerY-size, -size,    //t2
      centerX+size,  centerY+size,  size,      centerX+size, centerY-size, -size,    centerX+size,  centerY+size, -size,      //t3

      centerX+size,  centerY+size, -size,   centerX+size, centerY-size, -size,    centerX-size, centerY-size, -size,          //t4
      centerX+size,  centerY+size, -size,   centerX-size, centerY-size, -size,    centerX-size,  centerY+size, -size,         //t5
        
      centerX-size,  centerY+size, -size,   centerX-size, centerY-size, -size,    centerX-size, centerY-size,  size,          //t6
      centerX-size,  centerY+size, -size,   centerX-size, centerY-size,  size,       centerX-size,  centerY+size,  size,      //t7
       
      centerX-size,  centerY+size, -size,   centerX-size,  centerY+size,  size,      centerX+size,  centerY+size,  size,      //t8
      centerX-size,  centerY+size, -size,   centerX+size,  centerY+size,  size,      centerX+size,  centerY+size, -size,      //t9

      centerX-size, centerY-size,  size,       centerX-size, centerY-size, -size,    centerX+size, centerY-size, -size,       //t10
      centerX-size, centerY-size,  size,       centerX+size, centerY-size, -size,    centerX+size, centerY-size,  size        //t11
    ]);  

/*    this.vertices = new Float32Array([
     this.centerX+size, this.centerY+size, size,  this.centerX-size, this.centerY+size,size,  this.centerX-size, this.centerY-size, size,   this.centerX+size, this.centerY-size, size, // v0-v1-v2-v3 front
     this.centerX+size, this.centerY+size,size,  this.centerX+size, this.centerY-size, size,  this.centerX+size, this.centerY-size,-size,   this.centerX+size, this.centerY+size,-size, // v0-v3-v4-v5 right
     this.centerX+size, this.centerY+size,size,  this.centerX+size, this.centerY+size,-size,  this.centerX-size, this.centerY+size,-size,  this.centerX-size, this.centerY+size, size, // v0-v5-v6-v1 up
     this.centerX-size, this.centerY+size,size,  this.centerX-size, this.centerY+size,-size,  this.centerX-size, this.centerY-size,-size,  this.centerX-size, this.centerY-size, size, // v1-v6-v7-v2 left
     this.centerX-size, this.centerY-size,-size,  this.centerX+size, this.centerY-size,-size,  this.centerX+size, this.centerY-size, size,  this.centerX-size, this.centerY-size, size, // v7-v4-v3-v2 down
     this.centerX+size, this.centerY-size,-size,  this.centerX-size, this.centerY-size,-size,  this.centerX-size, this.centerY+size,-size,   this.centerX+size, this.centerY+size,-size  // v4-v7-v6-v5 back
     ]); */ 

    //Unless we are rotating it on the z plane (which I won't do) these can remain static 
    this.normals = new Float32Array([
  /*       // Normal
    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  // v0-v1-v2-v3 front
    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,  // v0-v3-v4-v5 right
    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  // v0-v5-v6-v1 up
   -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  // v1-v6-v7-v2 left
    0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,  // v7-v4-v3-v2 down
    0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   // v4-v7-v6-v5 back
    
    0,0,0,  0,0,0, 0,0,0, 0,0,0,
    0,0,0,   0,0,0, 0,0,0, 0,0,0,
    0,0,0, 0,0,0 ,0,0,0 ,0,0,0,
    0,0,0 ,0,0,0,0,0,0,0    */ 

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

     this.colors = new Float32Array([
      0,0,1,   0,0,1,  0,0,1,      0,0,1,   0,0,1,  0,0,1, 
       0,1,.5,   0,1,.5,  0,1,.5,      0,1,.5,   0,1,.5,  0,1,.5, 
    1,0,0,   1,0,0,  1,0,0,      1,0,0,   1,0,0,  1,0,0,
   // 0,1,0,   0,1,0,  0,1,0,      0,1,0,   0,1,0,  0,1,0, 
    1,0,0,  1,0,0, 1,0,0,     1,0,0,  1,0,0, 1,0,0, 
    .5,0,.5,  .5,0,.5,  .5,0,.5,     .5,0,.5,  .5,0,.5, .5,0,.5,
    0,0,1,  0,0,1,  0,0,1,   0,0,1,   0,0,1, 0,0,1 
      ]); 
  
  }

  /**
   * Updates the animation of the TiltedCube. Should make it rotate.
   */
  updateAnimation() {
   
  }

}
