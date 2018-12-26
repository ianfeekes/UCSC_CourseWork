/**
 * Specifies a geometric object.
 *
 * @author Ian Feekes
 * @this {Geometry}
 */
class Geometry {
  /**
   * Constructor for Geometry.
   *
   * @constructor
   */
  constructor() {
    /*Currentlly begins with empty vertices and an empty colour*/ 
    this.vertices = []; // Vertex objects. Each vertex has x-y-z.
    this.color = [];    // The color of your geometric object
    this.n = 0;         // The number of vertices of the object. 
    this.modelMatrix = new Matrix4(); //Initialize the model matrix
    this.currentAngle=0.0;
    this.vecX=0;
    this.vecY=0; 
    this.SIZE_STEP = 0;
  }

  //Sets color 
  setColor(c)
  {
    this.color = c; 
  }

  /**
   * Renders this Geometry within your webGL scene.
   * Sets color, translates vertices, sets vertices, and draws 
   */
  render() {
    //tells glsl to draw this shape's color 
    sendUniformVec4ToGLSL(this.color, u_FragColor); 
    //tells glsl to apply this shapes transformation matrix
    sendUniformMatToGLSL(this.modelMatrix, 'u_ModelMatrix');
    //tells glsl to apply this shapes vertices  
    let n = sendAttributeBufferToGLSL(this.vertices, this.n, 'a_Position'); 
    //draw the shape 
    tellGLSLToDrawCurrentBuffer(n); 
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
