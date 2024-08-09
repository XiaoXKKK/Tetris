#include "draw.h"
#include "terminal.h"

#include <iostream>

/*
	    0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
U+250x	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
*/
namespace dw{
    inline int block2col(int block){
        return block * 2 - 1;
    }

    void window(int top, int left, int weight, int height, std::string title)
    {
        // two characters for each block

        tc::setCursor(top, block2col(left));
        std::cout << " \u250C";
        for (int i = 1; i < weight - 1; i++)
        {
            std::cout << "\u2500\u2500";
        }
        std::cout << "\u2510";
        tc::setCursor(top + height - 1, block2col(left));
        std::cout << " \u2514";
        for (int i = 1; i < weight - 1; i++)
        {
            std::cout << "\u2500\u2500";
        }
        std::cout << "\u2518";
        for (int i = top + 1; i < top + height - 1; i++)
        {
            tc::setCursor(i, block2col(left));
            std::cout << " \u2502";
            tc::setCursor(i, block2col(left) + (weight - 1) * 2);
            std::cout << "\u2502";
        }
        tc::setCursor(top, block2col(left) + (weight * 2 - title.size()) / 2);
        std::cout << title;
    }
}