/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps1160 asg2
 *
 *htmlFunctions.js
 *Contains sendTextToHTML method*/ 


/**
 * Updates the text within an HTML element.
 *
 * @param {String} text String being sent to HTML element.
 * @param {String} htmlID The ID of an html element.
 *
 * This method simply takes the ID of the parameter and sets
 * its innerHTML text to the text parameter, used for illustrating
 * the mouse coordinates to the user when rectangles are drawn
 */
function sendTextToHTML(text, htmlID) {
    document.getElementById(htmlID).innerHTML = text; 
}
