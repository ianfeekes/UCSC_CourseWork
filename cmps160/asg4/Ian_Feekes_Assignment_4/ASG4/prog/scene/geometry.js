/**
 * Specifies a geometric object.
 *
 * @author Ian Feekes
 * @this {Geometry}
 */
class Geometry {
  /**
   * Constructor for Geometry.
   *
   * @constructor
   */
  constructor() {
    /*Currentlly begins with empty vertices and an empty colour*/ 
    this.vertices = []; // Vertex objects. Each vertex has x-y-z.
    this.color = [];    // The color of your geometric object
    this.n = 0;         // The number of vertices of the object. 
    this.modelMatrix = new Matrix4(); //Initialize the model matrix
    this.shader=null;   // shading program you will be using to shade this geometry
    this.currentAngle=0.0;
    this.vecX=0;
    this.vecY=0; 
    this.SIZE_STEP = 0;
    this.shader=null;   //We will have to start using multipl shaders for textures
    this.data = [];
    this.uvVals = []; 
    this.color_data = []; 
    if(this instanceof TiltedCube)
    {
       if(this instanceof CheckerCube || this instanceof MultiTextureCube)
        {
          //console.log("creating texture shaders for checkered cube \n"); 
          this.shader = createShader(gl, ASSIGN4_VSHADER_TEXTURE, ASSIGN4_FSHADER_TEXTURE);
          //useShader(gl, this.shader); 
        }
        else this.shader = createShader(gl, ASSIGN4_VSHADER, ASSIGN4_FSHADER); 
    }
    else
    {
       this.shader = createShader(gl, ASSIGN4_VSHADER, ASSIGN4_FSHADER); 
      //useShader(gl, this.shader); 
    }
    useShader(gl, this.shader); 
  }

  //Sets color 
  setColor(c)
  {
    //Do this for every vertex still 
    for(let i=0;i<this.n;i++)
    {
      /*this.color.push(c[0]);
      this.color.push(c[1]);
      this.color.push(c[2]); */ 
      this.vertices[i].setColor(c[0],c[1],c[2]); 
    } 
    //console.log(this.color+"\n"); 
  }

  /*Iterates through the number of vertices each object has and generates a 
   *random r, g, b value for them*/ 
  setRandomColor()
  {
    for(let i=0;i<this.n;i++)
    {
      //r g and b are all values between 0-255 inclusive 
      let r = (Math.floor(Math.random()*Math.floor(256)))/256;
      let g = (Math.floor(Math.random()*Math.floor(256)))/256;
      let b = (Math.floor(Math.random()*Math.floor(256)))/256;  
      this.vertices[i].setColor(r,g,b); 
    }
    //console.log(this.color+"\n"); 
  }

  /*This is done here rather than in setArrayValues because checkered cube initializes its
    super constructor, which would involve null values*/ 
  setUVArray()
  {
    for(let i=0;i<this.vertices.length;i++)
    {
      this.uvVals.push(this.vertices[i].uv[0], this.vertices[i].uv[1]); 
    }
    this.uvVals = new Float32Array(this.uvVals);
  }

  setArrayValues()
  {
    for(var i=0;i<this.vertices.length;i++)
    {
      this.data.push(this.vertices[i].points[0],this.vertices[i].points[1],this.vertices[i].points[2] ); 
      this.color_data.push(this.vertices[i].color[0], this.vertices[i].color[1],this.vertices[i].color[2]); 
    }
    //console.log("In setArrayValues logging  vertices uv data before initializing as float32\n"); 
    //console.log(this.vertices);  
    this.data = new Float32Array(this.data);
    this.color_data = new Float32Array(this.color_data);
  }

  /**
   * Renders this Geometry within your webGL scene.
   * Sets color, translates vertices, sets vertices, and draws 
   */
  render() {
    useShader(gl, this.shader); 
    if(this instanceof TiltedCube)
      {
        if(this instanceof CheckerCube || this instanceof MultiTextureCube)
        {
          //this.shader = createShader(gl, ASSIGN4_VSHADER_TEXTURE, ASSIGN4_FSHADER_TEXTURE);
          //useShader(gl, this.shader); 
          send2DTextureToGLSL(this.texture, 0, 'u_Sampler')
          //console.log(this.uv_data); 
          sendAttributeBufferToGLSL(this.uvVals, 2, 'a_TexCoord', 2, 0); 
        }
        else
        {
          //useShader(gl, this.shader); 
          //console.log("tilted cube so sending color buffer...\n"); 
          sendAttributeBufferToGLSL(this.color_data, 3, 'a_Color');
        }
        sendAttributeBufferToGLSL(this.data, 3, 'a_Position'); 
        sendUniformMatToGLSL(this.modelMatrix, 'u_ModelMatrix');
        //tellGLSLToDrawCurrentBuffer(36);
         sendIndicesBufferToGLSL(this.indices)
         gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_SHORT, 0);
      }
    /*This case applies to all non-cube shapes where we don't have to deal
      with the possibility of applying textures or working with index buffers*/ 
    else 
      {
        sendAttributeBufferToGLSL(this.color_data, 3, 'a_Color');
        sendAttributeBufferToGLSL(this.data, 3, 'a_Position'); 
        //tells glsl to apply this shapes transformation matrix
        sendUniformMatToGLSL(this.modelMatrix, 'u_ModelMatrix');
        //tells glsl to apply this shapes vertices  
        tellGLSLToDrawCurrentBuffer(this.n);
      }
  }

  /**
   * Responsible for updating the geometry's modelMatrix for animation.
   * Does nothing for non-animating geometry.
   *
   * The super method does nothing. Each shape has their own unique update
   * animation method
   */
  updateAnimation() {
    return;
  }

}
