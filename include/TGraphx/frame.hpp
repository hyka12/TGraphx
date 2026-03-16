#ifndef FRAME_HEADER
#define FRAME_HEADER

#include<vector>
#include<string>

namespace TGraphx {

    struct Frame {
        std::vector<char> chars_;
        std::vector<std::string> ansi_codes_;
        int w_, h_;

        int append_str(int x, int y, std::string str);
        int append_mstr(int x, int y, std::string str, char newline_marker);

        int append_fg_color(int x, int y, int r, int g, int b);
        int append_bg_color(int x, int y, int r, int g, int b);
    };
}

#endif 
