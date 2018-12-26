/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *shaders.js
 *cmps160 asg2
 *
 *Initializes the shaders
 */ 

// Basic Vertex Shader that receives position and size for each vertex (point).
var ASSIGN1_VSHADER =
   'attribute vec4 a_Position;\n' +
  //  'uniform mat4 u_xformMatrix;\n' + //This is the transformation matrix for the shapes
  'void main() {\n' +
  '  gl_Position = a_Position;\n' + //be sure to include the linear trans
  '}\n';

// Basic Fragment Shader that receives a single one color (point).
var ASSIGN1_FSHADER =
  'precision mediump float;\n' +
  'uniform vec4 u_FragColor;\n' + 
  'void main() {\n' +
 // 'gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' + 
  '  gl_FragColor = u_FragColor;\n' +
  '}\n';
