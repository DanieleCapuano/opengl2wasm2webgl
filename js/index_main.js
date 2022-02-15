import '../scss/index.scss';

export const API = {
    start: _start_render
};

let canvas;
let Bindings = {};
let u_opacity = 1.;

function _start_render() {
    render();
}

function render() {
    // Get A WebGL context
    /** @type {HTMLCanvasElement} */
    canvas = document.getElementById("canvas");
    Module = window.Module || {};
    Module.canvas = canvas;
    Module.onRuntimeInitialized = doRun;
    if (Module.calledRun === true) {
        doRun();
    }

    ///////////////////////////////////////
    ///////////////////////////////////////
    // DRAW

    function doRun() {
        Bindings.initGL = Module.cwrap('initGLAPI', 'number', ['number', 'number']);
        Bindings.draw = Module.cwrap('drawAPI', '', ['number', 'number', 'number', 'number']);

        if (!Bindings.initGL(canvas.width, canvas.height)) {
            console.warn("OpenGL Error");
        }

        draw_loop();
    }

    function draw_loop(now) {
        requestAnimationFrame(draw_loop);
        resizeCanvasToDisplaySize(canvas);
        Bindings.draw(canvas.width, canvas.height, performance.now() / 1000, u_opacity);
    }

    function resizeCanvasToDisplaySize(canvas, multiplier) {
        multiplier = multiplier || 1;
        multiplier = Math.max(0, multiplier);
        var width = canvas.clientWidth * multiplier | 0;
        var height = canvas.clientHeight * multiplier | 0;
      
        if (canvas.width !== width || canvas.height !== height) {
          canvas.width = width;
          canvas.height = height;
          return true;
        }
      
        return false;
      }
}
