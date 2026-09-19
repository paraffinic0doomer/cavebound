#version 330 core

in vec3 color;

uniform float alpha; // 1.0 = opaque, < 1.0 = translucent (needs blending enabled)

out vec4 FragColor;

void main()
{
   FragColor = vec4(color, alpha);
}
