<div align = "center">
  <img src = https://github.com/Rafapp/jellyengine/assets/38381290/d404dcfb-dd45-4afa-8a9f-42b7b3083d17 width = "650px" align = "center">
  <h1>A 3D Game Engine specialized for Soft Body Physics</h1>
</div>
<h2>Motivation</h2>
<div style="display: flex; align-items: center;">
    <div style="flex: 1;">
        <p>Most (if not all) modern game engines are capable of only simulating rigid body dynamics (left). However their counterpart, <b>soft bodies</b> (right) are not a feature available to developers out of the box or without the need to tinker and create custom solutions to solve for them in real-time rendering applications such as games and interactive applications.</p>
    </div>
    <div style="flex: 1;" align="center">
        <img src="https://media.giphy.com/media/J5XaDN7mg3lHLoUJbu/giphy.gif?cid=ecf05e47wjl82fppofuwugevgps9nhf4mlnhov0t7uk6kydd&ep=v1_gifs_search&rid=giphy.gif&ct=g" object-fit="contain" width="350px" height="200px" align="center">
        <img src = "https://media.giphy.com/media/l4FGHzb9sBnQmYjyU/giphy.gif?cid=ecf05e471w0gc90idkxq0236pp7yqx1h0n127w79ykqxmwr3&ep=v1_gifs_search&rid=giphy.gif&ct=g" object-fit="contain" width="200px" height="200px" align = "center">
    </div>
    <div align = "center">
    <p>It is for this reason that we decided to build <b>Jelly Engine.</b></p>
    </div>
</div>
<br>
<p>Soft bodies are all around us in the physical world. Ubiquitous materials such as human skin, rubber balls or even jelly behave in complex ways, which are typically hard to simulate and even more so at runtime while maintaining good performance in current hardware. Applications of this technology could be, but not limited to:</p>
<ul>
  <li><b>Medicine</b>: Training environments for surgery practicioners with high fidelity models of human organs and anatomy.</li>
  <li><b>Engineering</b>: Simulation and analysis of deformable materials like polymers and lattice structures.</li>
  <li><b>Interactive applications</b>: New game design mechanics involving deformable 3D objects.</li>
</ul>

<h2>Features</h2>
<div align="center">
    <table>
        <tr>
            <td><b>Rendering</b></td>
        </tr>
        <tr>
            <td>
                <ul>
                    <li>OpenGL rasterized graphics.</li>
                    <li>Support for 26+ 3D file formats.</li>
                    <li>Shaders (fragment, vertex, compute).</li>
                    <li>Blinn-phong shading with rgb color.</li>
                    <li>Multi-model scenes.</li>
                    <li>"Gummy Shader:" A jelly-like shader based on the Oren-Nayar reflectance model (simulate SSS).</li>
                </ul>
            </td>
            <td>
                <img src="https://github.com/Rafapp/jellyengine/assets/38381290/f11cf8ac-0174-47a3-84cb-1bfb2166e671" width="500" align="center">
                <p align="center">Stanford Dragon: 566,098 vertices, 1,132,830 triangles</p>
                <p align="center">Rendering realtime at 200+ FPS using "Gummy Shader"</p>
            </td>
        </tr>
    </table>
</div>

<div align="center">
    <table>
        <tr>
            <td><b>Soft Body Physics</b></td>
        </tr>
        <tr>
            <td>
                <ul>
                  <li>Dampened spring-mass model.</li>
                  <li>Euler integration.</li>
                  <li>Realtime soft body simulation.</li>
                  <li>Softbody-plane collision.</li>
                  <li>"Toybox" demo with 5 different soft bodies to play with, made with Jelly Engine.</li>
                </ul>
            </td>
            <td>
                <img src=https://github.com/Rafapp/jellyengine/assets/38381290/947ec998-76cd-4140-871a-97a203687502 width = "500" align = "center">
                <p align="center">"Toybox" demo made with Jelly Engine.</p>
            </td>
        </tr>
    </table>
</div>

## Instructions
### Running the toybox demo:

1. Install [CMake](https://cmake.org/download/).
2. Add CMake to `PATH`.
3. Run [build.bat](build.bat) to build the engine with the toybox demo game.
6. If the demo builds successfully, an `out` folder in the root folder will be generated. Go to `out/Game/game.exe` and run the demo!

### Creating your own game

1. Install [CMake](https://cmake.org/download/).
2. Add CMake to `PATH`.
3. Write your own game code in [game/src/game.cpp](game/src/game.cpp) and [game/src/game.h](game/src/game.h).
   - Use the toybox demo provided as a template, delete the contents of its functions.
   - You can write your code using the `Start()`, `Update()`, and `Exit()` functions.
   - We recommend using the toybox demo provided to see how to work with a `light`, the `scene` vector, the 3D `Model` class, and the `SoftBody` class.
5. Run [build.bat](build.bat) to build the engine with your specific game.
6. If your C++ code compiles and links, an `out` folder in the root folder will be generated. Go to `out/Game/game.exe` and run your game!

### Building the engine as a static library `JellyEngine.lib`

1. Install [CMake](https://cmake.org/download/).
2. Add CMake to `PATH`.
3. Modify the engine as needed.
5. Run the engine's [build.bat](build.bat) file to build the engine as a static library.
6. If your C++ code compiles and links, an `out` folder in the root folder will be generated. Go to `out/Engine` and you should see the file `JellyEngine.lib`. You can now link this library with any C++ application.

### Credits
- Rafael Padilla Perez: C++ Code, game engine architecture, design and implementation.
- Joshua Ebreo: Spring mass model research and [testing repository](https://github.com/Josh-Ebreo/Jelly-Engine-Beta).

### Acknowledgements
This project could not have been accomplished without the support and guidance of our project advisor, Professor Kevin Smith, the counsel from Spartak Gevorgyan, and the encouragement and support from our family, friends, and peers in the Software Engineering Program at San Jose State University.

### Research poster
![U24 Poster pptx](https://github.com/Rafapp/jellyengine/assets/38381290/8f4fcbc9-51a2-4f19-9a26-4f4e37fde240)

