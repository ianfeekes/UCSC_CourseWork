/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps160 asg4
 *
 *eventFunctions.js
 *This contains methods for nearly all interactions between the user and
 *the canvas. It has additional sliders and incorporates the use of classes
 *for the different shapes the user might want to draw
 */ 

/*Initialization of global variables*/ 
let redSlider;     //red slider object initialized on initEventHandlers; 
let greenSlider;   //green slider object initialized on initEventHandlers; 
let blueSlider;    //blue slider object initialized on initEventHandlers; 
let sizeSlider;    //Size slider object initialized on initEventHandlers; 
let segmentSlider; //Segment slider object initialized on initEventHandlers; 
let coordBox;      //ID of box where coordinates will be sent to with sendTextToHTML 
let clearButton;   //clear canvas button
let triangleButton;//button clicked for drawing triangles 
let squareButton;  //button clicked for drawing squares
let circleButton;  //button clicked for drawing circles 
let cubeButton;    //button clicked for drawing cubes 
let testButton; 
let colorButon;    //button to cycle between solid color and rainbows 
var g_points=[];   //Array for the position of a mouse press 
var g_colors = []; // The array to store the color of a point
var g_sizes = [];  //Array storing the size of each point
var currColor = [];//float value to hold the current color 
var pScale;        //value to hold the current size for linear transformations
var numSegments;   //value representing the number of vertices of circle to be drawn;
var currScene;     //Object holding the current scene with all of its shapes 
let drawMode; 
let objFile; 
let textureImage;  //element containing texture image; 
let addGeometryToScene; //element button containing geometry adder; 

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
  segmentSlider = document.getElementById("segmentSlider"); 
 // testButton = document.getElementById("testButton"); 
  colorButton = document.getElementById("colorButton"); 
  //get the ID of the coordinate box 
  coordBox = document.getElementById("coordBox");
  clearButton = document.getElementById("clearButton");
  triangleButton = document.getElementById("triangleButton");
  squareButton = document.getElementById("squareButton"); 
  circleButton = document.getElementById("circleButton"); 
  cubeButton = document.getElementById("cubeButton"); 
  addGeometryToScene = document.getElementById("addGeometryToScene"); 
  objFile = document.getElementById("objFile"); 
  textureFile = document.getElementById("textureImage"); 

  clearButton.onclick = function(){clearCanvas();};  
  //The canvas is initially set up to draw squares
  drawMode = "squares"; 

  colorButton.onclick = function changeText(){
    if(colorButton.value==="Solid Color D:")
    {
      colorButton.value="RAINBOW :D"; 
    }
    else colorButton.value="Solid Color D:"; 
  }

  addGeometryToScene.addEventListener("click", function(event) {
    event.preventDefault();
    loadFile(objFile.value.split(/(\\|\/)/g).pop(), function(textData){
      let lObj = new LoadedOBJ(textData); 
      if(textureFile.value)
      {
        let pathName = textureFile.value.split(/(\\|\/)/g).pop();
        let readablePath = "./"+pathName; 
        create2DTexture(path, gl.LINEAR, gl.LINEAR, gl.CLAMP_TO_EDGE, gl.CLAMP_TO_EDGE, (texture) => {
          lObj.texture = texture; 
        });
      }
      else{
          //set the vertex coloring 
      }
      currScene.addGeometry(lObj); 
       });
    });

  squareButton.onclick = function(){drawMode = "squares";}; 
  triangleButton.onclick = function(){drawMode = "triangles";};
  circleButton.onclick = function(){drawMode = "circles";}; 
  cubeButton.onclick= function(){drawMode = "cubes";}; 
  currScene = new Scene(); //initializes the scene  

  /*initialize the sizeArr which contains the ellipsoid values for point radius*/  
  sizeArr = new Float32Array([10.0, 10.0]);
  /*initialize the point colour to the default slider of a grey*/ 
  changePointColor([redSlider.value/100, greenSlider.value/100, blueSlider.value/100, 1.0]); 
  /*initialize the point size to the default slider value of 50px xy*/ 
  changePointSize(sizeSlider.value/1.5); 

  //We make our initial object extra large for fun 
  let tcu = new CheckerCube(pScale*3,0,0, currColor,1); 
     //tcu.generateSpecialUV();
     //let tcu = new MultiTextureCube(pScale, x, y, currColor, flag); 
      currScene.addGeometry(tcu); 
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
  changePointSize(sizeSlider.value/1.5)
  var x = ev.clientX;    
  var y = ev.clientY;  
  /*Load in the mouse coordinates*/ 
  sendTextToHTML("x: "+x+" y: "+y, "coordBox"); 
  /*Calibrate the mouse coordinates to display the point on the proper part of the html doc canvas*/ 
  var rect = ev.target.getBoundingClientRect();
  x = ((x - rect.left) - 250)/(250);
  y = (250 - (y - rect.top))/(250);
  /*Detects which shape the user wants to draw, creates the object, and pushes it
   *into the array of objects held by the scene we are rendering*/ 
  var flag; 
  if(colorButton.value==="Solid Color D:") flag=1; 
  else flag=0; 

  if(drawMode =="triangles"){
     //let tri = new FluctuatingTriangle(pScale, x, y); 
     let tri= new FluctuatingTriangle(pScale, x, y, currColor, flag); 
     currScene.addGeometry(tri);
     }
  else if(drawMode =="circles"){
     /*numSegments only needs to be computed if we are drawing a circle. This allows us 
       so save on computational power for only calculating it in this case*/ 
     numSegments = segmentSlider.value; 
     let circ = new RandomCircle(pScale, numSegments, x, y, currColor, flag); 
     currScene.addGeometry(circ);
  }
  else if(drawMode =="squares"){
     let squ = new SpinningSquare(pScale, x, y, currColor,flag); 
     currScene.addGeometry(squ); 
  } 
  else if(drawMode =="cubes"){
    //let cu = new TiltedCube(pScale,x,y);
    if(textureFile.value)
    {
      //console.log("texture found \n"); 
     let tcu = new CheckerCube(pScale,x,y, currColor,0); 
     //tcu.generateSpecialUV();
     //let tcu = new MultiTextureCube(pScale, x, y, currColor, flag); 
      currScene.addGeometry(tcu); 
    }
    else{
    let cu = new TiltedCube(pScale,x,y, currColor,flag);
    currScene.addGeometry(cu); 
    }
  }
   //let objFile = document.getElementById("file"); 
  /*console.log("objFile: "+objFile+"\n"); 
  console.log("objFile.value"+objFile.value+"\n"); 
  console.log("objFile.innerHTML "+objFile.innerHTML+"\n"); 
  console.log("objFile.innnerText: "+objFile.innerText+"\n"); 
  console.log("objFile.id: "+objFile.id+"\n"); 
  console.log("objFile.toString: "+objFile.toString()+"\n"); 
  console.log("objFile.name: "+objFile.name+"\n"); */
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
  // Clears the canvas and empties the colour buffer 
  gl.clearColor(0, 0, 0, 1);
  gl.clear(gl.COLOR_BUFFER_BIT); 
  //calls clear on the current scene
  currScene.render(); 
}


/**
 * Clears the HTML canvas.
 * clearCanvas removes all elements from the scene's geometry array
 * and then calls render to illustrate the newly blank canvas
 */
function clearCanvas() { 
  //Removes all geometric objects from the scene then immediately rendrs 
  currScene.clearGeometry(); 
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
  pScale = size; //sets the point scale to the argument and renders 
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
  render(); 
}