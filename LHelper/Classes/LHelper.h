//
//  Created by Luka Gabrić.
//  Copyright (c) 2013 Luka Gabrić. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LHelperCategories.h"


#pragma mark - String empty


#define isStringEmptyOrNil(str) [LHelper isStringEmptyOrNil:str]


#pragma mark - StrTo conversion


#define StrToInt(str) [str intValue]
#define StrToInteger(str) [str integerValue]
#define StrToFloat(str) [str floatValue]


#pragma mark - ToStr conversion


#define IntToStr(int) [NSString stringWithFormat:@"%d", int]
#define Int32ToStr(int) [NSString stringWithFormat:@"%ld", int]
#define Int64ToStr(int) [NSString stringWithFormat:@"%lld", int]
#define FloatToStr(float) [NSString stringWithFormat:@"%f", float]


#pragma mark - Log


#if DEBUG
#define LogLong(format, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Print(object)        NSLog(@"%@", object)
#define Log(format, ...)	 NSLog(@"%@", [NSString stringWithFormat:format, ## __VA_ARGS__])
#define LogInt(someInt)	     NSLog(@"%d", someInt)
#define LogFloat(someFloat)  NSLog(@"%f", someFloat)
#else
#define LogLong(format, ...)
#define Print(object)
#define Log(format, ...)
#define LogInt(someInt)
#define LogFloat(someFloat)
#endif


#pragma mark - LWarning

#if DEBUG
#define LWarning(condition, desc, ...)	\
if (!(condition)) {		\
NSLog(@"\n======> WARNING: " desc @"; %s [Line %d] ", ##__VA_ARGS__, __PRETTY_FUNCTION__, __LINE__);		\
}
#else
#define LWarning(condition, desc, ...)
#endif


#pragma mark - LAssert


#if DEBUG
#define LAssert(condition, desc, ...)	\
do {				\
__PRAGMA_PUSH_NO_EXTRA_ARG_WARNINGS \
if (!(condition)) {		\
[[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
object:self file:[NSString stringWithUTF8String:__FILE__] \
lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
}				\
__PRAGMA_POP_NO_EXTRA_ARG_WARNINGS \
} while(0)
#else
#define LAssert(condition, desc, ...)
#endif


#pragma mark - RGB color


#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1]
#define RGBA(r, g, b, a) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]
#define UIColorFromHex(hexValue) [UIColor colorWithRed:((float)((hexValue & 0xFF0000) >> 16))/255.0 green:((float)((hexValue & 0xFF00) >> 8))/255.0 blue:((float)(hexValue & 0xFF))/255.0 alpha:1.0]
#define UIColorFromHexAlpha(hexValue, a) [UIColor colorWithRed:((float)((hexValue & 0xFF0000) >> 16))/255.0 green:((float)((hexValue & 0xFF00) >> 8))/255.0 blue:((float)(hexValue & 0xFF))/255.0 alpha:a]


#pragma mark - Check if widescreen


#define isWidescreen() (fabs((double)[[UIScreen mainScreen] bounds].size.height - (double)568) < DBL_EPSILON)


#pragma mark - Check device


#define isIPhone() ([[[UIDevice currentDevice] model] isEqualToString:@"iPhone"])
#define isIPad() (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define isIPod() ([[[UIDevice currentDevice] model] isEqualToString:@"iPod touch"])


#pragma mark - Deg2Rad


#define degreesToRadians(x) (M_PI * x / 180.0)
#define radiansToDegrees(x) (x * (180.0 / M_PI))


#pragma mark - Functions to get dirs


#define documentsDir() [LHelper documentsDir]
#define libraryDir() [LHelper libraryDir]
#define cachesDir() [LHelper cachesDir]


#pragma mark - Check iOS versions


#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)


#define isIOS6() SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"6") && SYSTEM_VERSION_LESS_THAN(@"7")
#define isIOS7() SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"7")


#pragma mark - Singleton GCD Macro


#ifndef SINGLETON_GCD
#define SINGLETON_GCD(classname)                        \
\
+ (classname *)shared##classname {                      \
\
static dispatch_once_t pred;                        \
__strong static classname * shared##classname = nil;\
dispatch_once( &pred, ^{                            \
shared##classname = [[self alloc] init]; });    \
return shared##classname;                           \
}
#endif


#pragma mark - Async Test Flag


#define StartBlock() __block BOOL waitingForBlock = YES
#define EndBlock() waitingForBlock = NO
#define WaitUntilBlockCompletes() WaitWhile(waitingForBlock)
#define WaitWhile(condition) \
do { \
while(condition) { \
[[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:0.1]]; \
} \
} while(0)


#pragma mark -


@interface LHelper : NSObject


#pragma mark - Is string empty


+ (BOOL)isStringEmptyOrNil:(NSString *)string;


#pragma mark - Basic HTTP Authentication


+ (NSDictionary *)basicHttpAuthDictForUsername:(NSString *)username andPassword:(NSString *)password;


#pragma mark - Human readable file size


+ (NSString *)humanReadableFileSizeWithBytes:(CGFloat)bytes;


#pragma mark - Validate password


#define isPasswordValid(password) [LHelper isPasswordValid:password]


+ (BOOL)isPasswordValid:(NSString *)pass;


#pragma mark - Validate email


#define isMailValid(mail) [LHelper isMailValid:mail]


+ (BOOL)isMailValid:(NSString *)email;


#pragma mark - DoNotBackup


+ (BOOL)addSkipBackupAttributeToItemAtURL:(NSURL *)URL;
+ (BOOL)addSkipBackupAttributeToItemAtPath:(NSString *)path;


#pragma mark - UUID


#define newUUID() [LHelper getUUID]


+ (NSString *)getUUID;


#pragma mark - RGB color


+ (UIColor *)colorFromHexString:(NSString *)hexString;


#pragma mark - Image With UIColor


+ (UIImage *)imageWithColor:(UIColor *)color;


#pragma mark - Radnom


+ (NSInteger)randomNumberBetweenA:(NSInteger)a andB:(NSInteger)b;


#define randomInRange(a,b) [LHelper randomNumberBetweenA:a andB:b]


#pragma mark - Get View From Nib


+ (UIView *)getViewWithClass:(Class)viewClass fromNibNamed:(NSString *)nibName;


#pragma mark - Get applications window


+ (UIWindow *)appWindow;


#pragma mark - Get docs and lib dirs


+ (NSString *)documentsDir;
+ (NSString *)libraryDir;
+ (NSString *)cachesDir;


#pragma mark - Convert/get dates


+ (NSDate *)dateFromString:(NSString *)string withFormat:(NSString *)theFormat;
+ (NSString *)stringFromDate:(NSDate *)date withFormat:(NSString *)theFormat;


#pragma mark -


@end