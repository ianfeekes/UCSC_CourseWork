/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps160 asg4
 *
 *glsFunctions.js
 *contains sendUniformFloatToGLSL, Mat and Vec methods*/ 

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
  //console.log("logging val in send2DTextureToGLSL...\n");
  //console.log(val); 

  var uName = gl.getUniformLocation(gl.program, uniformName);
  if (uName < 0) {
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
 // gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR); 
  //l.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, );
  gl.uniform1i(u_Sampler, textureUnit); 
  // Recomendations: Within this funciton, you should:
  //    1. Gather your uniform location CHECK
  //    2. Determine the exture unit you will be using (gl.TEXTURE"N")
  //    3. Activate your texture unit using gl.activeTexture
  //    4. Bind your texture using gl.bindTexture
  //    5. Send the texture unit (textureUnit not the one you found) to your
  //       uniform location.
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
  let image = new Image();

  image.onload = function() {
    var texture = gl.createTexture();
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1); // Flip the image's y axis
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, magParam);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, minParam);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, wrapSParam);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, wrapTParam);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
    //console.log("in create2DTexture logging texture value...\n"); 
    //console.log(texture); 
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
  //Get the uniform and check its location 
  var uName = gl.getUniformLocation(gl.program, uniformName);
  if (uName < 0) {
    console.log('Failed to get the storage location of the attribute being sent to glsl\n');
    return -1;
  }
  //send the matrix to glsl 
  gl.uniformMatrix4fv(uName, false, val.elements); 
}

function sendAttributeBufferToGLSL(data, dataCount, attribName, stride = 0, offset = 0) {
 // console.log("in sendAttributeBufferToGLSL. Printing data...\n");
  //console.log(data); 
  let attribute = gl.getAttribLocation(gl.program, attribName);
  if (attribute < 0) {
    console.log('Failed to get the storage location of '+attribName)
    return
  }
  let vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object ')
    return
  }
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  let FSIZE = data.BYTES_PER_ELEMENT;
  gl.vertexAttribPointer(attribute, dataCount, gl.FLOAT, false, FSIZE*stride, FSIZE*offset);
  gl.enableVertexAttribArray(attribute);
}

function sendIndicesBufferToGLSL(indices) {
  const indexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
}


/**
 * Draws the current buffer loaded. Buffer was loaded by sendAttributeBufferToGLSL.
 *
 * @param {Integer} pointCount The amount of vertices being drawn from the buffer.
 *
 * Simply connects the dots, with pointCount specifying how many dots to connect 
 */
function tellGLSLToDrawCurrentBuffer(pointCount) { 
 gl.drawArrays(gl.TRIANGLES, 0, pointCount); 
}

/**specified
 * Sends a float value to the  uniform variable within GLSL shaders.
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