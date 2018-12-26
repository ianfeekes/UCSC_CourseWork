/**
 * Specifies a Circle. A subclass of Geometry.
 *
 * @author Ian Feekes
 * @this {Circle}
 *
 * Ian Feekes
 * ifeekes@ucsc.edu
 * #1474914
 * cmps160 asg3
 * circle.js
 * 
 * circle class containing a constructor, and a generator for the 
 * vertices of a circle 
 */
class Circle extends Geometry {
  /**
   * Constructor for Circle.
   *
   * @constructor
   * @param {Number} radius The radius of the circle being constructed
   * @param {Integer} segments The number of segments composing the circle
   * @param {Number} centerX The central x-position of the circle
   * @param {Number} centerY The central y-position of the circle
   */
  constructor(radius, segments, centerX, centerY,color,cFlag) {
    super(); 
    this.n=segments; 
    this.generateCircleVertices(radius, segments, centerX, centerY);
    if(cFlag==1)super.setColor(color); 
    else super.setRandomColor(); 
    this.centerX=centerX; 
    this.centerY=centerY; 
    this.radius=radius; 
    this.segments = segments; 
    super.setArrayValues()
  }

  render()
  {
    sendAttributeBufferToGLSL(this.color_data, 3, 'a_Color');
        sendAttributeBufferToGLSL(this.data, 3, 'a_Position'); 
        //tells glsl to apply this shapes transformation matrix
        sendUniformMatToGLSL(this.modelMatrix, 'u_ModelMatrix');
        //tells glsl to apply this shapes vertices  =
        //tellGLSLToDrawCurrentBuffer(this.n);
        gl.drawArrays(gl.TRIANGLE_FAN, 0, this.n)
        //gl.drawArrays(gl.TRIANGLES, 0, pointCount); 
  }

  /**
   * Generates the vertices of the Circle.
   *
   * @private
   * @param {Number} radius The radius of the circle being constructed
   * @param {Integer} segments The number of segments composing the circle
   * @param {Number} centerX The central x-position of the circle
   * @param {Number} centerY The central y-position of the circle
   */
  generateCircleVertices(radius, segments, centerX, centerY) {
    /*Mathematically delta represents the change in the angle needed to 
     *draw the desired number of vertices*/ 
     var delta = 2*Math.PI/(segments-1); 
     for(var i=0;i<=segments;i++)
     {  

       //var j = i*3; 
        var angle = delta * (i+1);
        let x = centerX+ Math.cos(angle)*radius/100; 
        let y = centerY+ Math.sin(angle)*radius/100; 

        //Initialize as a new vertex 
        let out = new Vertex();
        //let cen = new Vertex(); 
        out.setPoints(x,y,0);
       // cen.setPoints(centerX, centerY,0);  
        this.vertices.push(out);
        //this.vertices.push(cen); 
       
        //Set its data points to those calculated earlier
        //this.vertices[i].setPoints(x,y, 0);
        // this.vertices[i+1].setPoints(this.centerX, this.centerY, 0); 
/* 
        this.vertices.push(x); 
        this.vertices.push(y); 
        this.vertices.push(0);      //These lines are added to give z coordinates
        this.vertices.push(this.color[j]);
        this.vertices.push(this.color[j+1]); 
        this.vertices.push(this.color[j+2]); 
        this.vertices.push(centerX); 
        this.vertices.push(centerY);
        this.vertices.push(0);      //Added z coordinates 
        this.vertices.push(this.color[j+3]);
        this.vertices.push(this.color[j+4]); 
        this.vertices.push(this.color[j+5]);  */
     }
     console.log(this.vertices); 
  }

}