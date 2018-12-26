/**
 * Specifies a WebGL scene.
 *
 * @author Ian Feekes
 * @this {Scene}
 *
 * Ian Feekes
 * #1474914
 * ifeekes@ucsc.edu
 * cmps160 asg2
 * scene.js
 * 
 * This file holds all the functionbs for the scene class, which behaves essentially
 * as a linked list, appending objects to itself and calling their functions as desired.
 */

class Scene {
  /**
   * Constructor for Scene.
   *
   * @constructor
   */
  constructor() {
    this.geometries = []; // Geometries being drawn on canvas
    gl.clearColor(0, 0, 0, 1); //Clears the canvas to black and prepares to draw
    gl.clear(gl.COLOR_BUFFER_BIT); 
  }

  /**
   * Adds the given geometry to the the scene.
   *
   * @param {Geometry} geometry Geometry being added to scene
   */
  addGeometry(geometry) {
     this.geometries.push(geometry); 
  }

  /**
   * Clears all the geometry within the scene.
   */
  clearGeometry() {
    this.geometries = []; 
    render(); 
  }

  /**
   * Updates the animation for each geometry in geometries.
   */
  updateAnimation() {
    //iterates through all shapes and tells them to update their animation 
    for(var i=0;i<this.geometries.length;i++)
    {
      this.geometries[i].updateAnimation(); 
    }
  }

  /**
   * Renders all the Geometry within the scene.
   */
  render() {
    //iterates through all the shapes and tells them to draw themselves 
    for(var i =0;i<this.geometries.length;i++)
    {
      this.geometries[i].render(); 
    }
  }

}
