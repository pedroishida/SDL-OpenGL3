#version 130

attribute vec3 in_position; //attribute index 0
attribute vec4 in_color; //attribute index 1
 
out vec4 ex_color;

void main(void) {
    gl_Position = vec4(in_position[0], in_position[1], in_position[2], 1.0);
 
    ex_color = in_color;
}
