#import <AppKit/AppKit.h>

float getDisplayScalingFactor() {
  NSScreen *mainScreen = [NSScreen mainScreen];
  CGFloat scalingFactor = [mainScreen backingScaleFactor];
  return scalingFactor;
}
