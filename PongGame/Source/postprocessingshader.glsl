std::string_view fragmentShader = R"(

#version 130

uniform sampler2D texture;
uniform float time;        

vec2 uv_curve(vec2 uv);

void main() 
{
    float PI = 3.14159;
    float redOffset   =  0.005;
    float greenOffset =  0.002;
    float blueOffset  = -0.002;
    
    vec2 texSize  = textureSize(texture, 0).xy;
    vec2 texCoord = gl_TexCoord[0].xy / texSize;
    
    vec2 direction = texCoord - vec2(0.5f,0.5f);
    
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    
    color.r = texture2D(texture, gl_TexCoord[0].xy + (direction * vec2(redOffset  ))).r;
    color.g = texture2D(texture, gl_TexCoord[0].xy + (direction * vec2(greenOffset))).g;
    color.b = texture2D(texture, gl_TexCoord[0].xy + (direction * vec2(blueOffset ))).b;            
    
    float s = sin(uv_curve(gl_TexCoord[0].xy).y * 20.0f * PI * (time + 20.0f));
    s = (s * 0.5 + 0.5) * 0.9 + 0.1;
    vec4 scan_line = vec4(vec3(pow(s, 0.25)), 1.0);

    gl_FragColor = color * scan_line;

}


vec2 uv_curve(vec2 uv)
{   
    uv = (uv - 0.5) * 2.0;
    
    uv.x *= 1.0 + pow(abs(uv.y) / 3.0, 2.0);
    uv.y *= 1.0 + pow(abs(uv.x) / 3.0, 2.0);
    
    uv /= 1.2;
    
    uv = (uv/2.0) + 0.5;
    return uv;
}
)";