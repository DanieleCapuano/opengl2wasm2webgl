var LIB_main =
/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./js/index_main.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./js/index_main.js":
/*!**************************!*\
  !*** ./js/index_main.js ***!
  \**************************/
/*! exports provided: API */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"API\", function() { return API; });\n/* harmony import */ var _scss_index_scss__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../scss/index.scss */ \"./scss/index.scss\");\n/* harmony import */ var _scss_index_scss__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(_scss_index_scss__WEBPACK_IMPORTED_MODULE_0__);\n\nconst API = {\n  start: _start_render\n};\nlet canvas;\nlet Bindings = {};\nlet u_opacity = 1.;\nlet is_camera = false;\nlet ////////////////////////\ntranslation_amount = .1,\n    rotation_amount = 1; //world translate x and y\n\nlet t_x = 0.0,\n    t_y = 0.0; //camera rotate\n\nlet r_x = 0.0,\n    r_y = 0.0;\n\nfunction _start_render() {\n  render();\n}\n\nfunction render() {\n  // Get A WebGL context\n\n  /** @type {HTMLCanvasElement} */\n  canvas = document.getElementById(\"canvas\");\n  Module = window.Module || {};\n  Module.canvas = canvas;\n  Module.onRuntimeInitialized = doRun;\n\n  if (Module.calledRun === true) {\n    doRun();\n  } ///////////////////////////////////////\n  ///////////////////////////////////////\n  // DRAW\n\n\n  function doRun() {\n    Bindings.initGL = Module.cwrap('initGLAPI', 'number', ['number', 'number']);\n    Bindings.draw = Module.cwrap('drawAPI', '', ['number', 'number', 'number', 'number', 'number', 'number', 'number', 'number']);\n\n    if (!Bindings.initGL(canvas.width, canvas.height)) {\n      console.warn(\"OpenGL Error\");\n    }\n\n    listenToInputs();\n    console.info(\"Press 'r' for (eye) Rotation, 't' for (world) Translation\");\n    draw_loop();\n  }\n\n  function draw_loop(now) {\n    requestAnimationFrame(draw_loop);\n    resizeCanvasToDisplaySize(canvas);\n    Bindings.draw(canvas.width, canvas.height, performance.now() / 1000, u_opacity, t_x, t_y, //translate x and y\n    r_x, r_y //rotate x and y\n    );\n  }\n\n  function listenToInputs() {\n    document.addEventListener('keydown', e => {\n      switch (e.key) {\n        case \"r\":\n          console.info(\"Operation set to (eye) rotate\");\n          is_camera = true;\n          break;\n\n        case \"t\":\n          console.info(\"Operation set to (world) translate\");\n          is_camera = false;\n          break;\n\n        case \"ArrowLeft\":\n          if (is_camera) {\n            r_x -= rotation_amount;\n          } else {\n            t_x -= translation_amount;\n          }\n\n          ;\n          break;\n\n        case \"ArrowUp\":\n          if (is_camera) {\n            r_y -= rotation_amount;\n          } else {\n            t_y += translation_amount;\n          }\n\n          break;\n\n        case \"ArrowRight\":\n          if (is_camera) {\n            r_x += rotation_amount;\n          } else {\n            t_x += translation_amount;\n          }\n\n          break;\n\n        case \"ArrowDown\":\n          if (is_camera) {\n            r_y += rotation_amount;\n          } else {\n            t_y -= translation_amount;\n          }\n\n          break;\n      }\n    });\n  }\n\n  function resizeCanvasToDisplaySize(canvas, multiplier) {\n    multiplier = multiplier || 1;\n    multiplier = Math.max(0, multiplier);\n    var width = canvas.clientWidth * multiplier | 0;\n    var height = canvas.clientHeight * multiplier | 0;\n\n    if (canvas.width !== width || canvas.height !== height) {\n      canvas.width = width;\n      canvas.height = height;\n      return true;\n    }\n\n    return false;\n  }\n}\n\n//# sourceURL=webpack://LIB_main/./js/index_main.js?");

/***/ }),

/***/ "./scss/index.scss":
/*!*************************!*\
  !*** ./scss/index.scss ***!
  \*************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("// extracted by mini-css-extract-plugin\n\n//# sourceURL=webpack://LIB_main/./scss/index.scss?");

/***/ })

/******/ });