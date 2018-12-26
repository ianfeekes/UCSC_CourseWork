/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *cmps160
 *asg3 
 *tick.js
 *
 *sets up the animation of this program
 */ 

/**
 * Responsible for animating the Scene.
 */
function tick() {
		//each shape makes its own unique translations
	    currScene.updateAnimation(); 
	    //apply the translations to the vertex matrices and draw it
	    render(); 
	    //requrest that the browser calls tick
   		requestAnimationFrame(tick);
}
