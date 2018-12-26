/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps160 asg1
 *
 *eventFunctions.js
 *This contains methods for nearly all interactions between the user and
 *the canvas
 */ 

/*Initialization of global variables*/ 
let redSlider;     //red slider object initialized on initEventHandlers; 
let greenSlider;   //green slider object initialized on initEventHandlers; 
let blueSlider;    //blue slider object initialized on initEventHandlers; 
let sizeSlider;    //Size slider object initialized on initEventHandlers; 
let coordBox;      //ID of box where coordinates will be sent to with sendTextToHTML 
var g_points=[];   //Array for the position of a mouse press 
var g_colors = []; // The array to store the color of a point
var g_sizes = [];  //Array storing the size of each point
var currColor = [];//float value to hold the current color 
var currSize;      //float value to hold the current size 
var clearButton;   //clear canvas button 

/**
 * Responsible for initializing buttons, sliders, radio buttons, etc. present
 * within your HTML document.
 *
 * This will be the first eventFunction method called by main(). It initializes
 * the slider, button, and textbox objects and sets up an onclick listener for the 
 * button. It also initializes the array for point sizes and computes the initial
 * point colour and size before the canvas is rendered. 
 */
function initEventHandelers() {
  /*get the sliders and initialize them into variables with their names*/ 
  redSlider = document.getElementById("redSlider"); 
  greenSlider = document.getElementById("greenSlider"); 
  blueSlider = document.getElementById("blueSlider");
  sizeSlider = document.getElementById("sizeSlider"); 
  //get the ID of the coordinate box 
  coordBox = document.getElementById("coordBox");
  clearButton = document.getElementById('clearButton')
  clearButton.onclick = function(){clearCanvas();};  
  /*initialize the sizeArr which contains the ellipsoid values for point radius*/  
  sizeArr = new Float32Array([10.0, 10.0]);
  /*initialize the point colour to the default slider of a grey*/ 
  changePointColor([redSlider.value/100, greenSlider.value/100, blueSlider.value/100, 1.0]); 
  /*initialize the point size to the default slider value of 50px xy*/ 
  changePointSize(sizeSlider.value); 
}

/* This is called every time the mouse is clicked. It immediately computes the colour
 * point and size to make sure that the new point(s) to be drawn accurately resemble
 * the user desires. It then computes the mouse coordinates and updates the text box.
 * It then calibrates the coordinates so that the new point's coordinates will be on
 * the exact part of the canvas the user clicked on. 
 * The point, color, and size value of a new point is pushed on the each respective 
 * array, and render is called to draw the new rectangle. 
 */ 
function click(ev) {
  /*immediately render our new colour and size so that it will always be as desired*/ 
  changePointColor([redSlider.value/100,  greenSlider.value/100, blueSlider.value/100, 1.0]);
  changePointSize(sizeSlider.value)
  var x = ev.clientX;    
  var y = ev.clientY;  
  /*Load in the mouse coordinates*/ 
  sendTextToHTML("x: "+x+" y: "+y, "coordBox"); 
  /*Calibrate the mouse coordinates to display the point on the proper part of the html doc canvas*/ 
  var rect = ev.target.getBoundingClientRect();
  x = ((x - rect.left) - 250)/(250);
  y = (250 - (y - rect.top))/(250);
  g_points.push([x,y]);              //store the coordinates
  g_colors.push(currColor);          //store the colours
  g_sizes.push(currSize);            //store the size 
  // Calls render function to clear the canvas and draw each of the points
  render(); 
}

/**
 * Renders the scene on the HTML canvas.
 *
 * Render first clears the colour buffer for use of future points. 
 * It then iterates through each point, first setting the size into
 * a gl data buffer. It then creates the vertex, sets the color, and
 * draws the array. 
 */
function render() {
  gl.clear(gl.COLOR_BUFFER_BIT); 
  var len = g_points.length;
  for(var i = 0; i < len; i ++) {
      var xy = g_points[i];               //position
      var rgba = g_colors[i];             //colour
      var pointSize = g_sizes[i];         //size 
      /*Bind point size data to the gl shaders*/
      sendUniformFloatToGLSL(pointSize, p_size); 
     /*Creates a vertex with position on doc, x coord, y coord, and z=0 */ 
     gl.vertexAttrib3f(a_Position, xy[0], xy[1], 0.0);
     /*Creates the colour into the gl buffer with the rgba values computed*/ 
     sendUniformVec4ToGLSL(rgba, u_FragColor);
     //draws the point*/ 
     gl.drawArrays(gl.POINTS, 0, 1); 
   }
}

/**
 * Clears the HTML canvas.
 * clearCanvas removes all elements from the point, color, size arrays
 * and then calls render to illustrate the newly blank canvas
 */
function clearCanvas() { 
  g_sizes = []; 
  g_points = [];
  g_colors = []; 
  render(); 
}

/**
 * Changes the size of the points drawn on HTML canvas.
 *
 * @param {float} size Real value representing the size of the point.
 *
 * Sets the global variable holding the current size of poitns to be drawn
 * and then calls render to illustrate this with any new points 
 */
function changePointSize(size) {
  currSize = size;  
  render();
}

/**
 * Changes the color of the points drawn on HTML canvas.
 *
 * @param {float} color Color value from 0.0 to 1.0.
 *
 * Sets the current colour for all points to be drawn with values 
 * rgb taken from the arguments, where @param color is constantly 
 * being altered by the sliders
 */
function changePointColor(color) {
  currColor = [color[0], color[1], color[2], color[3]];
}
