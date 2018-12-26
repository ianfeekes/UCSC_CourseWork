/**
 * Specifies a Circle. A subclass of Geometry.
 *
 * @author Ian Feekes
 * @this {Circle}
 *
 * Ian Feekes
 * ifeekes@ucsc.edu
 * #1474914
 * cmps160 asg2
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
  constructor(radius, segments, centerX, centerY) {
    //
    // YOUR CODE HERE
    //
    super(); 
    this.generateCircleVertices(radius, segments, centerX, centerY);
    this.n=segments*2; 
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
        var angle = delta * (i+1);
        let x = centerX+ Math.cos(angle)*radius/100; 
        let y = centerY+ Math.sin(angle)*radius/100; 
        this.vertices.push(x); 
        this.vertices.push(y); 
        this.vertices.push(centerX); 
        this.vertices.push(centerY); 
     }
    //for(var theta = 0; theta<=(2*Math.PI); theta+=delta)
   // {
      /*Any given point that we want to draw will have its x position as 
        cos(theta) plus its center x coordinate, and likewise its y position
        will be sin(theta) plus its center y coordinate. We then only need
        to append the x and y values computed to the shapes vertices array*/ 
    /*  let x=radius/100*Math.cos(theta)+centerX; 
      let y=radius/100*Math.sin(theta)+centerY; 
      console.log("Pushing x y coords"+x+", "+y+"\n"); 
      this.vertices.push(x);
      this.vertices.push(y);  
    }*/ 


/*     this.vertices.push(centerX, centerY); 
     for(var i=0;i<=500;i++)
     {
        let x = centerX+radius/100*Math.cos(i*2*Math.PI/200);
        let y = centerY+radius/100*Math.sin(i*2*Math.PI/200); 
        this.vertices.push(x); 
        this.vertices.push(y); 
     }*/ 
    /*

    points.push(center);
for (i = 0; i <= 100; i++){
    points.push(center + vec2(
        r*Math.cos(2*Math.PI/200),
        r*Math.sin(2*Math.PI/200) 
    ));
}*/ 
  }
}
