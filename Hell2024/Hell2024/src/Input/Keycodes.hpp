// From glfw3.h
#pragma once

// Not used right now
constexpr static auto HELL_KEY_APOSTROPHE = 39;  /* ' */
constexpr static auto HELL_KEY_COMMA = 44;  /* , */
constexpr static auto HELL_KEY_PERIOD = 46;  /* . */
constexpr static auto HELL_KEY_SLASH = 47;  /* / */
constexpr static auto HELL_KEY_0 = 48;

// In use
constexpr static auto HELL_KEY_SPACE = 32; // Jump and some editor debug stuff
constexpr static auto HELL_KEY_MINUS = 45; // Go down (Noclip debug thing)
constexpr static auto HELL_KEY_1 = 49; // Debug 1 Key

constexpr static auto HELL_KEY_2 = 50;
constexpr static auto HELL_KEY_3 = 51;
constexpr static auto HELL_KEY_4 = 52;
constexpr static auto HELL_KEY_5 = 53;
constexpr static auto HELL_KEY_6 = 54;
constexpr static auto HELL_KEY_7 = 55;
constexpr static auto HELL_KEY_8 = 56;
constexpr static auto HELL_KEY_9 = 57;
constexpr static auto HELL_KEY_SEMICOLON = 59;  /* ; */
constexpr static auto HELL_KEY_EQUAL = 61;  /* = */
constexpr static auto HELL_KEY_A = 65;
constexpr static auto HELL_KEY_B = 66;
constexpr static auto HELL_KEY_C = 67;
constexpr static auto HELL_KEY_D = 68;
constexpr static auto HELL_KEY_E = 69;
constexpr static auto HELL_KEY_F = 70;
constexpr static auto HELL_KEY_G = 71;
constexpr static auto HELL_KEY_H = 72;
constexpr static auto HELL_KEY_I = 73;
constexpr static auto HELL_KEY_J = 74;
constexpr static auto HELL_KEY_K = 75;
constexpr static auto HELL_KEY_L = 76;
constexpr static auto HELL_KEY_M = 77;
constexpr static auto HELL_KEY_N = 78;
constexpr static auto HELL_KEY_O = 79;
constexpr static auto HELL_KEY_P = 80;
constexpr static auto HELL_KEY_Q = 81;
constexpr static auto HELL_KEY_R = 82;
constexpr static auto HELL_KEY_S = 83;
constexpr static auto HELL_KEY_T = 84;
constexpr static auto HELL_KEY_U = 85;
constexpr static auto HELL_KEY_V = 86;
constexpr static auto HELL_KEY_W = 87;
constexpr static auto HELL_KEY_X = 88;
constexpr static auto HELL_KEY_Y = 89;
constexpr static auto HELL_KEY_Z = 90;
constexpr static auto HELL_KEY_LEFT_BRACKET = 91;  /* [ */
constexpr static auto HELL_KEY_BACKSLASH = 92;  /* \ */
constexpr static auto HELL_KEY_RIGHT_BRACKET = 93;  /* ] */
constexpr static auto HELL_KEY_GRAVE_ACCENT = 96;  /* ` */
constexpr static auto HELL_KEY_WORLD_1 = 161; /* non-US #1 */
constexpr static auto HELL_KEY_WORLD_2 = 162; /* non-US #2 */

