#version 130
precision highp float;
 
in vec4 ex_color;
out vec4 frag_color;
 
void main(void) {
    frag_color = ex_color;
}
