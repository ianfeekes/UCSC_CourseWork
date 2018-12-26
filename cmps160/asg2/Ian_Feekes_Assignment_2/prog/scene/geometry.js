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
  }

  setColor(c)
  {
    this.color = c; 
  }

  /**
   * Renders this Geometry within your webGL scene.
   */
  render() {
    //
    // YOUR CODE HERE
    sendUniformVec4ToGLSL(this.color, u_FragColor); 
    let n = sendAttributeBufferToGLSL(this.vertices, this.n, 'a_Position'); 
    tellGLSLToDrawCurrentBuffer(n); 
    // Recommendations: sendUniformVec4ToGLSL(), tellGLSLToDrawCurrentBuffer(),
    // and sendAttributeBufferToGLSL() are going to be useful here.
  }
}