/* Function keys */
constexpr static auto HELL_KEY_ESCAPE = 256;
constexpr static auto HELL_KEY_ENTER = 257;
constexpr static auto HELL_KEY_TAB = 258;
constexpr static auto HELL_KEY_BACKSPACE = 259;
constexpr static auto HELL_KEY_INSERT = 260;
constexpr static auto HELL_KEY_DELETE = 261;
constexpr static auto HELL_KEY_RIGHT = 262;
constexpr static auto HELL_KEY_LEFT = 263;
constexpr static auto HELL_KEY_DOWN = 264;
constexpr static auto HELL_KEY_UP = 265;
constexpr static auto HELL_KEY_PAGE_UP = 266;
constexpr static auto HELL_KEY_PAGE_DOWN = 267;
constexpr static auto HELL_KEY_HOME = 268;
constexpr static auto HELL_KEY_END = 269;
constexpr static auto HELL_KEY_CAPS_LOCK = 280;
constexpr static auto HELL_KEY_SCROLL_LOCK = 281;
constexpr static auto HELL_KEY_NUM_LOCK = 282;
constexpr static auto HELL_KEY_PRINT_SCREEN = 283;
constexpr static auto HELL_KEY_PAUSE = 284;
constexpr static auto HELL_KEY_F1 = 290;
constexpr static auto HELL_KEY_F2 = 291;
constexpr static auto HELL_KEY_F3 = 292;
constexpr static auto HELL_KEY_F4 = 293;
constexpr static auto HELL_KEY_F5 = 294;
constexpr static auto HELL_KEY_F6 = 295;
constexpr static auto HELL_KEY_F7 = 296;
constexpr static auto HELL_KEY_F8 = 297;
constexpr static auto HELL_KEY_F9 = 298;
constexpr static auto HELL_KEY_F10 = 299;
constexpr static auto HELL_KEY_F11 = 300;
constexpr static auto HELL_KEY_F12 = 301;
constexpr static auto HELL_KEY_F13 = 302;
constexpr static auto HELL_KEY_F14 = 303;
constexpr static auto HELL_KEY_F15 = 304;
constexpr static auto HELL_KEY_F16 = 305;
constexpr static auto HELL_KEY_F17 = 306;
constexpr static auto HELL_KEY_F18 = 307;
constexpr static auto HELL_KEY_F19 = 308;
constexpr static auto HELL_KEY_F20 = 309;
constexpr static auto HELL_KEY_F21 = 310;
constexpr static auto HELL_KEY_F22 = 311;
constexpr static auto HELL_KEY_F23 = 312;
constexpr static auto HELL_KEY_F24 = 313;
constexpr static auto HELL_KEY_F25 = 314;
constexpr static auto HELL_KEY_KP_0 = 320;
constexpr static auto HELL_KEY_KP_1 = 321;
constexpr static auto HELL_KEY_KP_2 = 322;
constexpr static auto HELL_KEY_KP_3 = 323;
constexpr static auto HELL_KEY_KP_4 = 324;
constexpr static auto HELL_KEY_KP_5 = 325;
constexpr static auto HELL_KEY_KP_6 = 326;
constexpr static auto HELL_KEY_KP_7 = 327;
constexpr static auto HELL_KEY_KP_8 = 328;
constexpr static auto HELL_KEY_KP_9 = 329;
constexpr static auto HELL_KEY_KP_DECIMAL = 330;
constexpr static auto HELL_KEY_KP_DIVIDE = 331;
constexpr static auto HELL_KEY_KP_MULTIPLY = 332;
constexpr static auto HELL_KEY_KP_SUBTRACT = 333;
constexpr static auto HELL_KEY_KP_ADD = 334;
constexpr static auto HELL_KEY_KP_ENTER = 335;
constexpr static auto HELL_KEY_KP_EQUAL = 336;
constexpr static auto HELL_KEY_LEFT_SHIFT = 16;//340
constexpr static auto HELL_KEY_LEFT_CONTROL = 17;//341
constexpr static auto HELL_KEY_LEFT_ALT = 342;
constexpr static auto HELL_KEY_LEFT_SUPER = 343;
constexpr static auto HELL_KEY_RIGHT_SHIFT = 344;
constexpr static auto HELL_KEY_RIGHT_CONTROL = 345;
constexpr static auto HELL_KEY_RIGHT_ALT = 346;
constexpr static auto HELL_KEY_RIGHT_SUPER = 347;
constexpr static auto HELL_KEY_MENU = 348;
constexpr static auto HELL_KEY_LAST = HELL_KEY_MENU;

constexpr static auto HELL_KEY_LEFT_SHIFT_GLFW = 340;					// special case
constexpr static auto HELL_KEY_LEFT_CONTROL_GLFW = 341;					// special case

constexpr static auto HELL_MOUSE_LEFT = 350;
constexpr static auto HELL_MOUSE_RIGHT = 351;

constexpr static auto HELL_KEY_WIN_ENTER = 13;
constexpr static auto HELL_KEY_WIN_SHIFT = 16;
constexpr static auto HELL_KEY_WIN_CONTROL = 17;
constexpr static auto HELL_KEY_WIN_ALT = 18;
constexpr static auto HELL_KEY_WIN_TAB = 9;
constexpr static auto HELL_KEY_WIN_CAPSLOCK = 20;
constexpr static auto HELL_KEY_WIN_ESCAPE = 27;

/*constexpr static auto HELL_CONTROLLER_BUTTON_0	352
constexpr static auto HELL_CONTROLLER_BUTTON_1    353
constexpr static auto HELL_CONTROLLER_BUTTON_2    354
constexpr static auto HELL_CONTROLLER_BUTTON_3    355
constexpr static auto HELL_CONTROLLER_BUTTON_4    356
constexpr static auto HELL_CONTROLLER_BUTTON_5    357
constexpr static auto HELL_CONTROLLER_BUTTON_6    358
constexpr static auto HELL_CONTROLLER_BUTTON_7    359
constexpr static auto HELL_CONTROLLER_BUTTON_8    360
constexpr static auto HELL_CONTROLLER_BUTTON_9    361
constexpr static auto HELL_CONTROLLER_BUTTON_10	362
constexpr static auto HELL_CONTROLLER_BUTTON_11    363
constexpr static auto HELL_CONTROLLER_BUTTON_12    364
constexpr static auto HELL_CONTROLLER_BUTTON_13    365
constexpr static auto HELL_CONTROLLER_BUTTON_14    366
constexpr static auto HELL_CONTROLLER_BUTTON_15    367
constexpr static auto HELL_CONTROLLER_BUTTON_16    368
constexpr static auto HELL_CONTROLLER_BUTTON_17    369
constexpr static auto HELL_CONTROLLER_BUTTON_18    370
constexpr static auto HELL_CONTROLLER_BUTTON_19    371*/

