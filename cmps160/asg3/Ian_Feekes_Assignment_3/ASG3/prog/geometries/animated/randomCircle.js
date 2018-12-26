/**
 * Specifies a circle which moves randomly.
 *
 * @author Ian Feekes 
 * @this {RandomCircle}
 */
class RandomCircle extends Circle {
  /**
   * Constructor for RandomCircle.
   *
   * @constructor
   * @param {Number} radius The radius of the random circle being constructed
   * @param {Integer} segements The number of segments composing the circle
   * @param {Number} centerX The x-position of the circle being constructed
   * @param {Number} centerY The y-position of the circle being constructed
   * @returns {RandomCircle} RandomCircle object created
   */
  constructor(radius, segments, centerX, centerY) {
    //Initializes it like its a normal circle 
    super(radius,segments,centerX,centerY); 
    //Gives it an initial direction so that it doesn't just stay in place when initialized 
    this.changeDirection(); 
  }

  /**
   * Updates random circle's animation. Changes modelMatrix into a translation
   * matrix translating into a random direction.
   *
   * Every 50 frames (about once every two seconds or so) it will compute a 
   * random new direction vector. It translates its coordinates based on its
   * current direction 
   */
  updateAnimation() {
    if(Math.floor(Math.random() * Math.floor(50))==1)this.changeDirection();
    this.vecX=this.xDir;
    this.vecY=this.yDir; 
    this.modelMatrix.translate(this.vecX, this.vecY, 0); 
  }

  /*Generates a new direction vector for the circle to move in, first deciding
  * about whether its x and y directions should be positive or negative, and then
  * computing a slightly variable velocity
  */ 
  changeDirection()
  {
    let posX; 
    let posY; 
    if(Math.floor(Math.random() * Math.floor(2))==0)posX=1;
    else posX=-1; 
     if(Math.floor(Math.random() * Math.floor(2))==0)posY=1; 
    else posY=-1;  
    this.xDir = posX*(Math.floor(Math.random()*Math.floor(2)))/250; 
    this.yDir = posY*(Math.floor(Math.random()*Math.floor(2)))/250; 
  }

}
