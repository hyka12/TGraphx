#ifndef MATRIX_HEADER
#define MATRIX_HEADER 

#include<TGraphx/frame.hpp>

#include<sys/ioctl.h>
#include<unistd.h>

#include<vector>

namespace TGraphx {
    int get_term_size(struct winsize &term_size);
    
    class Framebuffer{
        std::vector<Frame> frames_;

    public:
        int frame_count(){return frames_.size();};

        int push(); // pushes blank frame
        int push(Frame frame);

        Frame* get_frame(int index);

        int draw();
        int pull();

    };

};

#endif
