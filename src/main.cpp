#include<TGraphx/framebuffer.hpp>

#include<sstream>
#include<fstream>
#include<thread>  
#include<chrono>

struct RGB {
    int r_ = 0;
    int g_ = 0;
    int b_ = 0;

    RGB(int r, int g, int b) 
       : r_(r), g_(g), b_(b){};
};

RGB m_color = RGB(0,0,0);

RGB morph_color(int iter, int iter_end, RGB start_color, RGB end_color){
    RGB m_color = start_color;
    float change = (float)iter/(float)iter_end; 

    m_color.r_ = m_color.r_ - (m_color.r_ * change) + (end_color.r_ * change);
    m_color.g_ = m_color.g_ - (m_color.g_ * change) + (end_color.g_ * change);
    m_color.b_ = m_color.b_ - (m_color.b_ * change) + (end_color.b_ * change);

    return m_color;
}

void looped_morph(RGB* m_color, int duration, RGB start_color, RGB end_color) {

    static int morph_iter = 1, morph_direction = 0;
        
    if (morph_iter==duration && morph_direction){
        morph_direction++;        

    } else if (morph_iter<duration && morph_direction){
        morph_iter++;
    }

    if(morph_iter==0 && !morph_direction){
        morph_direction--;

    } else if(morph_iter>0 && !morph_direction){
        morph_iter--; 
    }

    *m_color = morph_color(morph_iter, duration, start_color, end_color);
}

int main(){
    TGraphx::Framebuffer framebuffer;

    while(1) {
        framebuffer.push();
        TGraphx::Frame* frame_ref = framebuffer.get_frame(0);

        looped_morph(&m_color, 60*5, RGB(255,0,255), RGB(0,255,255));

        std::ifstream file("../ascii_art/computer_love_boxy");
        std::string content = "";
        std::string line = "";

        while(std::getline(file, line)){
            content += line;
        }

        frame_ref->append_mstr(frame_ref->w_/2-96/2, frame_ref->h_/2-18/2, content, '+');

        frame_ref->append_fg_color(0, 0, m_color.r_, m_color.g_, m_color.b_);
        frame_ref->append_bg_color(0, 0, 0,   0,   0);

        framebuffer.draw();
        framebuffer.pull();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }

    return 0;
}

