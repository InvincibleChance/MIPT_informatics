#include <iostrem>
namespace mipt
{
    namespace fefm
    {
        struct Point
        {
            int x, y;
        };
    }
    namespace frtk
    {
        void print(fefm::Point p)
        {





            std::cout << p.x << " " << p.y << std::endl;
        }





    }
}