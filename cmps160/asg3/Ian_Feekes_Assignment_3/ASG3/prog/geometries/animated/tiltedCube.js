/**
 * Specifies a tilted cube which rotates.
 *
 * @author Ian Feekes 
 * @this {TiltedCube}
 */
class TiltedCube extends Geometry {
  /**
   * Constructor for TiltedCube.
   *
   * @constructor
   * @returns {TiltedCube} Geometric object created
   */
  constructor(size, centerX, centerY) {
    super();
    this.generateCubeVertices(centerX, centerY, size, this.color);
    this.size=size;
    this.centerX=centerX;
    this.centerY=centerY; 
    this.n=8; 

    // Recommendations: Might want to tilt your cube at 30 degrees relative to
    // the z-axis here. Pretty good tilt that lets us see that it's a cube.
  }

  /**
   * Generates the vertices of TiltedCube. Just a regular cube.
   *
   * @private
   */
  generateCubeVertices(centerX, centerY, size, color) {
    let sizeScale = 150; 
    //vertex coordinates and color 
    this.verticesColors = new Float32Array([
    centerX+size/sizeScale,  centerY+size/sizeScale,  size/sizeScale,     color[0],  color[1],  color[2],  // White
    centerX-size/sizeScale,  centerY+size/sizeScale,  size/sizeScale,     color[0],  color[1],  color[2],  // White
    centerX-size/sizeScale, centerY-size/sizeScale,  size/sizeScale,    color[0],  color[1],  color[2],  // White
    centerX+size/sizeScale, centerY-size/sizeScale,  size/sizeScale,     color[0],  color[1],  color[2],  // White
    centerX+size/sizeScale, centerY-size/sizeScale, -size/sizeScale,     color[0],  color[1],  color[2],  // White
    centerX+size/sizeScale,  centerY+size/sizeScale, -size/sizeScale,     color[0],  color[1],  color[2],  // White
    centerX-size/sizeScale,  centerY+size/sizeScale, -size/sizeScale,     color[0],  color[1],  color[2],  // White
    centerX-size/sizeScale, centerY-size/sizeScale, -size/sizeScale,     color[0],  color[1],  color[2]  // White
    ]);

    //indices of the vertices 
    this.indices = new Uint8Array([
      0, 1, 2,   0, 2, 3, 
      0, 3, 4,   0, 4, 5, 
      0, 5, 6,   0, 6, 1, 
      1, 6, 7,   1, 7, 2, 
      7, 4, 3,   7, 3, 2, 
      4, 7, 6,   4, 6, 5
      ]); 
  }

  /*Cubes require a different way of buffering vertex data*/ 
  render(){
    //first set the color 
    sendUniformVec4ToGLSL(this.color, u_FragColor); 
    var vertexColorBuffer = gl.createBuffer(); 
    var indexBuffer = gl.createBuffer(); 
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexColorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, this.verticesColors, gl.STATIC_DRAW); 
    var FSIZE = this.verticesColors.BYTES_PER_ELEMENT; 
    var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
    if(a_Position < 0) {
      console.log('Failed to get the storage location of a_Position');
      return -1;
    }
    gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, FSIZE*6,0); 
    gl.enableVertexAttribArray(a_Position); 
    gl.uniformMatrix4fv(u_ModelMatrix, false, this.modelMatrix.elements);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer); 
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this.indices, gl.STATIC_DRAW); 
    gl.drawElements(gl.TRIANGLES, this.indices.length, gl.UNSIGNED_BYTE, 0);
  }

  /**
   * Updates the animation of the TiltedCube. Should make it rotate.
   *
   * Before rotation is translates, then it roates, then it translates back so that it 
   * is rotating about its own axis rather than the origin
   */
  updateAnimation() {
    this.modelMatrix.translate(this.centerX, this.centerY, 0);
    this.modelMatrix.rotate(1,1.5,1.5,1); 
    this.modelMatrix.translate(-this.centerX, -this.centerY, 0); 
  }

}
