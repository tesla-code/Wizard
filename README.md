# Wizard

<h1> libs </h1> 
GLM <br />
GLFW <br />
GLEW <br />
ASSIMP <br />
stb image (header only lib to load images for textures) <br />

<h1> Features  </h1>
<ul>
  <li> Can load the deer model, but the textures won render for some reason. </li>
  <li> PerlinNoise Class that can generate noise, atm it just makes a 256 x 256 2D noise
this can be used to generate height maps, or elevate the terrain. but for now I dont use
the function but it works at least</li>
  
  <li> camera that can zoom with mouse wheel (mostly from the frame work off assigntment 2) </li>
  <li> Can read inn grey scale heigt maps and generate correct normalized values, but for some reason my program
  crashes if I load inn the big sample files so for now it's just using a small test file that is 15x 14 </li>
  <li> Im rendering a skobox </li>
  <li> Rendering terrain using GL_TRIANGLE_STRIP, so all it is just one drawcall but all of the verticies has to be calculated
      before i draw inn the map constructor</li>
  </ul>
<br/>
