#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in float ambientTerm, diffuseTerm, specularTerm;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example
uniform vec3 lightColor;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main() {
  vec3 materialColor = vec3(1, 1, 1);
  // AMBIENT TERM
  vec3 color = ambientTerm * materialColor;

  // DIFFUSE TERM
  color += diffuseTerm * materialColor * lightColor;

  // SPECULAR TERM
  color += specularTerm * lightColor;

  fColor = vec4(color, 1.0);
}