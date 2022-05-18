#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ex_N; 

in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Normal_cameraspace;

in vec3 EyeDirection_cameraspace2;
in vec3 LightDirection_cameraspace2;
in vec3 Normal_cameraspace2;

in vec3 EyeDirection_cameraspace3;
in vec3 LightDirection_cameraspace3;
in vec3 Normal_cameraspace3;

in vec3 EyeDirection_cameraspace4;
in vec3 LightDirection_cameraspace4;
in vec3 Normal_cameraspace4;

uniform sampler2D texture_diffuse1;

uniform vec4 LightColor;
uniform vec4 LightPower;
uniform int  alphaIndex;
uniform float distance;

uniform vec4 LightColor2;
uniform vec4 LightPower2;
uniform int  alphaIndex2;
uniform float distance2;

uniform vec4 LightColor3;
uniform vec4 LightPower3;
uniform int  alphaIndex3;
uniform float distance3;

uniform vec4 LightColor4;
uniform vec4 LightPower4;
uniform int  alphaIndex4;
uniform float distance4;

uniform vec4 MaterialAmbientColor;
uniform vec4 MaterialDiffuseColor;
uniform vec4 MaterialSpecularColor;
uniform float transparency;

void main()
{    

    // Cálculo de componente difusa
    vec3 n = normalize( Normal_cameraspace );
    vec3 l = normalize( LightDirection_cameraspace );

    vec3 n2 = normalize( Normal_cameraspace2 );
    vec3 l2 = normalize( LightDirection_cameraspace2 );

    vec3 n3 = normalize( Normal_cameraspace3 );
    vec3 l3 = normalize( LightDirection_cameraspace3 );

    vec3 n4 = normalize( Normal_cameraspace4 );
    vec3 l4 = normalize( LightDirection_cameraspace4 );

    vec4 texel = texture(texture_diffuse1, TexCoords);
    
    float cosTheta = clamp( dot( n,l ), 0,1 );
    float cosTheta2 = clamp( dot( n2,l2 ), 0,1 );
    float cosTheta3 = clamp( dot( n3,l3 ), 0,1 );
    float cosTheta4 = clamp( dot( n4,l4 ), 0,1 );

    // Cálculo de componente difusa
    vec4 MaterialAmbColor = MaterialAmbientColor * LightColor;
    vec4 MaterialAmbColor2 = MaterialAmbientColor * LightColor2;
    vec4 MaterialAmbColor3 = MaterialAmbientColor * LightColor3;
    vec4 MaterialAmbColor4 = MaterialAmbientColor * LightColor4;

    // Cálculo de componente especular
    vec3 E = normalize(EyeDirection_cameraspace);
    vec3 R = reflect(-l,n);

    vec3 E2 = normalize(EyeDirection_cameraspace2);
    vec3 R2 = reflect(-l2,n2);

    vec3 E3 = normalize(EyeDirection_cameraspace3);
    vec3 R3= reflect(-l3,n3);

    vec3 E4 = normalize(EyeDirection_cameraspace4);
    vec3 R4 = reflect(-l4,n4);
 
    float cosAlpha = clamp( dot( E,R ), 0,1 );
    float cosAlpha2 = clamp( dot( E2,R2 ), 0,1 );
    float cosAlpha3 = clamp( dot( E3,R3 ), 0,1 );
    float cosAlpha4 = clamp( dot( E4,R4 ), 0,1 );

    vec4 ex_color = MaterialAmbColor +
                    MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
                    MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,alphaIndex) / (distance*distance) +
                    MaterialAmbColor2 +
                    MaterialDiffuseColor * LightColor2 * LightPower2 * cosTheta2 / (distance2*distance2) +
                    MaterialDiffuseColor * LightColor2 * LightPower2 * pow(cosAlpha2,alphaIndex2) / (distance2*distance2);
                    MaterialAmbColor3 +
                    MaterialDiffuseColor * LightColor3 * LightPower3 * cosTheta3 / (distance3*distance3) +
                    MaterialSpecularColor * LightColor3 * LightPower3 * pow(cosAlpha3,alphaIndex3) / (distance3*distance3) +
                    MaterialAmbColor4 +
                    MaterialDiffuseColor * LightColor4 * LightPower4 * cosTheta4 / (distance4*distance4) +
                    MaterialDiffuseColor * LightColor4 * LightPower4 * pow(cosAlpha2,alphaIndex4) / (distance4*distance4);
    ex_color.a = transparency;

    FragColor = texel * ex_color;
}