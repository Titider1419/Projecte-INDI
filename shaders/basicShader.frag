#version 330 core



in vec4 fvertSCO;
in vec3 fnormSCO;
in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

uniform vec3 posFocus;
uniform vec3 colorFocus;
uniform vec3 llumAmbient;
uniform mat4 view;

uniform bool modeNocturn;
uniform vec3 posLlanterna;
uniform vec3 dirLlanterna;
uniform vec3 colorLlanterna;

uniform vec3 posFantasma;
uniform vec3 colorFantasma;


uniform vec3 posMonedes[10];
uniform vec3 dirMonedes[10];
uniform int  numMonedes;
uniform sampler2D text;
uniform int textActive;
in vec2 fUV;

out vec4 FragColor;

vec3 Ambient() {
    return llumAmbient * fmatamb;
}

vec3 Difus(vec3 NormSCO, vec3 L, vec3 colFocus, vec3 matDiff) {
    vec3 colRes = vec3(0);
    if (dot(L, NormSCO) > 0)
        colRes = colFocus * matDiff * dot(L, NormSCO);
    return colRes;
}

vec3 Especular(vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) {
    vec3 colRes = vec3(0);
    if ((dot(NormSCO, L) < 0) || (fmatshin == 0))
        return colRes;
    vec3 R = reflect(-L, NormSCO);
    vec3 V = normalize(-vertSCO.xyz);
    if (dot(R, V) < 0)
        return colRes;
    float shine = pow(max(0.0, dot(R, V)), fmatshin);
    return (fmatspec * colFocus * shine);
}

float sigmoid(float dist) {
    return 1.0 / (1.0 + exp(5.0 * (dist - 4.0)));
}

void main() {
    vec3 matDiff = (textActive == 1) ? texture(text, fUV).rgb : fmatdiff;
    vec3 color = Ambient();
    if (!modeNocturn) {
        vec3 posFocusSCO = vec3(view * vec4(posFocus, 1.0));
        vec3 L = normalize(posFocusSCO - fvertSCO.xyz);
        color += Difus(fnormSCO, L, colorFocus, matDiff) + Especular(fnormSCO, L, fvertSCO, colorFocus);
    } else {
        vec3 posLlantSCO  = vec3(view * vec4(posLlanterna, 1.0));
        vec3 dirLlantSCO  = normalize(mat3(view) * dirLlanterna);
        vec3 L            = normalize(posLlantSCO - fvertSCO.xyz);
        float cosFragment = dot(-L, dirLlantSCO);
        if (cosFragment > cos(radians(30.0))) {
            float dist = length(posLlantSCO - fvertSCO.xyz);
            float atenuacio  = 1.0 / (1.0 + 0.5*dist + 0.3*dist*dist);
            color += atenuacio * (Difus(fnormSCO, L, colorLlanterna, matDiff) + Especular(fnormSCO, L, fvertSCO, colorLlanterna));
        }
        vec3 posFantasmaSCO = vec3(view * vec4(posFantasma, 1.0));
        vec3 Lf             = normalize(posFantasmaSCO - fvertSCO.xyz);
        float distF         = length(posFantasmaSCO - fvertSCO.xyz);
        float atenuacioF    = 1.0 / (1.0 + 0.5*distF + 0.3*distF*distF);
        color += atenuacioF * (Difus(fnormSCO, Lf, colorFantasma, matDiff) + Especular(fnormSCO, Lf, fvertSCO, colorFantasma));

        for (int k = 0; k < numMonedes; k++) {
            vec3 posMonSCO = vec3(view * vec4(posMonedes[k], 1.0));
            vec3 dirMonSCO = normalize(mat3(view) * dirMonedes[k]);

            vec3  L    = normalize(posMonSCO - fvertSCO.xyz);
            float dist = length(posMonSCO - fvertSCO.xyz);

            float atDist = sigmoid(dist);
            if (atDist < 0.01) continue;

            float spotFactor = max(0.0, dot(dirMonSCO, L));

            vec3 colorMon = vec3(1.0, 0.85, 0.2);
            color += atDist * spotFactor * (Difus(fnormSCO, L, colorMon, matDiff) + Especular(fnormSCO, L, fvertSCO, colorMon));
        }
    }

    FragColor = vec4(color, 1.0);
}
