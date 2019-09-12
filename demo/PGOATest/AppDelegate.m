//
//  AppDelegate.m
//  PGOATest
//
//  Created by rhythmkay on 2019/9/12.
//  Copyright © 2019 rhythmkay. All rights reserved.
//

#import "AppDelegate.h"
#import <PGOAnalyzer/PGOAnalyzer.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        
        
        pgoa_end(true,^(NSString *str){
            NSLog(@"%@",str);
        });
         

        /*
         //如下函数调用会生成order_file,和order_string.且返回的是一个文件路径
         //需要自己拷贝出来使用.
        pgoa_endp(^(NSString *path_orderfile, NSString *path_string) {
            
        });
        */

        /*
         NSString *doc = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
         NSString *file = [doc stringByAppendingPathComponent:@"order.txt"];
         pgoa_endwithfile(true,file,^(NSString *path){
         NSLog(@"path=%@",path);
         });
         */
        
        //        pgoa_logall(false,nil);
    });
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
