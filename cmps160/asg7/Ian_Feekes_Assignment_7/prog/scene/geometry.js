/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *
 *geometry
 */ 


/**
 * Specifies a geometric object.
 *
 * @author "Ian Feekes"
 * @this {Geometry}
 */
class Geometry {
  /**
   * Constructor for Geometry.
   *
   * @constructor
   */
  constructor() {
    this.vertices = []; // Vertex objects. Each vertex has x-y-z.
    this.modelMatrix = new Matrix4(); // Model matrix applied to geometric object
    this.x = [];
    this.y = [];
    this.n=0; 
    this.SIZE_STEP = 0;
    this.shader = null; 
    //allows us to buffer colors
    this.colors=[]; 
    this.data = [];
    this.uvVals = []; 
    this.normals = []; 
    this.color_data = []; 
    for(let i=0;i<200;i+=6)
    {
      //this.colors.push(Math.random()); 
      let c = Math.floor(Math.random()*255);
      for(let j=0;j<6;j++)this.colors.push(c/255);  
    }
    this.colors = new Float32Array(this.colors); 

  }

  // c=[4,g,b]
  setColor(c)
  {
    this.colors=[];
    for(let i=0;i<50;i++){
      this.colors.push(c[0]); 
      this.colors.push(c[1]); 
      this.colors.push(c[2]); 
    }
    this.colors=new Float32Array(this.colors); 
  }

  getColor(){
    let a=[this.colors[0], this.colors[1], this.colors[2]];
    return a; 
  }

  /**
   * Renders this Geometry within your webGL scene.
   */
  render(numberOfVertices, renderMethod, space) {
    let vColorBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vColorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, this.colors, gl.STATIC_DRAW);
    

    gl.vertexAttribPointer(a_Color, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_Color);
    /*Send the normal. I'm pretty over send attribute buffer to glsl bugs
      so this is going to be done to a copied function from the textbok */ 
   // if(!initArrayBuffer(gl, 'a_Normal', this.normals, 3, gl.FLOAT))return-1; 

    sendUniformMatToGLSL(this.modelMatrix.elements, u_ModelMatrix);  
    sendAttributeBufferToGLSL(this.vertices, space, a_Position);
    tellGLSLToDrawCurrentBuffer(renderMethod, numberOfVertices);
  }

  /**
   * Responsible for updating the geometry's modelMatrix for animation.
   * Does nothing for non-animating geometry.
   *
   * The super method does nothing. Each shape has their own unique update
   * animation method
   */
  updateAnimation() {
    return;
  }
}


