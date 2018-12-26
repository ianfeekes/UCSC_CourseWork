/**
 * A tilted cube that has a checkerboard texture applied to it. A subclass of
 * TiltedCube.
 *
 * @author "Ian Feekes"
 * @this {CheckerCube}
 */
class CheckerCube extends TiltedCube {
  /**
   * Constructor for CheckerCube
   *
   * @constructor
   * @returns {CheckerCube}
   */
  constructor(size,centerX,centerY,color,cFlag) {
     gl.enable(gl.DEPTH_TEST);
    super(size, centerX, centerY, color, cFlag); 
    if(cFlag==1)this.generateSpecialUV(); 
    else(this.generateUVCoordinates());    
    super.setUVArray();
    let path;  
    if(!textureFile.value){path = "./flcl.jpg"}
    else
    {
     let filename= document.getElementById('textureImage').value.split(/(\\|\/)/g).pop();
     path = "./"+filename; 
    }
    //callback simply sets the objects texture. This is ripped from the book 
    create2DTexture(path,gl.LINEAR, gl.LINEAR, gl.REPEAT, gl.REPEAT, (texture) => 
    {
         this.texture = texture; 
    }); 
  }

  //brute force attempt at generating cube faces of different patterns 
  generateSpecialUV()
  {
    this.vertices[0].uv = [0.0,  0.0];
     this.vertices[1].uv = [3.0,  0.0];
     this.vertices[2].uv = [3.0,  3.0];
     this.vertices[3].uv = [0.0,  3.0];
     this.vertices[4].uv = [0.0,  0.0];
     this.vertices[5].uv = [2.0,  0.0];
     this.vertices[6].uv = [2.0,  1.0];
     this.vertices[7].uv = [0.0,  1.0];
     this.vertices[8].uv = [0.0,  0.0];
     this.vertices[9].uv = [1.0,  0.0];
     this.vertices[10].uv = [1.0,  0.5];
     this.vertices[11].uv = [0.0,  0.5];
     this.vertices[12].uv = [0.0,  0.5];
     this.vertices[13].uv = [1.0,  0.5];
     this.vertices[14].uv = [1.0,  1.0];
     this.vertices[15].uv = [0.0,  1.0];
     this.vertices[16].uv = [0.0,  0.0];
     this.vertices[17].uv = [1.0,  0.0];
     this.vertices[18].uv = [1.0,  1.0];
     this.vertices[19].uv = [0.0,  1.0];
     this.vertices[20].uv = [0.0,  0.0];
     this.vertices[21].uv = [1.0,  0.0];
     this.vertices[22].uv = [1.0,  1.0];
     this.vertices[23].uv = [0.0,  1.0];
  }


  /**
   * Generates the texture coordinates of CheckerCube.
   *
   * @private
   */
   //brute force attempt to generate cube faces of normal type 
  generateUVCoordinates() {
    //
    // YOUR CODE HERE
    //
   //console.log("generating normal ones\n"); 
    this.vertices[0].uv = [0.0,  0.0]
    this.vertices[1].uv = [1.0,  0.0]
    this.vertices[2].uv = [1.0,  1.0]
    this.vertices[3].uv = [0.0,  1.0]
    this.vertices[4].uv = [0.0,  0.0]
    this.vertices[5].uv = [1.0,  0.0]
    this.vertices[6].uv = [1.0,  1.0]
    this.vertices[7].uv = [0.0,  1.0]
    this.vertices[8].uv = [0.0,  0.0]
    this.vertices[9].uv = [1.0,  0.0]
    this.vertices[10].uv = [1.0,  1.0]
    this.vertices[11].uv = [0.0,  1.0]
    this.vertices[12].uv = [0.0,  0.0]
    this.vertices[13].uv = [1.0,  0.0]
    this.vertices[14].uv = [1.0,  1.0]
    this.vertices[15].uv = [0.0,  1.0]
    this.vertices[16].uv = [0.0,  0.0]
    this.vertices[17].uv = [1.0,  0.0]
    this.vertices[18].uv = [1.0,  1.0]
    this.vertices[19].uv = [0.0,  1.0]
    this.vertices[20].uv = [0.0,  0.0]
    this.vertices[21].uv = [1.0,  0.0]
    this.vertices[22].uv = [1.0,  1.0]
    this.vertices[23].uv = [0.0,  1.0]

    //console.log("creating uv vertices...\n"); 
    //console.log(this.vertices); 
    //create2DTexture(textureImage.value, gl.LINEAR, gl.NEAREST_MIPMAP_LINEAR, gl.REPEAT, gl.REPEAT, send2DTextureToGLSL); 

    // Recomendations: Remember uv coordinates are defined from 0.0 to 1.0.
  }

  /**
   * Renders CheckerCube.
   */
  /*render() {
    //
    // YOUR CODE HERE
    //
    var vertexTexBuffer = gl.createBuffer(); 
    var FSIZE = this.vertices.BYTES_PER_ELEMENT; 
    gl.vertexAttribPointer(a_Position,2,gl.FLOAT,false,FSIZE*4,0);
    gl.enableVertexAttribArray(a_Position); 
    var a_TexCoord = gl.getAttribLocation(gl.program, 'a_TexCoord');
    gl.vertexAttribPointer(a_TexCoord,2,gl.FLOAT,false,FSIZE*4, FSIZE*2); 
    gl.enableVertexAttribArray(a_TexCoord);

    create2DTexture(textureImage.value, gl.LINEAR, gl.NEAREST_MIPMAP_LINEAR, gl.REPEAT, gl.REPEAT, send2DTextureToGLSL); 
    tellGLSLToDrawCurrentBuffer(this.n); 
    // Recomendations: This will be the first time render will need to be
    // overloaded. Why? Because this is a textured geometry, not a geometry
    // which relies on a color value.
  }*/
}
