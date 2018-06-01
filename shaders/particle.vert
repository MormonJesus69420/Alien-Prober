varying vec2 _texture;


void main(void)
{
    vec4 _position = gl_Vertex;
    _texture = gl_MultiTexCoord0.xy;
    gl_Position = gl_ModelViewProjectionMatrix * _position;
}
