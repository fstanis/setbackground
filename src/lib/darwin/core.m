// Based on wallpaper.m from github.com/sindresorhus/macos-wallpaper
// Original work Copyright © Sindre Sorhus
// Modified work Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

@import AppKit.NSCell;
@import AppKit.NSScreen;
@import AppKit.NSWorkspace;
@import Foundation.NSString;
@import Foundation.NSURL;

#include "styles.h"
#include "errors.h"

static BOOL is_style_valid(int style) {
  return style == STYLE_CENTER || style == STYLE_STRETCH;
}

int set_background_darwin(const char* path, int style) {
  @autoreleasepool {
    if (!is_style_valid(style)) {
      return E_UNSUPPORTED_STYLE;
    }

    NSURL* image = [NSURL fileURLWithPath:[NSString stringWithUTF8String:path] isDirectory:NO];
    NSError* err;
    if ([image checkResourceIsReachableAndReturnError:&err] == NO) {
      return E_INVALID_PATH;
    }
    NSWorkspace* sw = [NSWorkspace sharedWorkspace];
    NSScreen* screen = [NSScreen mainScreen];

    NSMutableDictionary *opts = [[sw desktopImageOptionsForScreen:screen] mutableCopy];
    if (style == STYLE_CENTER) {
      [opts setObject:[NSNumber numberWithInt:NSImageScaleNone] forKey:NSWorkspaceDesktopImageScalingKey];
      [opts setObject:[NSNumber numberWithBool:NO] forKey:NSWorkspaceDesktopImageAllowClippingKey];
    } else if (style == STYLE_STRETCH) {
      [opts setObject:[NSNumber numberWithInt:NSImageScaleAxesIndependently] forKey:NSWorkspaceDesktopImageScalingKey];
      [opts setObject:[NSNumber numberWithBool:YES] forKey:NSWorkspaceDesktopImageAllowClippingKey];
    }

    bool success = [sw setDesktopImageURL:image forScreen:screen options:opts error:&err];
    if (!success) {
      return E_FAIL;
    }
    return E_SUCCESS;
  }
}
