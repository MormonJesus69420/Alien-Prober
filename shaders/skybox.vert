varying vec3 _texture_coordinates;

void main(void)
{
    _texture_coordinates = gl_Vertex.xyz;
    gl_Position = ftransform();
}
