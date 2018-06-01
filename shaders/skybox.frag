uniform samplerCube _skybox;

varying vec3 _texture_coordinates;

void main(void)
{
    gl_FragColor = textureCube(_skybox, _texture_coordinates);
}
