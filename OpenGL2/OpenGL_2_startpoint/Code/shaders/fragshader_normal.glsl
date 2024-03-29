#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertNormal;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main() {
  vec3 mappedNormal = vertNormal;

  // This maps [-1,1] to [0,1]
  mappedNormal += 1;
  mappedNormal /= 2;

  // Add the alpha to the normalized normals
  fColor = vec4(normalize(mappedNormal), 1.0);
}
