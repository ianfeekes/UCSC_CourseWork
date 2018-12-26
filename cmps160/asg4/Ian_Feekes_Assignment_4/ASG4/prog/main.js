/*We want to define these variables as global so that the eventFunctions
 *have access to them and so that they don't need to be re-initialized on 
 *the stack or passed in as arguments at later times when many functions 
 *will need to access them*/ 
let gl;                   //It's nice to be able to access gl rather than find it every time you need to tell it to draw 
let a_Position;           //Everything drawn will have its own matrix to manipulate gl drawing a position 
let a_Color;              //Lots of shapes will be using this for vertex colors
let u_Sampler;            //Texture shader parameter 
var u_ModelMatrix;        //This lets us transform shapes and easily tell gl to move/animate things 
let p_size;               //Point size is ocassionally used 
var canvas;               //Its nice to let event functions access the canvas without any problems 

/**
 * Function called when the webpage loads.
 */
function main() {
  /*This line invokes query selector which essentially searches the html document for
    any tags matching canvas, and once it does, it will store the specifications into 
    the variable canvas*/  
  canvas = document.getElementById('can'); 
  if (!canvas) { 
    console.log('Failed to retrieve the <canvas> element');
    return false; 
  } 
  /*gl will hold the rendering context from the canvas*/
  gl = getWebGLContext(canvas); 
  if(!gl)
  {
    console.log('Failed to retreive the <gl> element'); 
    return; 
  }

  /*Initializes the shaders and makes sure that they exist*/ 
  let prog = createShader(gl, ASSIGN4_VSHADER, ASSIGN4_FSHADER); 
  if(!prog)
  {
    console.log('Failed to initialize shaders.'); 
    return; 
  }
  useShader(gl,prog); 
  // Get the storage location of a_Position
  a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return;
  }
  // Get the storage location of a_Color 
  a_Color = gl.getAttribLocation(gl.program, 'a_Color'); 
  if(a_Color<0)
  {
    console.log('Failed to get the storage location of a_Color'); 
    return; 
  }
  //Initialize the matrix 
  u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix'); 
  //initialize point size 
  p_size = gl.getUniformLocation(gl.program, 'p_size'); 
  if (p_size<0)
  {
    console.log('Failed to get the storage location of p_size'); 
    return
  }  
  u_Sampler = gl.getUniformLocation(gl.program, 'u_Sampler'); 
  if(u_Sampler<0)
  {
    console.log('Failed to get the storage location of u_Sampler'); 
    return; 
  }

  initEventHandelers();
  //Sets the color for the "clear" command as full black
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT);
  /*This is the event listener. If it senses the mouse is pressed it will start up a function to make it so 
   *that mouse movement behaves as the click method. If the mouse is released, the movement function is set 
   *to null to allow for dragging*/ 
  canvas.onmousedown = function(ev){click(ev);
                                    canvas.onmousemove = function(ev){click(ev);};
                                   }; 
  canvas.onmouseup = function(ev){canvas.onmousemove = function(ev){null; };};  

  tick(); 
}
