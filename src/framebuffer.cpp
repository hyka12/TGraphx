#include<TGraphx/framebuffer.hpp>

#include<string>
#include<unistd.h>

int TGraphx::get_term_size(struct winsize &term_size){
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_size) == -1)
        return 1;

    return 0;
};

int TGraphx::Framebuffer::push(){

    struct winsize term_size;
    TGraphx::get_term_size(term_size);

    TGraphx::Frame new_frame;
    new_frame.w_ = term_size.ws_col;
    new_frame.h_ = term_size.ws_row;

    for(int row = 0; row < new_frame.w_; row++){
        for(int col = 0; col < new_frame.h_; col++){
            new_frame.chars_.push_back(' ');
            new_frame.ansi_codes_.push_back("");
        }
    }

    frames_.insert(frames_.begin(), new_frame);

    return 0;
}

int TGraphx::Framebuffer::push(TGraphx::Frame frame){
    frames_.insert(frames_.begin(), frame);

    return 0;
};

TGraphx::Frame* TGraphx::Framebuffer::get_frame(int frame_index){
    return &frames_[frame_index];
}

int TGraphx::Framebuffer::draw(){

    TGraphx::Frame first_frame = frames_[frames_.size()-1];

    std::string batch;

    for(int f = 0; f<first_frame.w_ * first_frame.h_; f++) {
        batch += first_frame.ansi_codes_[f];
        batch += first_frame.chars_[f];
    }

    write(STDOUT_FILENO, batch.c_str(), batch.length());

    return 0;
}

int TGraphx::Framebuffer::pull(){

    if (!frames_.empty()) { 
        frames_.pop_back();
    }else{
        return 1;
    }

    return 0;
}









