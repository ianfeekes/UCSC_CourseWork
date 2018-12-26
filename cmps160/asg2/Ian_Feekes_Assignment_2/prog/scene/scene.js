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
   *
   * Initializes the empty shapes array and clears the canvas in preparation for 
   * being drawn on.
   */
  constructor() {
    this.geometries = []; // Geometries being drawn on canvas
    gl.clearColor(0, 0, 0, 1);
    gl.clear(gl.COLOR_BUFFER_BIT); 
  }

  /**
   * Adds the given geometry to the the scene.
   *
   * @param {Geometry} geometry Geometry being added to scene
   *
   * Simply pushes the argument object into the array of shapes held by scene 
   */
  addGeometry(geometry) {
    this.geometries.push(geometry); 
  }

  /**
   * Clears all the geometry within the scene.
   *
   * Empties the array of all objects and renders it
   */
  clearGeometry() {
    this.geometries = []; 
    render(); 
  }

  /**
   * Renders all the Geometry within the scene.
   *
   * Simply iterates through all shapes held by the scene and makes them render
   * themselves. 
   */
  render() {
    for(var i =0;i<this.geometries.length;i++)
    {
      this.geometries[i].render(); 
    }
  }
}
