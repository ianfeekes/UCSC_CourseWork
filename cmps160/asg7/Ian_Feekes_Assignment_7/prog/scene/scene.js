/**
 * Specifies a WebGL scene.
 *
 * @author "Ian Feekes"
 * @this {Scene}
 */
class Scene {
  /**
   * Constructor for Scene.
   *
   * @constructor
   */
  constructor() {
    this.geometries = []; 
  }

  /**
   * Adds the given geometry to the the scene.
   */
  /*addWorldObject(worldObject) {
    this.worldObjects.push(worldObject);
  }*/

  addGeometry(geometry) {
    this.geometries.push(geometry);
  }

  /**
   * Clears all the geometry within the scene.
   */
  clearGeometry() {
    while (this.geometries.length > 0) {
      this.geometries.pop();
    }
    this.geometries=[]; 
  }

  //Rendering the objects will in turn also update the animations.
  //Updating is done individually through their own classes 
  updateAnimation() {
    //myGeometry.updateAnimation();
    for(let i = 0; i < this.geometries.length; i++) {
      this.geometries[i].updateAnimation();
  }
 }

  render() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    for(let i = 0; i < this.geometries.length; i++) {
      if(!gToggle && this.geometries[i] instanceof Lcube)
      {

      }
      else this.geometries[i].render();
    }
  }

}
