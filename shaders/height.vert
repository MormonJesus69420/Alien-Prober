uniform sampler2D _height_map;

varying vec4 _texture_coordinates;

void main()
{
    vec4 _position = gl_Vertex;
    _texture_coordinates = gl_MultiTexCoord0;
    vec4 _texture_height = texture2D(_height_map, _texture_coordinates.xy);
    _position.y = _texture_height.y * 100.0 - 100.0;

    gl_Position = gl_ModelViewProjectionMatrix * _position;
}