constexpr static auto HELL_PS_4_CONTROLLER_CROSS = 1;	//0
constexpr static auto HELL_PS_4_CONTROLLER_CIRCLE = 2;	//1
constexpr static auto HELL_PS_4_CONTROLLER_SQUARE = 0;	//2
constexpr static auto HELL_PS_4_CONTROLLER_TRIANGLE = 3;
constexpr static auto HELL_PS_4_CONTROLLER_L1 = 4;
constexpr static auto HELL_PS_4_CONTROLLER_L2 = 6;
constexpr static auto HELL_PS_4_CONTROLLER_L3 = 10;	//9
constexpr static auto HELL_PS_4_CONTROLLER_R1 = 5;
constexpr static auto HELL_PS_4_CONTROLLER_R2 = 7;
constexpr static auto HELL_PS_4_CONTROLLER_R3 = 11;	//10
constexpr static auto HELL_PS_4_CONTROLLER_SHARE = 6;
constexpr static auto HELL_PS_4_CONTROLLER_OPTIONS = 9;	//7
constexpr static auto HELL_PS_4_CONTROLLER_PS_BUTTON = 12;	//8
constexpr static auto HELL_PS_4_CONTROLLER_DPAD_UP = 14;	//11
constexpr static auto HELL_PS_4_CONTROLLER_DPAD_RIGHT = 15;	//12
constexpr static auto HELL_PS_4_CONTROLLER_DPAD_DOWN = 16;	//13
constexpr static auto HELL_PS_4_CONTROLLER_DPAD_LEFT = 17;	//14
constexpr static auto HELL_PS_4_CONTROLLER_TRIGGER_L = 18;			// you manually chose this button code so u can store it in the same buttons vector
constexpr static auto HELL_PS_4_CONTROLLER_TRIGGER_R = 19;			// you manually chose this button code so u can store it in the same buttons vector

constexpr static auto HELL_XBOX_CONTROLLER_A = 0;
constexpr static auto HELL_XBOX_CONTROLLER_B = 1;
constexpr static auto HELL_XBOX_CONTROLLER_X = 2;
constexpr static auto HELL_XBOX_CONTROLLER_Y = 3;
constexpr static auto HELL_XBOX_CONTROLLER_L1 = 4;
constexpr static auto HELL_XBOX_CONTROLLER_R1 = 5;
constexpr static auto HELL_XBOX_CONTROLLER_WIERD_1 = 6;
constexpr static auto HELL_XBOX_CONTROLLER_WIERD_2 = 7;
constexpr static auto HELL_XBOX_CONTROLLER_L3 = 8;
constexpr static auto HELL_XBOX_CONTROLLER_R3 = 9;
constexpr static auto HELL_XBOX_CONTROLLER_DPAD_UP = 10;
constexpr static auto HELL_XBOX_CONTROLLER_DPAD_RIGHT = 11;
constexpr static auto HELL_XBOX_CONTROLLER_DPAD_DOWN = 12;
constexpr static auto HELL_XBOX_CONTROLLER_DPAD_LEFT = 13;
constexpr static auto HELL_XBOX_CONTROLLER_TRIGGER_L = 14;			// you manually chose this button code so u can store it in the same buttons vector
constexpr static auto HELL_XBOX_CONTROLLER_TRIGGER_R = 15;			// you manually chose this button code so u can store it in the same buttons vector

constexpr static auto HELL_KEY_NUMPAD_0 = 320;
constexpr static auto HELL_KEY_NUMPAD_1 = 321;
constexpr static auto HELL_KEY_NUMPAD_2 = 322;
constexpr static auto HELL_KEY_NUMPAD_3 = 323;
constexpr static auto HELL_KEY_NUMPAD_4 = 324;
constexpr static auto HELL_KEY_NUMPAD_5 = 325;
constexpr static auto HELL_KEY_NUMPAD_6 = 326;
constexpr static auto HELL_KEY_NUMPAD_7 = 327;
constexpr static auto HELL_KEY_NUMPAD_8 = 328;
constexpr static auto HELL_KEY_NUMPAD_9 = 329;
constexpr static auto HELL_KEY_NUMPAD_DECIMAL = 330;
constexpr static auto HELL_KEY_NUMPAD_DIVIDE = 331;
constexpr static auto HELL_KEY_NUMPAD_MULTIPLY = 332;
constexpr static auto HELL_KEY_NUMPAD_SUBTRACT = 333;
constexpr static auto HELL_KEY_NUMPAD_ADD = 334;
constexpr static auto HELL_KEY_NUMPAD_ENTER = 335;
constexpr static auto HELL_KEY_NUMPAD_EQUAL = 336;