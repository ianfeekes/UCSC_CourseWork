/**
 * Specifies a Triangle. A subclass of Geometry.
 *
 * @author "Your Name Here"
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
    //
    // YOUR CODE HERE
    //
    super(); 
    this.generateTriangleVertices(size, centerX, centerY); 

    //console.log("in triangle constructor\n"); 
    //console.log("centerx: "+centerX+" centery: "+centerY+", size: "+size); 
    //console.log("I am a triangle!\n"); 
    //ar size = size; 
    //var centerX = centerX; 
    //let centerY = centerY; 
    
    //this.generateTriangleVertices(size, centerX, centerY); 
  
   // this.n=3; 
    // Recommendations: Remember that Triangle is a subclass of Geometry.
    // "super" keyword can come in handy when minimizing code reuse.
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
    //
    // YOUR CODE HERE
    //
    this.vertices = new Float32Array([   
    //centerX-size/100, centerY-size/100,  
   // centerX, centerY+2,    
 //   centerX+size/100, centerY+size/100,
 //   centerX-size/100, centerY-size/100,
    centerX, centerY+size/100, 
    centerX-size/100, centerY-size/100, 
    centerX+size/100, centerY-size/100
    // 0, 0.5,   -0.5, -0.5,   0.5, -0.5
    ]);
    this.n=3; 
    
    // Recommendations: Might want to call this within your Triangle constructor.
    // Keeps your code clean :)
  }
}
