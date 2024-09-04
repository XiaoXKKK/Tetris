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
    void tetromino(Tetromino_0 &t, int top, int left)
    {
        tc::setCursor(top, ut::b2c(left));
        for(int i = 0;i < t.size();i++){
            tc::setCursor(top + i, ut::b2c(left));
            for(int j = 0;j < t[i].size();j++){
                if(t[i][j] != 0){
                    tc::resetColor();
                    tc::setBackColor(int(gm::tetro_colors[t[i][j]]));
                    std::cout << "  ";
                }
                else{
                    tc::resetColor();
                    std::cout << "  ";
                }
            }
            std::cout << std::endl;
        }
    }
    void tetromino(Tetromino& t, int top, int left, int index)
    {
        tc::setCursor(top, ut::b2c(left));
        tc::setBackColor(t[index][0].second);
        std::cout << "  ";
        for (auto& i : t[index]) {
            if (i.first >= 'A') continue;
            tc::setCursor(top - i.second, ut::b2c(left + i.first));
            std::cout << "  ";
        }
    }
    void frame(Matrix& m, int top, int left)
    {
        static Matrix buffer(m.size(), std::vector<int>(m[0].size(), -1));
        std::ostringstream oss;

        // frame xy -> col row
        int row, col;
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 20; y++)
            {
                if (m[y][x] == buffer[y][x]) continue;
                buffer[y][x] = m[y][x];

                row = 20 - y - 1 + top;
                col = x + left;
                tc::setCursor(row, ut::b2c(col), oss);
                if (m[y][x] > 0)
                {
                    tc::resetColor(oss);
                    tc::setBackColor(m[y][x], oss);
                    oss << "  ";
                }
                else if (m[y][x] < 0)
                {
                    tc::resetColor(oss);
                    tc::setForeColor(-m[y][x], oss);
                    oss << "\u25E3\u25E5";
                }
                else
                {
                    tc::resetColor(oss);
                    oss << "\u30FB";
                }
            }
        }
        std::cout << oss.str();
    }
}