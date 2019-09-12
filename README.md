# PGOAnalyzer
support for iOS objc application's binary layout.二进制重排trace生成order_file以及order_string

PGOAnalyzer

#### 一、关于

Analyzer目标是实现对objc程序的动态trace并顺序记录启动过程中的所有符号调用，以达到二进制（代码段）重排目的。

重排的trace过程主要有2种方式，编译插桩和运行时trace。从代码覆盖率上来说编译插桩是最佳方式，但编译插桩无法解决工程中引入的二进制库的重排问题。所以本项目采取了运行时trace的动态方式来插桩而实现trace过程，最终完成重排。

> 实际使用，可以考虑编译插桩与动态trace结合，合并生成order file符号信息，以达到更优。


#### 二、使用方式

使用方式如下：

 1. 将release目录下的PGOAnalyzer.framework拖到当前app内，由于是动态库需要特殊设置，且尽量使得当前动态库排在第一位，以避免工程中接入了其它动态库而无法及时trace该动态库的问题，设置如下图：

或参考 [Embedding Frameworks In An App](https://developer.apple.com/library/archive/technotes/tn2435/_index.html)

 2. 在主app，自定义一个新的类，重写其load方法，如，添加如下代码，即可：

```
 #if defined(__arm64__) || defined(__aarch64__)
 #import <PGOAnalyzer/PGOAnalyzer.h>
 
 void my_cpp_initializer(int argc, const char* argv[], const char* envp[], const char* apple[], const pgoa_program_vars_t* vars)
 {
    pgoa_stub_initializer(argc,argv,envp,apple,vars);
 }
 
 @interface PGOALTest : NSObject
 @end
 
 @implementation PGOALTest
 
 + (void)load
 {
    pgoa_hook_mod_init((intptr_t)my_cpp_initializer);
 }
 
 @end
 
 #endif
 
 ```
 
 3. 在启动结束时间点，如主viewcontroller的viewDidAppear等回调里加入如下代码：

 ```
  #if defined(__arm64__) || defined(__aarch64__)
  #import <PGOAnalyzer/PGOAnalyzer.h>
    pgoa_end(true,^(NSString *str){
        NSLog(@"%@",str);
    });
    /*
    NSString *doc = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *file = [doc stringByAppendingPathComponent:@"order.txt"];
    pgoa_endwithfile(true,file,^(NSString *path){
        NSLog(@"path=%@",path);
    });
    */
    /*
    //如下函数调用会生成order_file,和order_string.且返回的是一个文件路径
    //需要自己拷贝出来使用.
    pgoa_endp(^(NSString *path_orderfile, NSString *path_string) {
            
    });
    */
  #endif
```

 4. 以上新加的代码，必须处于如下宏定义内.使用arm64,arm64e设备真机测试运行即可.

 ```
 #if defined(__arm64__) || defined(__aarch64__)
    //..代码块
 #endif
 
 //需要引入头文件：
 #import <PGOAnalyzer/PGOAnalyzer.h>
 ```
 
 5. 如果选择默认配置，则需要开启符号表（在工程配置Build Settings里找到并关闭strip linked product），否则无法自动翻译符号表，Strip Linked Product = NO;
 

 6. 按照如上接入后，构建打包，建议Release下构建打包并运行。

 > 备注：如果是DEBUG下构建打包则不需要设置5中的Strip Linked Product = NO;

 7. 运行后得到的翻译后的文件名为order_file.txt，且默认在Documents目录下，可自行完成选择导出;
 
 8. 将7中导出的文件，配置到正式仓库工程中，设置order_file，如：
 将order_file.txt文件放到工程根目录，然后在Build Settings里设置order file，添加值为$(SRCROOT)/order_file.txt

 ![image](http://cdn.rhythmkay.com/img/09122040.png)

 9. 再次重新构建打包，即得到重排后的二进制。
 
 如需要重排字符串，请将生成的PGOAOrderString.m文件拖进工程里，且在Build Phases里找到Compile Sources并将PGOAOrderString.m拖到最顶部即可。
 
 #### 三、其它
  建议结合编译插桩来生成多份order_file来拼凑起一个更完善的order file；工程里不要再hook objc_msgSend,block,initialize,load,dispatch_sync,UIViewController等逻辑，不然可能会有异常情况。
