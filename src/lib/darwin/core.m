// Based on wallpaper.m from github.com/sindresorhus/macos-wallpaper
// Original work Copyright © Sindre Sorhus
// Modified work Copyright (c) 2017 Filip Stanis
// This code is licensed under MIT license (see LICENSE for details)

@import AppKit.NSCell;
@import AppKit.NSScreen;
@import AppKit.NSWorkspace;
@import Foundation.NSString;
@import Foundation.NSURL;

#include "errors.h"

int set_background_darwin(const char* path) {
  @autoreleasepool {
    NSURL* image = [NSURL fileURLWithPath:[NSString stringWithUTF8String:path] isDirectory:NO];
    NSError* err;
    if ([image checkResourceIsReachableAndReturnError:&err] == NO) {
      return E_INVALID_PATH;
    }
    NSWorkspace* sw = [NSWorkspace sharedWorkspace];
    NSScreen* screen = [NSScreen mainScreen];

    NSMutableDictionary *opts = [[sw desktopImageOptionsForScreen:screen] mutableCopy];
    [opts setObject:[NSNumber numberWithInt:NSImageScaleNone] forKey:NSWorkspaceDesktopImageScalingKey];
    [opts setObject:[NSNumber numberWithBool:NO] forKey:NSWorkspaceDesktopImageAllowClippingKey];

    bool success = [sw setDesktopImageURL:image forScreen:screen options:opts error:&err];
    if (!success) {
      return E_FAIL;
    }
    return E_SUCCESS;
  }
}
