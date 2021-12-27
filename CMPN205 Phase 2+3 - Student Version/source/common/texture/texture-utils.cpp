#include "texture-utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

glm::ivec2 our::texture_utils::loadImage(Texture2D& texture, const char *filename, bool generate_mipmap) {
    //2D texture we load the image in, file name of the image, generate mipmap or not
    
    glm::ivec2 size;
    int channels;
    //Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
    //We need to till stb to flip images vertically after loading them

    //zay lma kant el sora ma2loba fe el tutorial
    //by3tbr awl row hwa a5r row
    stbi_set_flip_vertically_on_load(true);

    //Load image data and retrieve width, height and number of channels in the image
    //The last argument is the number of channels we want and it can have the following values:
    //- 0: Keep number of channels the same as in the image file
    //- 1: Grayscale only
    //- 2: Grayscale and Alpha
    //- 3: RGB
    //- 4: RGB and Alpha (RGBA)
    //Note: channels (the 4th argument) always returns the original number of channels in the file
    unsigned char* data = stbi_load(filename, &size.x, &size.y, &channels, 4);
    if(data == nullptr){
        std::cerr << "Failed to load image: " << filename << std::endl;
        return {0, 0};
    }
    //TODO: Finish this function
    //HINT: The steps should be as follows: bind the texture, send the pixel data to the GPU, then generate the mipmap (if requested).

    // bind the texture
    //Bind the texture such that we upload the image data to its storage
    texture.bind();

    // send the pixel data to the GPU
    //(type of texture, level of mipmap, color components of texture, image width, image height, always border = 0, type bta3 el color bta3 el pixel, range mn 0 to 255, data ely hsht8l 3leha)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // generate the mipmap (if requested)
    //lazm yb2a fe mipmap aw mesh hyrsm zay el tutorial
    if (generate_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // unbind the texture
    texture.unbind();

    stbi_image_free(data); //Free image data after uploading to GPU
    return size;
}