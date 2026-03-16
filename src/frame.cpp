#include<TGraphx/frame.hpp>

#include<iostream>
#include<sstream>

//TODO: add error handling to these functions...

int TGraphx::Frame::append_str(int x, int y, std::string str){

    for(int c = 0; c<str.length(); c++){
        chars_[y*w_+x+c] = str[c];
    }

    return 0;
}

int TGraphx::Frame::append_mstr(int x, int y, std::string Input_Str, char Newline_Marker){

    std::vector<std::string> split_str; 
    std::stringstream str_stream(Input_Str); 
    std::string str_buf;

    while (std::getline(str_stream, str_buf, Newline_Marker)) {
        split_str.push_back(str_buf); 
    }

    for(int p = 0; p<split_str.size(); p++){
        append_str(x, y+p, split_str[p]);
    }

    return 0;
}

int TGraphx::Frame::append_fg_color(int x, int y, int r, int g, int b){

    std::stringstream str_stream;
    str_stream<<"\e[38;2;"<<r<<";"<<g<<";"<<b<<"m";

    ansi_codes_[y*w_+x] += str_stream.str();

    return 0;
}

int TGraphx::Frame::append_bg_color(int x, int y, int r, int g, int b){

    std::stringstream str_stream;
    str_stream<<"\e[48;2;"<<r<<";"<<g<<";"<<b<<"m";

    ansi_codes_[y*w_+x] += str_stream.str();

    return 0;
}
