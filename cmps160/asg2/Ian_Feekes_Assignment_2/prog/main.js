/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *cmps160
 *asg2
 *main.js
 *Function called immediately when the webpage loads. This is largely
 *responsible for initializing the shader programs, initializing the
 *event handlers, and for implementing the mouse event listener*/ 


/*We want to define these variables as global so that the eventFunctions
 *have access to them and so that they don't need to be re-initialized on 
 *the stack or passed in as arguments at later times when many functions 
 *will need to access them*/ 
let gl; 
let a_Position; 
let u_FragColor;
var u_xformMatrix; 
let p_size; 
var canvas;    
 
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
  if(!initShaders(gl, ASSIGN1_VSHADER, ASSIGN1_FSHADER))
  {
    console.log('Failed to initialize shaders.'); 
    return; 
  }
  // Get the storage location of a_Position
  a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return;
  }
  //initialize colours
  u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
  if (!u_FragColor) {
    console.log('Failed to get the storage location of u_FragColor');
    return;
  }
  //initialize point size 
  p_size = gl.getUniformLocation(gl.program, 'p_size'); 
  if (p_size<0)
  {
    console.log('Failed to get the storage location of p_size'); 
    return
  }  
  initEventHandelers();
  /*Initialize our transofmation matrix*/  
   
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
    
}

  
