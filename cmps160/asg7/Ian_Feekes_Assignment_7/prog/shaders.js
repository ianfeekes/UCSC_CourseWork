/*Ian Feekes
  #1474914
  ifeekes@ucsc.edu
  Shaders.js
  Pretty much copied from the book*/ 

/*
var ASSIGN5_VSHADER =
  'attribute vec4 a_Position;\n' +
  'attribute vec4 a_Color;\n' +
  'attribute vec2 a_TexCoord;\n' + //added from old shaders 
  'attribute vec4 a_Normal;\n' +
 // 'uniform mat4 u_MvpMatrix;\n' +
  'uniform mat4 u_ModelMatrix;\n' +    // Model matrix
  'uniform mat4 u_NormalMatrix;\n' +   // Coordinate transformation matrix of the normal
  'uniform vec3 u_LightColor;\n' +     // Light color
  'uniform vec3 u_LightPosition;\n' +  // Position of the light source
  'uniform vec3 u_AmbientLight;\n' +   // Ambient light color
  'varying vec4 v_Color;\n' +
  'varying vec2 v_TexCoord;\n' +    //added from old shaders 
   'uniform mat4 u_ViewMatrix;\n' + //added from old shaders 
   'uniform float u_VSwitch;\n' +   //switch between textures 
  'uniform mat4 u_ProjMatrix;\n' +  //added from old shaders 
  'void main() {\n' +
 // '  gl_Position = u_MvpMatrix * a_Position;\n' +
  '  gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * a_Position;\n' +
     // Recalculate the normal based on the model matrix and make its length 1.
  '  vec3 normal = normalize(vec3(u_NormalMatrix * a_Normal));\n' +
     // Calculate world coordinate of vertex
  '  vec4 vertexPosition = u_ModelMatrix * a_Position;\n' +
     // Calculate the light direction and make it 1.0 in length
  '  vec3 lightDirection = normalize(u_LightPosition - vec3(vertexPosition));\n' +
     // Calculate the dot product of the normal and light direction
  '  float nDotL = max(dot(normal, lightDirection), 0.0);\n' +
     // Calculate the color due to diffuse reflection
  '  vec3 diffuse = u_LightColor * a_Color.rgb * nDotL;\n' +
     // Calculate the color due to ambient reflection
  '  vec3 ambient = u_AmbientLight * a_Color.rgb;\n' +
     // Add the surface colors due to diffuse reflection and ambient reflection
  '  v_Color = vec4(diffuse + ambient, a_Color.a);\n' + 
  '}\n'; */ 

  var ASSIGN5_FSHADER = 
  'precision mediump float;\n' +
  'varying vec4 v_Color;\n' +
  'uniform sampler2D u_Sampler;\n' +
  'varying vec2 v_TexCoord;\n' +
  'uniform float u_FSwitch;\n' +
  'void main() {\n' +
  '  if (u_FSwitch == 1.0) {\n' +
  '    gl_FragColor = v_Color;\n' +
  '  }\n' +
  '  if (u_FSwitch == 0.0) {\n' +
  '    gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n' +
  '  }\n' +
  '}\n';
 
 //Blindly copied and pasted lighting shaders from textbook 
 var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'attribute vec4 a_Color;\n' +
  'attribute vec2 a_TexCoord;\n' + //added from old shaders 
  'attribute vec4 a_Normal;\n' +
 // 'uniform mat4 u_MvpMatrix;\n' +
  'uniform mat4 u_ModelMatrix;\n' +    // Model matrix
  'uniform mat4 u_NormalMatrix;\n' +   // Coordinate transformation matrix of the normal
  'uniform vec3 u_LightColor;\n' +     // Light color
  'uniform vec3 u_LightPosition;\n' +  // Position of the light source
  'uniform vec3 u_AmbientLight;\n' +   // Ambient light color
  'varying vec4 v_Color;\n' +
  'varying vec2 v_TexCoord;\n' +    //added from old shaders 
   'uniform mat4 u_ViewMatrix;\n' + //added from old shaders 
   'uniform float u_VSwitch;\n' +   //switch between textures 
   'uniform float u_LightSwitch;\n'+
  'uniform mat4 u_ProjMatrix;\n' +  //added from old shaders 
  'void main() {\n' +
 // '  gl_Position = u_MvpMatrix * a_Position;\n' +
  '  gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * a_Position;\n' +
     // Recalculate the normal based on the model matrix and make its length 1.+
  '  vec3 normal = normalize(vec3(u_NormalMatrix * a_Normal));\n' +
     // Calculate world coordinate of vertex
  '  vec4 vertexPosition = u_ModelMatrix * a_Position;\n' +
     // Calculate the light direction and make it 1.0 in length
  '  vec3 lightDirection = normalize(u_LightPosition - vec3(vertexPosition));\n' +
     // Calculate the dot product of the normal and light direction
  '  float nDotL = max(dot(normal, lightDirection), 0.0);\n' +
     // Calculate the color due to diffuse reflection
  '  vec3 diffuse = u_LightColor * a_Color.rgb * nDotL;\n' +
     // Calculate the color due to ambient reflection
     //specular lighting calculations 
  '  float specular = 0.0;\n'+
  '  float d = max(dot(normal, lightDirection),0.0);\n'+
  '  if(d>0.0){\n'+
  '     vec3 reflectVec = reflect(-lightDirection, normal);\n'+
  '     vec3 viewVec = vec3(0,0,1.0);\n'+ 
  '     specular=pow(max(dot(reflectVec, viewVec), 0.0),120.0);}\n'+ 
     //if we are working the the phong lighting... 
  '  if(u_LightSwitch==1.0){\n' + 
    '  vec3 ambient = u_AmbientLight * a_Color.rgb;\n' +
    '  v_Color = vec4(ambient + diffuse, a_Color.a);}\n' + 
  '  else if(u_LightSwitch==0.0){\n' + 
    '  vec3 ambient = u_AmbientLight * a_Color.rgb;\n' +
    '  v_Color = vec4(ambient, a_Color.a);}\n '+
 // '  v_Color = vec4(diffuse, a_Color.a;}\n'+
  '}\n';


/*
   gl_Position = u_MvpMatrix * a_Position ;\n' +
  // Make the length of the normal 1.0
  '  vec3 normal = normalize(a_Normal.xyz);\n' +
  // Dot product of the light direction and the orientation of a surface (the normal)
  '  float nDotL = max(dot(u_LightDirection, normal), 0.0);\n' +
  // Calculate the color due to diffuse reflection
  '  vec3 diffuse = u_LightColor * a_Color.rgb * nDotL;\n' +
  '  v_Color = vec4(diffuse, a_Color.a);\n' + */ 

// Fragment shader program
/*var FSHADER_SOURCE = 
  '#ifdef GL_ES\n' +
  'precision mediump float;\n' +
  '#endif\n' +
  'varying vec4 v_Color;\n' +
  'void main() {\n' +
  '  gl_FragColor = v_Color;\n' +
  '}\n'; */ 
