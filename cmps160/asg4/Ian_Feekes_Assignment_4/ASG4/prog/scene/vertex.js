/**
 * Specifies a vertex. 
 *
 * @author Ian Feekes 
 * @this {Vertex}
 */
class Vertex {

  constructor() {
    this.points = [];
    this.color = [];
    // For later assignments
    this.uv = [];
    this.normal = new Vector3();
  }

  setPoints(x,y,z){
    //console.log("setting points...\n"); 
  	this.points=[x,y,z]; 
  }

  setColor(r,g,b){
    //console.log("setting color...\n"); 
  	this.color=[r,g,b]; 
  }
}
