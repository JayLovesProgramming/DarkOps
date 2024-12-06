#pragma once

// Load an image
// Don't render or update a LOT of stuff while in LOADING_STATE
// All we need to do is stop rendering and updating things that don't need to be in use
// Then we need to load the required assets and render a cool loading screen

enum class preGameState { LOADING_STATE };