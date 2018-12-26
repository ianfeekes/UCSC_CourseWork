

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
  constructor(size, centerX, centerY,color,cFlag) {
    super(); 
    //triangles get three vertices, yay something easy 
    this.n=3; 
    //first create the vertex objects and set their point coordinates
    this.generateTriangleVertices(size, centerX, centerY); 
    /*Then we determine how we should color each vertex once they have been 
      initialized. */ 
    if(cFlag==1)super.setColor(color); 
    else super.setRandomColor(); 
    //Buffers everything set into the vertices into separate arrays for processing
    super.setArrayValues()
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
    size/=100; 
    for(let i=0;i<this.n;i++)
    {
      this.vertices[i]=new Vertex(); 
    }
    //now we hard code points of triangle, not necessarily equilateral
    this.vertices[0].setPoints(centerX,centerY+size,0);
    this.vertices[1].setPoints(centerX-size, centerY-size,0);
    this.vertices[2].setPoints(centerX+size, centerY-size,0); 
  }
  
}