#include <stdio.h>

/* Comments */

// comment

#define CONST 12

int main()
{
    int a = 5;
    for (int i = 0; i < a; ++i)
    {
        char* var = "/* string */";
        char* var2 = "*/";
        char* var3 = "// asdasd";

        // some other comment */ asdad// asdasd

        char c = '\\';
        if ( i % 2 == 0)
        {
            // comments
            /*
                Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris faucibus neque porttitor diam bibendum blandit. Fusce venenatis neque sit amet arcu ullamcorper maximus. Suspendisse efficitur pellentesque tellus, nec sodales ipsum ultricies in. Quisque ornare turpis et mi mollis, eget pellentesque erat suscipit. 
            */
            continue;
        }
    }
}

// Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris faucibus neque porttitor diam bibendum blandit. Fusce venenatis neque sit amet arcu ullamcorper maximus. Suspendisse efficitur pellentesque tellus, nec sodales ipsum ultricies in. Quisque ornare turpis et mi mollis, eget pellentesque erat suscipit. 