uniform samplerCube _colour_map;

varying vec3 _normal;
varying mat4 _view;
varying vec4 _eye;

// Reflection shader loosely based on:
// http://antongerdelan.net/opengl/cubemaps.html

void main()
{
    vec3 eye_coordinates = vec3(_eye);
    eye_coordinates.x = -eye_coordinates.x;

    vec3 reflection = reflect(-normalize(eye_coordinates), _normal);

    gl_FragColor = textureCube(_colour_map, reflection);
}
