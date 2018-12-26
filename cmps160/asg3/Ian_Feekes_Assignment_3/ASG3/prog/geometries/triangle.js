

/**
 * Specifies a Triangle. A subclass of Geometry.
 *
 * @author Ian Feekes
 * @this {Triangle}
 */
class Triangle extends Geometry {
  /**
   * Constructor for Triangle.
   *
   * @constructor
   * @param {Number} size The size of the triangle drawn
   * @param {Number} centerX The center x-position of the triangle
   * @param {Number} centerY The center y-position of the triangle
   */
  constructor(size, centerX, centerY) {
    super(); 
    this.generateTriangleVertices(size, centerX, centerY); 
  }

  /**
   * Generates the vertices of the Triangle.
   *
   * @private
   * @param {Number} size The size of the triangle drawn
   * @param {Number} centerX The center x-position of the triangle
   * @param {Number} centerY The center y-position of the triangle
   */
  generateTriangleVertices(size, centerX, centerY) {
    this.vertices = new Float32Array([   
    centerX, centerY+size/100, 
    centerX-size/100, centerY-size/100, 
    centerX+size/100, centerY-size/100
    ]);
    this.n=3; 
  }
  
}