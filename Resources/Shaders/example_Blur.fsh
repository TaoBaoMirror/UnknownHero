#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 resolution;
uniform float XRadius;
uniform float sampleNumX;
uniform float YRadius;
uniform float sampleNumY;

vec4 blur(vec2);

void main(void)
{
	vec4 col = blur(v_texCoord);
	gl_FragColor = vec4(col);
}

vec4 blur(vec2 p)
{
    if (XRadius > 0.0 && sampleNumX > 1.0 && YRadius > 0.0 && sampleNumY > 1.0)
    {
        vec4 col = vec4(0);
        vec2 unit = 1.0 / resolution.xy;
        
        float xr = XRadius;
        float sampleStepX = xr / sampleNumX;
        
        float yr = YRadius;
        float sampleStepY = yr / sampleNumY;
        
        float count = 0.0;
        
        for(float x = -xr; x < xr; x += sampleStepX)
        {
            for(float y = -yr; y < yr; y += sampleStepY)
            {
                float weight = (xr - abs(x)) * (yr - abs(y));
                col += texture2D(CC_Texture0, p + vec2(x * unit.x, y * unit.y)) * weight;
                count += weight;
            }
        }
        
        return col / count;
    }
    
    return texture2D(CC_Texture0, p);
}
