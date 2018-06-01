varying vec3 _normal;

void main()
{
    _normal = gl_NormalMatrix * gl_Normal;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    gl_FrontColor = gl_Color;
} 
