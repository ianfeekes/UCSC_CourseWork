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
  constructor(size, centerX, centerY,color,cFlag) {
    super();
    this.n=24; 
    this.generateCubeVertices(centerX, centerY, size, this.color);
    this.size=size;
    this.centerX=centerX;
    this.centerY=centerY;
     if(cFlag==1)
      { 
        //console.log("setting color to grey"); 
        super.setColor(color);
      }
     else super.setRandomColor();   
     //Dissect the color and point data for easy digestion during rendering
     super.setArrayValues(); 
    // Recommendations: Might want to tilt your cube at 30 degrees relative to
    // the z-axis here. Pretty good tilt that lets us see that it's a cube.
  }

  /**
   * Generates the vertices of TiltedCube. Just a regular cube.
   *
   * @private
   */
  generateCubeVertices(centerX, centerY, size, color) {
    size/=150; 
    for(let i=0;i<24;i++)
    {
    	this.vertices[i]=new Vertex(); 
    }
    this.vertices[0].setPoints(centerX-size, centerY-size, size);
    this.vertices[1].setPoints(centerX+size,centerY-size,size); 
    this.vertices[2].setPoints(centerX+size,centerY+size,size); 
    this.vertices[3].setPoints(centerX-size,centerY+size,size); 
    this.vertices[4].setPoints(centerX-size,centerY-size,-size);
    this.vertices[5].setPoints(centerX-size,centerY+size,-size);
    this.vertices[6].setPoints(centerX+size,centerY+size,-size); 
    this.vertices[7].setPoints(centerX+size,centerY-size,-size); 
    this.vertices[8].setPoints(centerX-size,centerY+size,-size); 
    this.vertices[9].setPoints(centerX-size,centerY+size,size); 
    this.vertices[10].setPoints(centerX+size,centerY+size,size); 
    this.vertices[11].setPoints(centerX+size,centerY+size,-size);
    this.vertices[12].setPoints(centerX-size,centerY-size,-size); 
    this.vertices[13].setPoints(centerX+size,centerY-size,-size);
    this.vertices[14].setPoints(centerX+size,centerY-size,size); 
    this.vertices[15].setPoints(centerX-size,centerY-size,size); 
    this.vertices[16].setPoints(centerX+size,centerY-size,-size);
    this.vertices[17].setPoints(centerX+size,centerY+size,-size);
    this.vertices[18].setPoints(centerX+size,centerY+size,size); 
    this.vertices[19].setPoints(centerX+size,centerY-size,size); 
    this.vertices[20].setPoints(centerX-size,centerY-size,-size);
    this.vertices[21].setPoints(centerX-size,centerY-size,size);
    this.vertices[22].setPoints(centerX-size,centerY+size,size); 
    this.vertices[23].setPoints(centerX-size,centerY+size,-size);

    //console.log("about to print cube vertices \n");
    //console.log(this.vertices); 

    /*this.vertices = new Float32Array([
    centerX+size/sizeScale,  centerY+size/sizeScale,  size/sizeScale,   this.color[0],  this.color[1],  this.color[2],  
    centerX-size/sizeScale,  centerY+size/sizeScale,  size/sizeScale,   this.color[3],  this.color[4],  this.color[5],  
    centerX-size/sizeScale, centerY-size/sizeScale,  size/sizeScale,   this.color[6],  this.color[7],  this.color[8],  
    centerX+size/sizeScale, centerY-size/sizeScale,  size/sizeScale,    this.color[9],  this.color[10],  this.color[11],  
    centerX+size/sizeScale, centerY-size/sizeScale, -size/sizeScale,     this.color[12],  this.color[13],  this.color[14],  
    centerX+size/sizeScale,  centerY+size/sizeScale, -size/sizeScale,    this.color[15],  this.color[16],  this.color[17],  
    centerX-size/sizeScale,  centerY+size/sizeScale, -size/sizeScale,    this.color[18],  this.color[19],  this.color[20],  
    centerX-size/sizeScale, centerY-size/sizeScale, -size/sizeScale,    this.color[21],  this.color[22],  this.color[23]  
    ]);*/

    //indices of the vertices 
    this.indices = new Uint8Array([
      0, 1, 2,   0, 2, 3, 
      4, 5, 6,   4, 6, 7, 
      8, 9, 10,  8, 10, 11,
      12, 13, 14, 12, 14, 15,
      16, 17, 18, 16, 18, 19, 
      20, 21, 22, 20, 22, 23, 
      ]); 
  }

  /**
   * Updates the animation of the TiltedCube. Should make it rotate.
   *
   * Before rotation is translates, then it roates, then it translates back so that it 
   * is rotating about its own axis rather than the origin
   */
  updateAnimation() {
  	//console.log("updating animation of tilted cube \n"); 
    this.modelMatrix.translate(this.centerX, this.centerY, 0);
    this.modelMatrix.rotate(1,1.5,1.5,1); 
    this.modelMatrix.translate(-this.centerX, -this.centerY, 0);  
  }

  /*render()
  {

     //gl.enable(gl.DEPTH_TEST);
    //gl.clearColor(0.0, 0.0, 0.0, 1.0);
    //gl.enable(gl.DEPTH_TEST); 

    var vertexBuffer = gl.createBuffer(); 
    var indexBuffer = gl.createBuffer(); 
    
    if (!vertexBuffer || !indexBuffer) {
    return -1;
    }

    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, this.vertices, gl.STATIC_DRAW); 
    var FSIZE = this.vertices.BYTES_PER_ELEMENT; 
    
    gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, FSIZE*6,0); 
    gl.enableVertexAttribArray(a_Position); 
    gl.vertexAttribPointer(a_Color, 3, gl.FLOAT, false, FSIZE*6,FSIZE*3);
    gl.enableVertexAttribArray(a_Color); 

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer); 
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this.indices, gl.STATIC_DRAW); 

    sendUniformMatToGLSL(this.modelMatrix, 'u_ModelMatrix');
  //  gl.uniformMatrix4fv(u_ModelMatrix, false, this.modelMatrix.elements);

    gl.drawElements(gl.TRIANGLES, this.indices.length, gl.UNSIGNED_BYTE, 0);
  }*/ 

}
