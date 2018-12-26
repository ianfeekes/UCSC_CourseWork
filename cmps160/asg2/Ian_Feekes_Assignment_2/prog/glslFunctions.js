/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps160 asg2
 *
 *glsFunctions.js
 *contains sendUniformFloatToGLSL and Vec methods*/ 

/**
 * Sends a float value to the specified uniform variable within GLSL shaders.
 * Prints an error message if unsuccessful.
 *
 * @param {float} val The float value being passed to uniform variable
 * @param {String} uniformName The name of the uniform variable
 *
 * Sends the float to the specified glsl uniform
 */
function sendUniformFloatToGLSL(val, uniformName) {
  gl.uniform1f(uniformName, val);
}

/**
 * Sends an JavaSript array (vector) to the specified uniform variable within
 * GLSL shaders. Array can be of length 2-4.
 *
 * @param {Array} val Array (vector) being passed to uniform variable
 * @param {String} uniformName The name of the uniform variable
 *
 * Simply sends the value(assumed to be a 4 entry vector) to the uniform name. 
 * This function is called each time a shape needs to have its colour set. 
 * This function is also called each time a corona gets its lime ;) 
 */
function sendUniformVec4ToGLSL(val, uniformName) {
  gl.uniform4f(uniformName, val[0], val[1], val[2], val[3]); 
}


/* Sends data to an attribute variable using a buffer
 * This is one of the most challenging functions to properly impliment
 * throughout this programming assignment. It essentially just throws
 * data into glsl in preparation for rendering. 
 */ 
function sendAttributeBufferToGLSL(data, dataCount, attribName) {
  //contain data within vertices for easier processing
  var vertices = new Float32Array(data); 
  // Create a buffer object
  var vertexBuffer = gl.createBuffer();
  //Checks to make sure the buffer has been initialized
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }
  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  // Write date into the buffer object
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
  //gets the attribute ane checks to see if it's valid
  var aName = gl.getAttribLocation(gl.program, attribName);
  if (aName < 0) {
    console.log('Failed to get the storage location of the attribute being sent to glsl\n');
    return -1;
  }
  //Points the attribute to the pointer
  gl.vertexAttribPointer(aName, 2, gl.FLOAT, false, 0, 0);
  // Enable the assignment to the attribute variable
  gl.enableVertexAttribArray(aName);
  // returns the data count passed in
  return dataCount; 
}

/**
 * Draws the current buffer loaded. Buffer was loaded by sendAttributeBufferToGLSL.
 *
 * @param {Integer} pointCount The amount of vertices being drawn from the buffer.
 *
 * Simply connects the dots, with pointCount specifying how many dots to connect 
 */
function tellGLSLToDrawCurrentBuffer(pointCount) {
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, pointCount); 
}
