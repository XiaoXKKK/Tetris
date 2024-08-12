#include "draw.h"
#include "terminal.h"
#include "utils.h"
#include "define.h"

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
namespace dw{                    //0123456
    const std::u32string thick = U" ━┃┏┓┗┛";
    const std::u32string thin = U" ─│┌┐└┘";
    const std::u32string double_line = U" ═║╔╗╚╝";
    const std::u32string rounded_corner = U" ─│╭╮╰╯";

    const std::u32string style = rounded_corner;


    void window(int top, int left, int weight, int height, std::string title)
    {
        // two characters for each block

        // first line
        tc::setCursor(top, ut::b2c(left));
        std::cout << ut::utf32_to_utf8({style[0],style[3]});
        for (int i = 1; i < weight - 1; i++)
        {
            std::cout << ut::utf32_to_utf8({style[1], style[1]});
        }
        std::cout << ut::utf32_to_utf8({style[4]});
        // last line
        tc::setCursor(top + height - 1, ut::b2c(left));
        std::cout << ut::utf32_to_utf8({style[0], style[5]});
        for (int i = 1; i < weight - 1; i++)
        {
            std::cout << ut::utf32_to_utf8({style[1], style[1]});
        }
        std::cout << ut::utf32_to_utf8({style[6]});
        // middle lines
        for (int i = top + 1; i < top + height - 1; i++)
        {
            tc::setCursor(i, ut::b2c(left));
            std::cout << ut::utf32_to_utf8({style[0], style[2]});
            tc::setCursor(i, ut::b2c(left) + (weight - 1) * 2);
            std::cout << ut::utf32_to_utf8({style[2]});
        }
        // title
        tc::setCursor(top, ut::b2c(left) + (weight * 2 - title.size()) / 2);
        std::cout << title;
    }
}