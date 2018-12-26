/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps160 asg5
 *glsl functions
 *
 *Contains all functions for interactions between object-oriented javascript
 *and glsl for canvas usage*/

  function initArrayBuffer (gl, attribute, data, num, type) {
  // Create a buffer object
  var buffer = gl.createBuffer();
  if (!buffer) {
    console.log('Failed to create the buffer object');
    return false;
  }
  // Write date into the buffer object
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  // Assign the buffer object to the attribute variable
  var a_attribute = gl.getAttribLocation(gl.program, attribute);
  if (a_attribute < 0) {
    console.log('Failed to get the storage location of ' + attribute);
    return false;
  }
  gl.vertexAttribPointer(a_attribute, num, type, false, 0, 0);
  // Enable the assignment of the buffer object to the attribute variable
  gl.enableVertexAttribArray(a_attribute);

  gl.bindBuffer(gl.ARRAY_BUFFER, null);

  return true;
}


/**
 * Sends a WebGL 2D texture object (created by load2DTexture) and sends it to
 * the shaders.
 *
 * @param val The WebGL 2D texture object being passed
 * @param {Number} textureUnit The texture unit (0 - 7) where the texture will reside
 * @param {String} uniformName The name of the uniform variable where the texture's
 * textureUnit location (0 - 7) will reside
 */
function send2DTextureToGLSL(val, textureUnit, uniformName) {
  var uName = gl.getUniformLocation(gl.program, uniformName);
  if(uName<0){
    console.log('Failed to get the storage location of the attribute being sent to glsl\n');
    return -1;
  }
  if(textureUnit==0) gl.activeTexture(gl.TEXTURE0);
  else if(textureUnit==1) gl.activeTexture(gl.TEXTURE1);
  else if(textureUnit==2) gl.activeTexture(gl.TEXTURE2); 
  else if(textureUnit==3) gl.activeTexture(gl.TEXTURE3); 
  else if(textureUnit==4) gl.activeTexture(gl.TEXTURE4); 
  else if(textureUnit==5) gl.activeTexture(gl.TEXTURE5); 
  else if(textureUnit==6) gl.activeTexture(gl.TEXTURE6);
  else if(textureUnit==7) gl.activeTexture(gl.TEXTURE7); 
  gl.bindTexture(gl.TEXTURE_2D, val);
  gl.uniform1i(uName, textureUnit);
}

/**
 * Creates a WebGl 2D texture object.
 *
 * @param imgPath A file path/data url containing the location of the texture image
 * @param magParam texParameteri for gl.TEXTURE_MAG_FILTER. Can be gl.NEAREST,
 * gl.LINEAR, etc.
 * @param minParam texParameteri for gl.TEXTURE_MIN_FILTER. Can be gl.NEAREST,
 * gl.LINEAR, etc.
 * @param wrapSParam texParameteri for gl.TEXTURE_WRAP_S. Can be gl.REPEAT,
 * gl. MIRRORED_REPEAT, or gl.CLAMP_TO_EDGE.
 * @param wrapTParam texParameteri for gl.TEXTURE_WRAP_S. Can be gl.REPEAT,
 * gl. MIRRORED_REPEAT, or gl.CLAMP_TO_EDGE.
 * @param callback A callback function which executes with the completed texture
 * object passed as a parameter.
 */
function create2DTexture(imgPath, magParam, minParam, wrapSParam, wrapTParam, callback) {
  var image = new Image();
  image.onlaod = function () {
  var texture = gl.createTexture();   // Create a texture object
  gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1); // Flip the image's y axis
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  gl.texParameteri(gl.TEXTURE_2D, gl.WRAP_S, gl.CLAMP_TO_EDGE);
  gl.texParameteri(gl.TEXTURE_2D, gl.WRAP_T, gl.CLAMP_TO_EDGE);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);

  callback(texture);
  }
  image.src = imgPath;
}

/**
 * Sends data to a uniform variable expecting a matrix value.
 *
 * @private
 * @param {Array} val Value being sent to uniform variable
 * @param {String} uniformName Name of the uniform variable recieving data
 */
 function sendUniformMatToGLSL(val, uniformName) {
  gl.uniformMatrix4fv(uniformName, false, val);
}

/**
 * Sends data to an attribute variable using a buffer.
 */
function sendAttributeBufferToGLSL(data, dataCount, attribName) {
  vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  gl.vertexAttribPointer(attribName, dataCount, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(attribName);
}

//Added helper function for cube objects 
function sendIndicesBufferToGLSL(indices) {
  const indexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
}

/**
 * Draws the current buffer loaded. Buffer was loaded by sendAttributeBufferToGLSL.
 *
 * @param {Integer} pointCount The amount of vertices being drawn from the buffer.
 */
function tellGLSLToDrawCurrentBuffer(renderMethod, pointCount) {
  gl.drawArrays(renderMethod, 0, pointCount);
}

/**
 * Sends a float value to the specified uniform variable within GLSL shaders.
 * Prints an error message if unsuccessful.
 */
function sendUniformFloatToGLSL(val, uniformName) {
  gl.uniform1f(uniformName, val);
}

/**
 * Sends an JavaSript array (vector) to the specified uniform variable within
 * GLSL shaders. Array can be of length 2-4.
 */
function sendUniformVec4ToGLSL(val, uniformName) {
  gl.uniform4f(uniformName, val[0], val[1], val[2], val[3]);
}


