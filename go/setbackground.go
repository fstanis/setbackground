// Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

// Package setbackground allows easily changing the desktop background
// (wallpaper) regardless of operating system and desktop environment.
package setbackground

// #cgo CFLAGS: -I${SRCDIR}/../src/lib
// #cgo darwin CFLAGS: -x objective-c -fmodules
// #cgo LDFLAGS: -L${SRCDIR}/../lib -lsetbackground
// #cgo linux LDFLAGS: -ldbus-1 -ldconf -lgio-2.0 -lgobject-2.0 -lglib-2.0 -ldl
// #cgo windows LDFLAGS: -lole32 -loleaut32 -lshlwapi
// #include <stdlib.h>
// #include "setbackground.h"
// #include "styles.h"
// #include "errors.h"
import "C"
import (
	"fmt"
	"unsafe"
)

const (
	// StyleCenter center the image (with no stretching).
	StyleCenter = int(C.STYLE_CENTER)
	// StyleStretch stretches the image to exactly fit on the screen.
	StyleStretch = int(C.STYLE_STRETCH)
	// StyleTile tiles the image across the screen.
	StyleTile = int(C.STYLE_TILE)
)

// SetBackground sets the current desktop background to the given image,
// applying the given style, if supported by the platform.
func SetBackground(path string, style int) error {
	pathStr := C.CString(path)
	result := C.set_background(pathStr, C.int(style))
	C.free(unsafe.Pointer(pathStr))
	return parseError(result)
}

func parseError(result C.int) error {
	if result == C.E_SUCCESS {
		return nil
	}

	return fmt.Errorf("error %d returned from setbackground", int(result))
}
