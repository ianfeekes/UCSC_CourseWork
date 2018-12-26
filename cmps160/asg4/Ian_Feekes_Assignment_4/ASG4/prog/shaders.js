/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *shaders.js
 *cmps160 asg4
 *
 *Initializes the shaders
 */  

// Basic Vertex Shader that receives position and size for each vertex (point).
var ASSIGN4_VSHADER =
   'attribute vec4 a_Position;\n' +
   'attribute vec4 a_Color;\n' +        //This allows us to start dynamically allocating colors 
  // 'attribute vec2 a_TexCoord;\n'+      //THESE TWO LINES ARE ADDED  
   //'varying vec2 v_TexCoord;\n'+      
   'uniform mat4 u_ModelMatrix;\n'+     //This is the transformation matrix for the shapes 
   'varying vec4 v_Color;\n'+           //Allows us to shade vertex colours 
  'void main() {\n' +
  //The next line is very important for u_ModelMatrix for translation 
  '  gl_Position = u_ModelMatrix * a_Position;\n' + //be sure to include the linear trans
  //'  v_TexCoord = a_TexCoord;\n'+       //THIS IS NEW 
  '  v_Color = a_Color;\n'+
  '}\n';

// Basic Fragment Shader that receives a single one color (point).
var ASSIGN4_FSHADER =
  '#ifdef GL_ES\n'+                     //NOT SURE WHAT THIS DOES: MAY NEED MODIFICATION
  'precision mediump float;\n' +
 // 'uniform sampler2D u_Sampler;\n' +    //THIS COMES FROM TEXTURE PROGRAM
 // 'varying vec2 v_TexCoord;\n'+         //THIS ALSO COMES FROM TEXTURE PROGRAM
  '#endif\n'+                           //STILL NOT SURE ABOUT THE NECESSITY OF THIS DEFINITION
  'varying vec4 v_Color;\n' + 
  'void main() {\n' +
 // 'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' + 
//  '  gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n'+ //ADDED 
  '  gl_FragColor = v_Color;\n' +       //THIS IS DIFFERENT REMEMBER THIS 
  '}\n';

  var ASSIGN4_VSHADER_TEXTURE =
`uniform mat4 u_ModelMatrix;\n` +
`attribute vec4 a_Position;\n` +
'attribute vec2 a_TexCoord;\n' +
'varying vec2 v_TexCoord;\n' +
  `void main() {\n` +
  `   gl_Position = u_ModelMatrix * a_Position;\n` +
  '   v_TexCoord = a_TexCoord;\n' +
  `}\n`;

 var ASSIGN4_FSHADER_TEXTURE =
  `precision mediump float;\n` +
  'uniform sampler2D u_Sampler;\n' +
  'varying vec2 v_TexCoord;\n' +
  `void main() {\n` +
  ' gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n' +
  `}\n`;

 /* var ASSIGN4_VSHADER_TEXTURE = 
  'uniform mat4 u_ModelMatrix;\n'+
  'attribute vec4 a_Position;\n'+ 
  'attribute vec2 a_TexCoord;\n'+
  'varying vec2 v_TexCoord;\n'+
  'void main(){\n'+
  '   gl_Position = u_ModelMatrix * a_Position;\n'+
  '   v_TexCoord = a_TexCoord\n'+
  '}\n';

  var ASSIGN4_FSHADER_TEXTURE = 
  'precision mediump float;\n'+
  'uniform sampler2D u_Sampler;\n'+
  'varying vec2 v_TexCoord;\n'+
  'void main() {\n'+
  '   gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n'+
  '}\n'; */ 
  