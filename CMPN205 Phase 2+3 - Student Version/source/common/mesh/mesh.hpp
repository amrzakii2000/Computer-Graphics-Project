#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our
{

 // locations of attributes in GPU 
#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    //Mesh is a collection of vertices that defines the object. It defines the object shape.
    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // TODO: Write this function
            //  remember to store the number of elements in "elementCount" since you will need it for drawing
            //  For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            elementCount = elements.size();

            glGenVertexArrays(1, &VAO); //1 3lshan b3ml generate le buffer wahed bas (a vertex array object to define how to read the vertex & element buffer during rendering)
            glGenBuffers(1, &VBO); //1 3lshan b3ml generate le buffer wahed bas (a vertex buffer to store the vertex data on the VRAM
            glGenBuffers(1, &EBO); //1 3lshan b3ml generate le buffer wahed bas (an element buffer to store the element data on the VRAM)

            glBindVertexArray(VAO); //bn3ml bind lel vertex array ely hnsht8l 3leh
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //b3mel bind lel element buffer ely hnsht8l 3leh

            //We move the data of elements to the element buffer(el target ely h3ml bind 3leh, el size bta3 el buffer, el address bta3 el data bta3ty, el mode of draw)
            //Drawing modes:
            //GL_STATIC_DRAW : The data store contents will be modified once and used many times.
            //GL_DYNAMIC_DRAW: The data store contents will be modified repeatedly and used many times.
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);

            //We move the data of verticies to vertex buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


            // Position attribute
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
            //(location ely hab3t 3leh, size of elements ely hab3tha, type of data, ha3ml normalize wla la2 ? , bamshy 2ad eih 3lshan ab3t ely ba3do, el offset ely babda2 mno) 
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

            // Color attribute
            //unsigned byte for efficiency and colors from 0 to 255 for each channel
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

            // Texture Coordinate attribute
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));

            // Normal attribute
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
        }

        // this function should render the mesh
        void draw()
        {
            // TODO: Write this function

            // Bind the VAO
            glBindVertexArray(VAO);

            // Draw the mesh
            //(type of primitives to draw, count of elements to draw, type of the indicies, pointer to location wjhere indices are stored)
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);

            // Unbind the VAO
            glBindVertexArray(0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            // TODO: Write this function
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}