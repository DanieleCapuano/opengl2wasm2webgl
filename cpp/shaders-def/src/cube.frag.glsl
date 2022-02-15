#version 300 es
precision mediump float;

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform float u_time;
uniform float u_opacity;

// positions and colors of lights
const int MAX_LIGHTS_N = 10;
uniform int u_nlights;
uniform vec4 u_lightposn[MAX_LIGHTS_N];
uniform vec4 u_lightcolor[MAX_LIGHTS_N];

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  
uniform vec4 u_ambient; 
uniform vec4 u_diffuse; 
uniform vec4 u_specular; 
uniform vec4 u_emission; 
uniform float u_shininess; 

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

vec4 computeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

        float nDotL = dot(normal, direction)  ;           
        vec4 lambert = (mydiffuse * lightcolor) * max (nDotL, 0.0) ;

        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = (myspecular * lightcolor) * pow (max(nDotH, 0.0), myshininess) ; 

        vec4 retval = lambert + phong ; 
        return retval ;            
}

vec4 manageLights(void) {
    const vec3 eyepos = vec3(0.,0.,0.) ; 
    
    // Dehomogenize current location 
    vec3 mypos = myvertex.xyz / myvertex.w ; 
    vec3 eyedirn = normalize(eyepos - mypos);
    vec4 retcolor = vec4(0., 0., 0., 0.);
    vec3 halfvec, direction;

    // Compute normal, needed for shading. 
    vec3 normal = normalize(mynormal) ; 
    int i;
    for (i=0; i< u_nlights; i++) {
        if (u_lightposn[i].w == 0.) {
            //directional light
            direction = normalize (u_lightposn[i].xyz) ; 
            halfvec = normalize (direction + eyedirn) ; 
            retcolor += computeLight(direction, u_lightcolor[i], normal, halfvec, u_diffuse, u_specular, u_shininess) ;
        }
        else {
            //point light
            vec3 position = u_lightposn[i].xyz / u_lightposn[i].w ; 

            // no attenuation 
            direction = normalize (position - mypos) ;
            halfvec = normalize (direction + eyedirn) ;  
            retcolor += computeLight(direction, u_lightcolor[i], normal, halfvec, u_diffuse, u_specular, u_shininess) ;
        }
    }

    return retcolor;
}

void main (void) {
    vec4 zero_one_color = u_ambient + u_emission + manageLights();
    fragColor = zero_one_color;
    
    // vec4(
    //     zero_one_color.r * 256.,
    //     zero_one_color.g * 256.,
    //     zero_one_color.b * 256.,
    //     zero_one_color.a
    // );
}
