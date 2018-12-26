/**
 * Specifies a square which spins realtive to its center.
 *
 * @author "Your Name"
 * @this {SpinningSquare}
 */
class SpinningSquare extends Square {
  
  /**
   * Constructor for SpinningSquare.
   *
   * @constructor
   * @param {Number} size The size of the square drawn
   * @param {Number} centerX The center x-position of the square
   * @param {Number} centerY The center y-position of the square
   * @returns {SpinningSquare} SpinningSquare object created
   */
  constructor(size, centerX, centerY, color, cFlag) {   
    super(size, centerX, centerY,color,cFlag); 
    this.centerX=centerX;
    this.centerY=centerY; 
    this.g_last = Date.now(); //Last time when this function was called 
    this.ANGLE_STEP = 45.0;     //Angle step for change of angle each frame
  }

  /**
   * Updates the animation for spinning square. Rotates the square by spinAngle
   * relative to its center.
   *
   * This method took forever for me to figure out. The squares need to
   * first be translated so that they are rotating along the axis of their
   * own coordinates rather than the origin, then rotation is applied, then
   * it is translated back to their own initial coordinates. 
   */
  updateAnimation() {
    this.modelMatrix.translate(this.centerX, this.centerY, 0); 
    this.modelMatrix.rotate(1,0,0,1); 
    this.modelMatrix.translate(-this.centerX, -this.centerY, 0); 
  }

}
