//
//  util.hpp
//
//  Created by Joel Schmidt on 3/10/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <string>
#include <GL/glew.h>

namespace util {
    GLint TextureFromFile(const char* path, std::string directory);
}

#endif /* util_hpp */
