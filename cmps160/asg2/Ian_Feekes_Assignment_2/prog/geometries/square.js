/**
 * Specifies a Square. A subclass of Geometry.
 *
 * @author "Your Name Here"
 * @this {Square}
 */
class Square extends Geometry {
  /**
   * Constructor for Square.
   *
   * @constructor
   * @param {Number} size The size of the square drawn
   * @param {Number} centerX The center x-position of the square
   * @param {Number} centerY The center y-position of the square
   */
  constructor(size, centerX, centerY) {
    //
    // YOUR CODE HERE
    //
    super(); 
    this.generateSquareVertices(size, centerX, centerY); 
    this.n = 4; 
    // Recommendations: Remember that Square is a subclass of Geometry.
    // "super" keyword can come in handy when minimizing code reuse.
  }

  /**
   * Generates the vertices of the square.
   *
   * @private
   * @param {Number} size The size of the square drawn
   * @param {Number} centerX The center x-position of the square
   * @param {Number} centerY The center y-position of the square
   */
  generateSquareVertices(size, centerX, centerY) {
    //
    // YOUR CODE HERE
    //
    this.vertices = [
    //This is probably incorrect
    centerX-size/100, centerY+size/100,  
    centerX-size/100, centerY-size/100,    
    centerX+size/100, centerY+size/100,
    centerX+size/100, centerY-size/100
    ];
    
    // Recommendations: Might want to call this within your Square constructor.
    // Keeps your code clean :)
  }
}
