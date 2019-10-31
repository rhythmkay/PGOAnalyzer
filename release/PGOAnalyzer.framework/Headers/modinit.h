//
//  mod_init_hook.h
//  PGOAnalyzer
//
//  Created by rhythmzhang on 2019/8/13.
//  Copyright © 2019 rhythmzhang. All rights reserved.
//

#if defined(__arm64__) || defined(__aarch64__)
#import <Foundation/Foundation.h>

//copy from dyld ImageLoader.h
typedef struct
{
    const void*        mh;
    int*            NXArgcPtr;
    const char***    NXArgvPtr;
    const char***    environPtr;
    const char**    __prognamePtr;
} pgoa_program_vars_t;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    void pgoa_stub_initializer(int argc, const char* argv[], const char* envp[], const char* apple[], const pgoa_program_vars_t* vars);
    void pgoa_hook_mod_init(intptr_t func);
    
#ifdef __cplusplus
}
#endif  // __cplusplus


#endif
