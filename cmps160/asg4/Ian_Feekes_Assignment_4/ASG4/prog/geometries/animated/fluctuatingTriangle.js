/**
 * Specifies a triangle which fluctuates in size (grows and shrinks).
 *
 * @author "Your Name"
 * @this {FluctuatingTriangle}
 */
class FluctuatingTriangle extends Triangle {
  /**
   * Constructor for FluctuatingTriangle.
   *
   * @constructor
   * @param {Number} size The size of the triangle drawn
   * @param {Number} centerX The center x-position of the triangle
   * @param {Number} centerY The center y-position of the triangle
   */
  constructor(size, centerX, centerY,color,cFlag) {

    super(size,centerX,centerY,color,cFlag);          //first construct a normal triangle
    this.scale=size;  //scale variable to keep track of the medium fluctuation of growth 
    this.g_last = Date.now();
    this.currentSize = size/100;  
    this.SIZE_STEP = 10/600;
    this.incr = .001;
    this.i=35; 
    this.centerX=centerX;
    this.centerY=centerY; 
  }

  /**
   * Updates the animation for FluctuatingTriangle. Grows and shrinks the
   * triangle in size.
   */
  updateAnimation() {
    if(this.i>70)
    {
      this.i=0;
      this.SIZE_STEP*=-1; 
    }
    this.i++; 
    this.modelMatrix.translate(this.centerX, this.centerY,0); 
    this.modelMatrix.scale(1+this.SIZE_STEP, 1+this.SIZE_STEP, 1);
    this.modelMatrix.translate(-this.centerX, -this.centerY,0); 
  }
}
