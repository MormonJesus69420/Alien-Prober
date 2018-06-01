uniform sampler2D _colour_map;

varying vec4 _texture_coordinates;

void main()
{
    gl_FragColor = texture2D(_colour_map, _texture_coordinates.xy);
}
