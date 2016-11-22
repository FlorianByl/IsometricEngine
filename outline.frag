uniform float border_width;
uniform float aspect;  // ratio of width to height
varying vec2 texCoord;

void main() {
   float maxX = 1.0 - border_width;
   float minX = border_width;
   float maxY = maxX / aspect;
   float minY = minX / aspect;

   if (texCoord.x < maxX && texCoord.x > minX &&
       texCoord.y < maxY && texCoord.y > minY) {
     gl_FragColor = vec4(0.5, 0.2, 1.0, 1.0);
   } else {
     gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
   }
}
