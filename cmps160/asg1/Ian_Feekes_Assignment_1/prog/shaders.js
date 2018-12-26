/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *shaders.js
 *
 *Initializes the shaders
*/ 

// Basic Vertex Shader that receives position and size for each vertex (point).
var ASSIGN1_VSHADER =
   'attribute vec4 a_Position;\n' +
  'uniform float p_size;\n'+ //p_size is the float used to bind the value of point size
  'void main() {\n' +
  '  gl_Position = a_Position;\n' +
  '  gl_PointSize = p_size;\n' + //set the gl_PointSize to p_size 
  '}\n';

// Basic Fragment Shader that receives a single one color (point).
var ASSIGN1_FSHADER =
  'precision mediump float;\n' +
  'uniform vec4 u_FragColor;\n' + 
  'void main() {\n' +
  '  gl_FragColor = u_FragColor;\n' +
  '}\n';
