// Vertex shader used by 'Sprite'
#version 330 core

// We can store both position and texture-coordinate data in a single 'vec4' variable
// Because both position and texture coordinates contain two floats, we can combine them
// into a single vertex attribute. 
layout (location = 0) in vec4 vertex; 

// To be passed onto the fragment shader
out vec2 TexCoords; 

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

  TexCoords = vertex.zw;  
  gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);

}