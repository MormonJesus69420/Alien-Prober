uniform samplerCube _colour_map;
uniform float _time;

varying vec3 _normal;
varying mat4 _view;
varying vec4 _eye;

// Reflection shader loosely based on:
// http://antongerdelan.net/opengl/cubemaps.html

void main(void)
{
    vec4 pos = gl_Vertex;

    _view = gl_ModelViewMatrix;

    _eye = gl_ModelViewMatrix * gl_Vertex;

    pos.y = -90.0 + sin(pos.z / 180.0) + cos(pos.x / 90.0);

    gl_Position = gl_ModelViewProjectionMatrix * pos;

    _normal = gl_NormalMatrix * gl_Normal;
}
