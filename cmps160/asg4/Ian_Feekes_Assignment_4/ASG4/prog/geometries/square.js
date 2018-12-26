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
  constructor(size, centerX, centerY, color, cFlag) {
    super(); 
    /*since I'm changing all the glsl functions to work with gl.TRIANGLES
      squares are now composed of two triangles, so they get 6 vertices */ 
    this.n = 6; 
    //create the vertices and set their elements first 
    this.generateSquareVertices(size, centerX, centerY);
    /*test to see if the color values must be randomized. This has to be done
      AFTER the vertices have been initialized */  
    if(cFlag==1)
      {
        super.setColor(color);
        } 
    else {
      super.setRandomColor(); 
    }
    super.setArrayValues()
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
   //First we initialize the vertices
   //console.log("generating square vertices...\n"); 
   size/=100; 
   for(let i=0;i<this.n;i++)
   {
    this.vertices[i]= new Vertex(); 
   }
   //Then we sloppily hard code the values for each vertex
   this.vertices[0].setPoints(centerX-size, centerY+size, 0);
   //this.vertices[0].points = [centerX-size, centerY+size, 0]; 
   this.vertices[1].setPoints(centerX-size, centerY-size, 0);
   this.vertices[2].setPoints(centerX+size, centerY-size, 0);
   this.vertices[3].setPoints(centerX+size, centerY-size, 0);
   this.vertices[4].setPoints(centerX+size, centerY+size, 0);
   this.vertices[5].setPoints(centerX-size, centerY+size, 0);
   

   /*this.vertices[1].points.elements = [centerX-size, centerY-size, 0];
   this.vertices[2].points.elements = [centerX+size, centerY-size, 0];
   this.vertices[3].points.elements = [centerX+size, centerY-size, 0];
   this.vertices[4].points.elements = [centerX+size, centerY+size, 0];
   this.vertices[5].points.elements = [centerX-size, centerY+size, 0]; */ 
  // console.log("printing newly initialized vertices: \n"); 
   //console.log(this.vertices); 
  }


}
