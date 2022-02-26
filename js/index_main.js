import '../scss/index.scss';

export const API = {
    start: _start_render
};

let canvas;
let Bindings = {};
let u_opacity = 1.;

let is_camera = false;
let ////////////////////////
    translation_amount = .1,
    rotation_amount = 1;

//world translate x and y
let t_x = 0.0,
    t_y = 0.0;

//camera rotate
let r_x = 0.0,
    r_y = 0.0;

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
        Bindings.draw = Module.cwrap('drawAPI', '', ['number', 'number', 'number', 'number', 'number', 'number', 'number', 'number']);

        if (!Bindings.initGL(canvas.width, canvas.height)) {
            console.warn("OpenGL Error");
        }

        listenToInputs();
        console.info("Press 'r' for (eye) Rotation, 't' for (world) Translation");

        draw_loop();
    }

    function draw_loop(now) {
        requestAnimationFrame(draw_loop);
        resizeCanvasToDisplaySize(canvas);
        Bindings.draw(
            canvas.width, 
            canvas.height, 
            performance.now() / 1000, u_opacity,
            t_x, t_y,    //translate x and y
            r_x, r_y     //rotate x and y
        );
    }

    function listenToInputs() {
        document.addEventListener('keydown', (e) => {
            switch (e.key) {
                case "r":
                    console.info("Operation set to (eye) rotate");
                    is_camera = true;
                    break;
                case "t":
                    console.info("Operation set to (world) translate");
                    is_camera = false;
                    break;
                case "ArrowLeft":
                    if (is_camera) {
                        r_x -= rotation_amount;
                    }
                    else {
                        t_x -= translation_amount;
                    };
                    break;
                case "ArrowUp":
                    if (is_camera) {
                        r_y -= rotation_amount;
                    }
                    else {
                        t_y += translation_amount;
                    }
                    break;
                case "ArrowRight":
                    if (is_camera) {
                        r_x += rotation_amount;
                    }
                    else {
                        t_x += translation_amount;
                    }
                    break;
                case "ArrowDown":
                    if (is_camera) {
                        r_y += rotation_amount;
                    }
                    else {
                        t_y -= translation_amount;
                    }
                    break;
            }
        });
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
