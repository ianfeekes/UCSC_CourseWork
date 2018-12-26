/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps160 asg3
 *square.js
 *
 *Specifies a square, a subclass of Geometry
 */ 

/**
 * Specifies a Square. A subclass of Geometry.
 *
 * @author Ian Feekes
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
    super(); 
    this.generateSquareVertices(size, centerX, centerY); 
    this.n = 4; 
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
    this.vertices = [
    centerX-size/100, centerY+size/100,  
    centerX-size/100, centerY-size/100,    
    centerX+size/100, centerY+size/100,
    centerX+size/100, centerY-size/100
    ];
  }

}
