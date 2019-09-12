//
//  CPPHook.h
//  PGOAnalyzer
//
//  Created by rhythmkay on 2019/8/13.
//  Copyright © 2019 rhythmkay. All rights reserved.
//

#import <Foundation/Foundation.h>

#if defined(__arm64__) || defined(__aarch64__)


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

 /*!
 * @function pgoa_endp
 *
 * @param completion
 * block传入并异步返回排列好的order symbol，和order_string的文件路径；
  注意：path_string返回的是一个.m文件，可以直接拖进工程Compile Source里设置，或导出为.m拖进Compile Source设置
 */
void pgoa_endp(void(^completion)(NSString* path_orderfile,NSString *path_string));
    

/*!
 * @function pgoa_end
 *
 * @abstract
 * 得到trace的order_file字符串
 *
 * @param symbolicate
 * 是否需要自动翻译符号表，建议传入true，否则需要自行结合dwarf翻译符号表
 *
 * @param completion
 * block传入并异步返回排列好的order symbol，由order_txt变量返回.
 */
 void pgoa_end(bool symbolicate, void(^completion)(NSString* order_txt));
    

/*!
 * @function pgoa_endwithfile
 *
 * @abstract
 * 得到trace的order_file保存的文件路径
 *
 * @param symbolicate
 * 是否需要自动翻译符号表，建议传入true，否则需要自行结合dwarf翻译符号表
 *
 * @param path
 * 指定order_file的路径或文件名，绝对路径.如/xxx/xx/abc.txt
 *
 * @param completion
 * block传入并异步返回实际写成功的order_file文件路径，由path变量返回.
 */
 void pgoa_endwithfile(bool symbolicate, NSString *path, void(^completion)(NSString *path));

#ifdef __cplusplus
}
#endif

#endif
