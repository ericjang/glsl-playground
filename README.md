#GLSL-Playground

glsl-playground is a viewer for OpenGL fragment shaders.
It is desgined to be compatible with http://shadertoy.com, so you can simply copy & paste your shader from ShaderToy for offline editing. This is also handy for consumer laptops that aren't powerful enough to run the WebGL overhead.

![screenshot.png](https://bitbucket.org/repo/jX8gon/images/1255298048-screenshot.png)

glsl-playground currently does not support `sampleCube` or `sampler2D` textures, and has no support for audio yet. Implementation is in progress.

## Compiling
Requires QT5. Build tested on Ubuntu Linux.

```
$ git clone https://ejang@bitbucket.org/ejang/glsl-playground.git
$ cd glsl-playground
$ qmake && make
```

## Usage

Save your shader in a plaintext file (e.g. myShader.txt or myShader.frag, extension doesn't matter).

In your terminal, run 
```
./glsl-playground [path-to-your-shader] # e.g. myShader.txt
```

You can make edits to your shader in your favorite text editor, and recompile it by hitting the Ctrl-R hotkey. If there are mistakes in your shader, they will be printed to the terminal.

## TODO

* Add a built-in shader editor with realtime editing tweaks, inspired by Bret Victor's ["Inventing on Principle" Talk](https://vimeo.com/36579366) and [Apple's Swift Playground](http://www.objc.io/issue-16/rapid-prototyping-in-swift-playgrounds.html).

## Supported Platforms

This has tested with OpenGL versions 3.0 and 4.3 on Ubuntu Linux.