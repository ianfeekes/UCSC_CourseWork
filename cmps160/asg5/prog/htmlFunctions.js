/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *
 *htmlFunctions.j
 *
 *holds sendTextToHTML, which I don't think I've used in 4 assignments
 */ 

/**
 * Updates the text within an HTML element.
 *
 * @param {String} text String being sent to HTML element.
 * @param {String} htmlID The ID of an html element.
 */
function sendTextToHTML(text, htmlID) {
    htmlID.innerHTML = text;
}

