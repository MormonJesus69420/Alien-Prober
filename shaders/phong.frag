varying vec3 _normal;

void main ()
{
    vec3 _light_vector = vec3(gl_LightSource[0].position);
    vec3 _diffuse_material = gl_FrontLightProduct[0].diffuse.xyz;
    vec3 _specular_material = gl_FrontLightProduct[0].specular.xyz;

    // Calculate vectors
    vec3 _normal_vector = normalize(_normal);
    vec3 _eye_vector = vec3(0.0, 0.0, 1.0);
    vec3 _half_vector = normalize(_light_vector + _eye_vector);

    // Calculate diffuse component
    vec3 _diffuse = vec3(max(0.5*dot(_normal_vector, _light_vector), 0.5)) * _diffuse_material;

    // Calculate specular component
    //vec3 _specular = vec3(max(dot(_normal_vector, _half_vector), 0.0));
    //_specular = pow(_specular.x, 32.0) * _specular_material;

    // Combine diffuse and specular contributions and output final vertex color
    gl_FragColor.rgb = _diffuse; //+ _specular;
} 
